# plagiat

***Описание***: Был тут на CTF и мне не понравился таск, вот и решил скопировать...

Формат: EclipseCTF{smth_like_text}

---
### Решение

Участникам выдан архив с фотографиями из игры `Dota2`:

![ScreenShot](Assets/For_Tasks/plagiat-1.png)

Первые буквы из названий этих предметов складываются в флаг:

```
1. nullifier => n
2. observer ward => o
3. aghamin's scepter => a
4. null talisman => n
5. iron branch => i
6. maelstrom => m
7. eul's scepter => e
8. giant ring => g
9. infused Raindrops => i
10. reaver => r
11. linken's Sphere => l
12. sange and yasha => s
13. octarine core => o
14. ninja gear => n
15. cornucopia => c
16. teleport => t
17. falcon blade => f
```

Альтернативный вариант решения (долгий):
1. Открываем архив и видим предметы из доты
2.  Начинаем искать похожие таски на последних прошедших [CTF](https://ctftime.org/event/list/past)
3. Почти сразу находим MireaCTF Quals 2024
4. Находим репозиторий на [GitHub](https://github.com/cR4-sh/mireactf-quals-2024)
5. Дальше решаем таск точно так же, как и таск `first-title`
6. Получаем флаг

---

***Флаг***: `EclipseCTF{no_anime_girls_on_ctf}`