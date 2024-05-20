# RSA-Again

***Описание***: И вновь я решил вкатиться в криптографию, жаль, что порог вхождения слишком большой. Или ты можешь доказать обратное?

Подключение: `nc localhost 8888`

Формат: EclipseCTF{...}

---
### Решение

Алгоритм решения:
1. Подключаемся через nc 
2. Cмотрим функционал и видим функцию get_flag
3. Видим, что используется маленькая e
4. Проводим атаку Хастада (пример ниже)
5. Получаем флаг

```python
import gmpy2

gmpy2.get_context().precision = 2048
from binascii import unhexlify
from gmpy2 import root

# Håstad's Broadcast Attack
# https://id0-rsa.pub/problem/11/

# Resources
# https://en.wikipedia.org/wiki/Coppersmith%27s_Attack
# https://github.com/sigh/Python-Math/blob/master/ntheory.py

EXPONENT = 3


def chinese_remainder_theorem(items):
    # Determine N, the product of all n_i
    N = 1
    for a, n in items:
        N *= n

    # Find the solution (mod N)
    result = 0
    for a, n in items:
        m = N // n
        d, s, r = gmpy2.gcdext(n, m)
        if d != 1:
            raise "Input not pairwise co-prime"
        result += a * r * m

    # Make sure we return the canonical solution.
    return result % N


if __name__ == '__main__':
    C1 = 6600336144898405432946865436216772285146119544279321223031295846195788727534219708282614442603025040323487261314811288662809155318383157879916820267685839
    C2 = 1671885210110551057447129632193021681917709531776525510550128289291498136848307846779992577142467485721894400412172229690727592165609640188687689416624299
    C3 = 5881250544591480647276338436519107268579528261847855957955859811774441699930395384480817174849489213006387996187532991245115418733617842518527759649452157

    N1 = 10031707613882551289969453699138211364559217639657447865847380805871205370366656345482474105719782855208981329336085375715796342584785476023127463498443903
    N2 = 6788073797654373334416556336884425041130549170973985872134789187072829388112270377614165724714434752060388014585799532536168469557711928942125334684845697
    N3 = 6754877693337919717100589714967726401527503320667043578305281679899867986256260820915239830244423263194100177711415492524974743705965224378119724058774103

    C = chinese_remainder_theorem([(C1, N1), (C2, N2), (C3, N3)])
    M = int(root(C, 3))
    M = hex(M)[2:]
    print(unhexlify(M))

```

---

***Флаг***: `EclipseCTF{S@me_m3ss@ges_1s_n0t_s0_g00d}`