@echo off

set ts_dir=%cd%\ts\

cd ../

call:translate src

pause 
exit

rem Func define
:translate
   cd %1
   for /f "tokens=2" %%i in ('find /i "(target_name" CMakeLists.txt') do set name=%%i
   set folder=%name:~0,-1%
   qmake -project -o %folder%.pro
   echo TRANSLATIONS += %ts_dir%/%folder%_zh_CN.ts >> %folder%.pro
   lupdate -verbose %folder%.pro -ts %ts_dir%/%folder%_zh_CN.ts
   del %folder%.pro
   cd %base_dir%
goto:eof
