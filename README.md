# Короткое описание
## Как использовать
Используя список базовых функций вы можете написать программу под любу вашу задачу 
Список функций:
```
    push arg
    pop  arg

    add 
    sub 
    mul 
    divv
    out 
    in  
    sqrt
    sin  
    cos  
    dump 
    hlt  
    ja   arg
    jae  arg
    jb   arg
    jbe  arg
    je   arg
    jne  arg
    jmp  arg
    drow 
    call arg
    ret
```
### Разновидности push
push chislo               - складывает число в стек
push registr              - складывает значение из регистра в стек
push chislo + registr     - складывает сумму чисоа и значения из регистра в стек
push [ chislo ]           - складывает в стек число из RAM по адресу chislo
push [ registr ]          - складывает в стек число из RAM по адрес хранящемся в registr
push [ chislo + registr ] - складывает в стек число из RAM по адресу хранящемся в registr + chislo

### Разновидности pop
pop registr               - складывает значение из стека в регистр
pop [ registr ]           - складывает значение из стека в RAM по адресу хранящемся в registr
pop [ chislo ]            - складывает значение из стека в RAM по адресу chislo
pop [ registr + chislo ]  - складывает значение из стека в RAM по адресу хранящемся в registr + chislo

## Примеры кода

Функция, использующая рекурсию для подсчета факториала любого числа

```
main:
                in
                pop     cx
                call    factorial
                push    cx
                out
                hlt

factorial:
                dump
                push    0
                dump
                push    cx
                dump
                jb      iteration
                dump
                push    1
                pop     cx
                dump
                ret
iteration:      
                dump
                push    cx
                push    cx
                push    1
                sub
                dump
                pop     cx
                dump
                call    factorial
                dump
                push    cx
                mul
                dump
                pop     cx
                ret
```

# Как использовать
## Установка
```
git clone --depth=1 https://github.com/MatveyDmitryevich2/SPU
cd SPU
./bash_asembler.sh
./bash_proccessor.sh
```
## Запуск
### Ассемблер
```
./assembler.exe
```
### Процессор
```
./processor.exe
```

# Готовые примеры
- Факториал
- Квадратка
- Кружок

# Reporting Issues
Пожалуйста, сообщайте о любых проблемах, которые вы можете обнаружить в нашем багтрекере.

# Contributing code
Вы можете отправлять запросы на обновление в репозитории GitHub. Пожалуйста, ознакомьтесь с руководством по внесению изменений для получения информации о кодировании, документации или рекомендациях по исправлению.

# Документация
Важно при обращении к памяти при помощи комнад push или pop первым аргументом передавать число, а следом регистр, а не 
наоборот. К сожалению, программа этого не учитывает.

# Лицензия
The project is licensed under MIT License.