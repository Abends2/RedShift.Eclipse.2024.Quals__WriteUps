# TicTakToe

***Описание***: Попробуй победить!

Формат: EclipseCTF{...}

---
### Решение - Этап 1. Исследование дизассемблированного кода

После нескольких неудачных попыток победить компьютер в крестики-нолики руки совсем опускаются. Поэтому для решения таска следует перейти в IDA PRO x64. Нас встречает main-функция:

![ScreenShot](../screenshots/TicTakToe-1.png)

Мы помним, что после проигрыша/ничьи программа находится в ожидании какое-то время. Значит тело программы находится до функции Sleep, перейдем к нему. Здесь замечаем 3 переменные типа BOOL, которые являются своеобразными «флагами состояния». Все три флага передаются в единую функцию в конце программы. Верно будет предположить, что именно эта функция является проверкой на победу:

![ScreenShot](../screenshots/TicTakToe-2.png)

В ассемблерном представлении данной функции в самом конце замечаем вызов функции wcout, которая предположительно выводит сообщение о статусе игры:

![ScreenShot](../screenshots/TicTakToe-3.png)

При изучении псевдокода видим, что на вывод идет массив v5, в котором хранится массив v46:

![ScreenShot](../screenshots/TicTakToe-4.png)

В массиве v46 хранятся сообщения о ничье (Tie) и о выигрыше компьютера (Winner is Computer):

![ScreenShot](../screenshots/TicTakToe-5.png)

Однако нет никакого сообщения о выигрыше пользователя. Возвращаясь на шаг назад, вспоминаем об альтернативном блоке кода, расположенном слева:

![ScreenShot](../screenshots/TicTakToe-6.png)

В конце блока вызывается функция free(), которая предположительно освобождает какой-то блок памяти. Перейдем к функции до вызова функции и обнаружим вызов функции printf():

![ScreenShot](../screenshots/TicTakToe-7.png)

### Решение - Этап 2. Отладка с модификацией

Можно сделать вывод, что сообщение о выигрыше выводится через эту функцию. Настало время проверить гипотезу и выполнить отладку программы с последующей модификацией. Для этого поставлю точку останова на первом значимом разветвлении программы в функции проверки победителя:

![ScreenShot](../screenshots/TicTakToe-8.png)

Вторую точку остановка поставлю в разветвлении, которое гарантированно приведет к выводу информации скрытой функцией:

![ScreenShot](../screenshots/TicTakToe-9.png)

Запустим отладку, снова проиграем компьютеру и перейдем в точку останова. Мигающая стрелочка свидетельствует о переходе вправо. Нас это устраивает. Ставим еще одну точку останова на следующем разветвлении и нажимаем F9 для перехода к ней:

![ScreenShot](../screenshots/TicTakToe-10.png)

Это разветвление ведет нас напрямую к выводу сообщения о ничье/поражении, поэтому меняем инструкцию с jnz на jz и ставим следующую точку останова:

![ScreenShot](../screenshots/TicTakToe-11.png)

![ScreenShot](../screenshots/TicTakToe-12.png)

Для сокращения количества переходов здесь меняем инструкцию с jz на jnz и переходим в следующую точку останова:

![ScreenShot](../screenshots/TicTakToe-13.png)

Здесь меняем инструкцию с jnz на jz и ставим еще один breakpoint, таким образом организуем себе прямой путь к нужному блоку кода:

![ScreenShot](../screenshots/TicTakToe-14.png)

В нем оставляем инструкцию jz, и переходим к главной точке останова:

![ScreenShot](../screenshots/TicTakToe-15.png)

Если все сделано правильно, jz-инструкция должна привести нас напрямую к выводу победного сообщения, которое вызывается после блоков кода с формированием этого самого сообщения. Поставим точку останова в почти в конце программы, после вызова функции вывода на экран:

![ScreenShot](../screenshots/TicTakToe-16.png)

Если заглянуть в терминал, то мы увидим это самое сообщение:

![ScreenShot](../screenshots/TicTakToe-17.png)

Воспользуемся инструментом Cipher Identifier на веб-сайте dcode.fr. Он делает 2 предположения, верным является №2. Это кодировка base58. При расшифровке получаем заветный флаг:

![ScreenShot](../screenshots/TicTakToe-18.png)

---

***Флаг***: `EclipseCTF{H&ppy_v1ct0ry}`