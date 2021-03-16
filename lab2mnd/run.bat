@ECHO OFF

g++ sol.cpp -o sol.exe -ggdb -DDEBUG -std=c++14 -O2 -Wl,--stack=256000000 -Wall -Wextra -Wshadow 

:Start

sol.exe > out.txt

cls
setlocal EnableDelayedExpansion
set "cmd=findstr /R /N "^^" out.txt | find /C ":""

for /f %%a in ('!cmd!') do set number=%%a
::echo %number%

if %number% == 1 (echo The dispersion is inhomogeneous & Goto Start) else (echo FCKSCT & type out.txt)

pause