@echo off
set cur_dir= %~dp0
echo %cur_dir%
REM schtasks /create /? > %cur_dir%\schtasks_help.txt
set d=%date:~0,10%
set hour=%time:~0,2%
set min=%time:~3,2%
set str0=0
echo %min%
set /a min1=%min%+1
if %min1% lss 10 (set min1=%str0%%min1%)
set st=%hour%:%min1%
echo %st%
If "%1"=="" (
echo exe_name can't be null!
pause
exit
)

set exe_name=%1
REM schtasks /create /tn taskname2 /tr "%cur_dir%reboot_exe.bat %exe_name%" /sc once /st %st% /ru %username% /Z 
schtasks /delete /tn taskname1 /f
schtasks /create /tn taskname1 /tr "%~dp0reboot_exe.bat %exe_name%" /sc once /st %st% /ru %username% /IT  

