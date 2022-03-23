@echo off

SETLOCAL ENABLEDELAYEDEXPANSION 

set ts_dir=%cd%\ts
set qm_dir=%cd%\qm

cd %ts_dir%

for %%i in (*.ts) do (
  set str=%%i
  set file_name=!str:.ts=.qm!
  lrelease -verbose %%i -qm %qm_dir%\!file_name!
)

pause