@echo off
chcp 65001 >nul
setlocal
set APP_DIR=%~dp0
cd /d %APP_DIR%
WinT.exe
endlocal
pause
