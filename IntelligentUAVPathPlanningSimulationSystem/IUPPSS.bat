@ECHO OFF

SET batFileDir=%cd%
SET pythonExeFilePath=/python-3.7.5-embed-amd64/python.exe
SET MainAppFilePath=/core/main.py
SET pythonExeAbsFilePath=%batFileDir%%pythonExeFilePath%
REM SET pythonExeAbsFilePath=Python
SET MainAppAbsFilePath=%batFileDir%%MainAppFilePath%
SET "spaceChar= "
SET RunCommand=%pythonExeAbsFilePath%%spaceChar%%MainAppAbsFilePath%

ECHO.

ECHO Intelligent UAV path Planning simulation system (V1.0.0) is starting, please wait a moment......

ECHO.

%RunCommand%

PAUSE
