# F4llout

***Описание***: Вас, как самого лучшего специалиста по компьютерным системам в стране, срочно вызвали на совещание Генерального Штаба Вооружённых сил СССР. Вы немного задерживаетесь, но тут вы слышите монолог одного из генералов...

Подключение: `nc localhost 31338`

Формат: EclipseCTF{...}

---
### Решение

![ScreenShot](screenshots/F4llout-1.png)

![ScreenShot](screenshots/F4llout-2.png)

![ScreenShot](screenshots/F4llout-3.png)

У нас есть некоторые сообщения, которые необходимо расшифровать. При этом есть сразу подсказка - Windows Server. В системах Windows ранее активно использовался алгоритм шифрования `cpassword`. Кое-где его можно встретить и сейчас, но это уже из разряда редко.

Через сайт `https://securixy.kz/hack-faq/gpp-password-decrypt-online.html/` расшифровываем все сообщения поочередно:

```
1. Uhn+wMm2Ankkpfkoo86t1Q = The
2. wWHIrHyXsbFpBhpQ/fMKbwEEg3Ko0Es+RskCj/W6F8I = password
3. HS/pGpYX9bQoUAB8NZ1hrA = is
4. +vGjK3XFiINhO1jwdVnMAaJMqQoe7lC89bSwm+Qe3Y2m5PrxvgFECr3vvCDLzNyz = MilitaryAdministrator
```

Пробуем с помощью кастомной команды из описания подключиться к пункту управления одной из точек. Получается это сделать только на `point_3`:

![ScreenShot](screenshots/F4llout-4.png)

И вот тут интересно. Если выберем `stop`, то...

![ScreenShot](screenshots/F4llout-5.png)

Да, отключив точку, мы остановили все процессы и запустили ракеты, но что, если попробовать `leave`:

![ScreenShot](screenshots/F4llout-6.png)

Без лишних слов. Надеюсь, вам понравился таск!

---

***Флаг***: `EclipseCTF{w4r___w4r_n3v3r_ch4ng3s}`
