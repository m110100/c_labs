@echo off

if exist fib_static.o del fib_static.o
if exist fib_static.lib del fib_static.lib
if exist main.exe del main.exe
if exist keyboard.o del keyboard.o
if exist keyboard.dll del keyboard.dll

g++ -c fib_static.cpp -o fib_static.o
ar rcs fib_static.lib fib_static.o

g++ main.cpp -o main.exe fib_static.lib

g++ -c keyboard.cpp -DKEYBOARD_EXPORTS -o keyboard.o

g++ -shared -o keyboard.dll keyboard.o -luser32 -lpthread
