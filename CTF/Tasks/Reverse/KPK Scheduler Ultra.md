# KPK Scheduler Ultra

***Описание***: В день начала RedShift, у непутевого разработчика перестало запускаться приложение, странно всё это... и в настройках появились надписи...

Формат: eclipseCTF{...}

---
### Решение (Вариант 1) - JADX

Для начала скачиваем JADX. После этого открываем прилагаемый к таску APK-файл. И исследуем структуру проекта. Зачастую всё что нужно хранится в `package ID` в нашем случае это `com` => `KopohGames.Scheduler (com.KopohGames.Scheduler)`

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-1.png)

Изучая приложение, мы находим файл `TeacherLoginScreen`. Находим в нем его `ViewModel` с названием `TeacherLoginViewModel`:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-2.png)

Видим обращение к файлу `TeacherRepository`. Дальше, кликая по методу `teacherLogin(login, password)`, получаем ссылку на этот метод, в котором спрятаны значения для входа:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-3.png)

Перейдя в метод, мы видим условное выражение `if(login == "eclipse" && password == "eclipse")`. Далее входим в приложение, предварительно поставив в телефоне (эмуляторе) дату начала `Redshift.Eclipse (18.12.2023)`:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-4.png)

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-5.png)

И по условию смотрим на страничку настроек, где видим подсказку (что надо найти её в дискорде у пользователя `kopoh`)

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-6.png)

Или же на этапе исследования проекта найти картинку, которая закопана глубоко в файлах:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-7.png)

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-8.png)

И флаг это:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-9.png)

---
### Решение (Вариант 2) - IDA PRO

Открываем APK-файл в ida64, как APK:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-10.png)

Дальше используем `Strings` для того, чтобы собрать все строки в коде:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-11.png)

После этого ищем (поле/строку `email` или `eclipse`):

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-12.png)

В итоге выходим на блок кода с условием `if(email == "eclipse")`:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-13.png)

Далее вход в приложение с датой начала EclipseCTF и поиск флага в дискорде:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-4.png)

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-5.png)

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-6.png)

Итог:

![ScreenShot](Assets/For_Tasks/KPK-Scheduler-Ultra-9.png)

---

***Флаг***: `eclipseCTF{k0po#_1S_U9V3R$}`