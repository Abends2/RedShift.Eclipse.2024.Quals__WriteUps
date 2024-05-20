# Dirty logging

***Описание***: Странный какой-то сайт, еще и обзывается. Эти печеньки вечно что-то не договаривают...

Ссылка: `http://localhost:5555`

Формат: EclipseCTF{...}

---
### Решение - Этап 1. Исследование ресурса

Для начала посмотрим запрос в Burp Suite. Передается какая-то строка в base64:

![ScreenShot](screenshots/Dirty-logging-1.png)

Раскодируем через python base64 или любым другим способом:

![ScreenShot](screenshots/Dirty-logging-2.png)

![ScreenShot](screenshots/Dirty-logging-3.png)
### Решение - Этап 2. Эксперименты

Видим `php serialized cookie`. Обратимся к файлу `index.php`, чтобы посмотреть, как они формируются:

![ScreenShot](screenshots/Dirty-logging-4.png)

Если у пользователя нет куки, создается новый объект класса `User`. Заглянем в файл `user.class.php`. Можно попробовать создать куки для другого пользователя, например `admin`. Для этого допишем в файл `index.php` новую строку:

![ScreenShot](screenshots/Dirty-logging-5.png)

Выполним `php index.php` через терминал:

![ScreenShot](screenshots/Dirty-logging-6.png)

Раскодируем строку с помощью python base64:

![ScreenShot](screenshots/Dirty-logging-7.png)
### Решение - Этап 3. Формирование зловредного cookie

Далее перейдем к файлу `log.class.php`:

![ScreenShot](screenshots/Dirty-logging-8.png)

Понимаем, что этот класс можно использовать для вывода лог-файла на экран. Вернемся в `user.class.php` и заменим вызов класса `Welcome` на `Log`:

![ScreenShot](screenshots/Dirty-logging-9.png)

В log.class.php сменим переменную на `/etc/passwd`:

![ScreenShot](screenshots/Dirty-logging-10.png)

Снова выполним `index.php` через терминал и посмотрим, что в нем лежит:

![ScreenShot](screenshots/Dirty-logging-11.png)

![ScreenShot](screenshots/Dirty-logging-12.png)

Попробуем закинуть это куки в запрос, получим в ответе от сервера то же самое:

![ScreenShot](screenshots/Dirty-logging-13.png)

![ScreenShot](screenshots/Dirty-logging-14.png)
### Решение - Этап 4. Чтение флага

Попробуем таким же способом прочитать `flag.txt`:

![ScreenShot](screenshots/Dirty-logging-15.png)

![ScreenShot](screenshots/Dirty-logging-16.png)

![ScreenShot](screenshots/Dirty-logging-17.png)

![ScreenShot](screenshots/Dirty-logging-18.png)

![ScreenShot](screenshots/Dirty-logging-19.png)

---

***Флаг***: `EclipseCTF{d1rt7_php_l0gging}`

