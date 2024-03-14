echo off
chcp 65001
copy ..\Debug\bookword.exe bookword.exe

set "resultTests=Tests Ok"

echo ****************** Start tests ****************

call :startTest smoke

del .\out\notExistFile.txt
call :startTest notExistFile

call :startTest camelEn

call :startTest camelRu

echo ****************** End tests ******************
echo %resultTests%
exit 0

:startTest
set "pathIn=.\in\"
set "pathOut=.\out\"
set "pathCmp=.\compare\"

set "bookSrc=%pathIn%%1.txt"
set "book=%pathOut%%1.txt"
echo copy %bookSrc% %book%
copy %bookSrc% %book%

set "cmdFile=%pathIn%%1_cmd.txt"
echo bookword.exe %book% <%cmdFile%
bookword.exe %book% <%cmdFile%

set "cmpFile=%pathCmp%%1.txt"
fc %book% %cmpFile%
if errorlevel 1 (
    echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!
    set "resultTests=Tests is not Ok"
) else (
    echo ----------------------Ok-----------------------
)
exit /b
