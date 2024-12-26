@echo off

if exist fib_static.o del fib_static.o
if exist fib_static.lib del fib_static.lib
if exist keyboard.o del keyboard.o
if exist keyboard.dll del keyboard.dll
if exist main.exe del main.exe

g++ -c fib_static.cpp -DFIB_STATIC_EXPORTS -o fib_static.o
g++ -shared -o fib_static.dll fib_static.o
g++ -c keyboard.cpp -DKEYBOARD_EXPORTS -o keyboard.o
g++ -shared -o keyboard.dll keyboard.o -luser32 -lpthread

g++ main.cpp -o main.exe -L. -lfib_static
