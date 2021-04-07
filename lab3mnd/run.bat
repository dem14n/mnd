@ECHO OFF

javac Main.java

:Start

java Main > output.txt 2> error.txt

cls
setlocal EnableDelayedExpansion
set "cmd=findstr /R /N "^^" error.txt | find /C ":""

for /f %%a in ('!cmd!') do set number=%%a
::echo %number%

if %number% == 1 (echo The regression equation is inadequate to the original at a significance level of 0.05 & Goto Start) else (echo FCKSCT & type output.txt)

pause