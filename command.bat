@echo off

rem Удаляем предыдущие скомпилированные файлы
if exist fib_static.o del fib_static.o
if exist fib_static.lib del fib_static.lib
if exist main.exe del main.exe
if exist keyboard.o del keyboard.o
if exist keyboard.dll del keyboard.dll

rem Компиляция объекта для статической библиотеки
g++ -c fib_static.cpp -o fib_static.o
rem Создание статической библиотеки
ar rcs fib_static.lib fib_static.o

rem Компиляция исполняемого файла main.exe с использованием статической библиотеки
g++ main.cpp -o main.exe fib_static.lib


rem Компиляция объекта для динамической библиотеки
g++ -c keyboard.cpp -DKEYBOARD_EXPORTS -o keyboard.o

rem Создание динамической библиотеки

g++ -shared -o keyboard.dll keyboard.o -luser32 -lpthread

echo Компиляция завершена. Вы можете запускать main.exe.