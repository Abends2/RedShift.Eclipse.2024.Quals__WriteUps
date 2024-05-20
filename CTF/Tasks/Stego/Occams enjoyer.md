# Occams enjoyer

***Описание***: Оккам! Положи бритву! Пожалуйста!

Формат: EclipseCTF{...}

---
### Решение

Участникам выдана картинка:

![ScreenShot](Assets/For_Tasks/Okam-1.png)

Закидываем изображение в `Aperi'Solve`:

>https://aperisolve.fr/

![ScreenShot](Assets/For_Tasks/Okam-2.png)

![ScreenShot](Assets/For_Tasks/Okam-3.png)

Обращаем внимание на LSB. `Aperi'Solve` сразу не решил, автор таска вставил несколько абзацев текста поэтому поля вывода не хватает. Находим тулзу для извлечения данных (LSB)

>https://stylesuxx.github.io/steganography/

![ScreenShot](Assets/For_Tasks/Okam-4.png)

---

***Флаг***: `EclipseCTF{okkam_razor_LSB}`