# string.h

## Description
Реализация библеотеки string.h языка C.
Реализованы функции:
- sprintf
- memchr
- memcmp
- memcpy
- memmove
- memset
- strcat
- strncat
- strchr
- strcmp
- strncmp
- strcpy
- strncpy
- strcspn
- strerror
- strlen
- strpbrk
- strrchr
- strspn
- strstr
- strtok
- to_upper
- to_lower
- insert
- trim

## to run

-собрать библиотеку
```
make string.a
```
-запустить тесты
```
make test
```
-получить отсчёт о тестах в виде html-страницы
```
make gcov_report
