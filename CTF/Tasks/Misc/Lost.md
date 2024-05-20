# Lost

***Описание***: Я тут потерял кое-что в репозитории, помоги восстановить данные

Формат: EclipseCTF{...}

---
### Решение

Команда `git fsck` позволит просканировать репозиторий на наличие `dangling`-объектов. Таким образом, мы получим хэш нашего объекта:

![ScreenShot](screenshots/Lost-1.png)

Просматриваем содержимое `dangling-blob`:

![ScreenShot](screenshots/Lost-2.png)

---

***Флаг***: `EclipseCTF{git_lost_blob}`