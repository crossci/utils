@echo off
set cur_dir= %~dp0
set exe_name=%1
set waitTime=2
echo %cur_dir%%exe_name%
taskkill /im %exe_name%* /f
ping -n %waitTime% 127.0>nul
start %cur_dir%%exe_name%



