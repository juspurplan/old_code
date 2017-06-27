@echo off
java Assembler
echo Source Path:
set /p src=
echo Dest Path:
set dest=0
set /p dest=%=%

if %dest%==0 goto one else goto two

:two
java Assembler %src% %dest%
goto end

:one
java Assembler %src%
goto end

:end
pause