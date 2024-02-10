echo off

copy /y ..\cmake-build-debug\replace.exe replace.exe

set "resultTests=Test Ok"

echo ****************** Start tests ****************
echo ---------------- Empty file test --------------
call :startTest empty.txt empty ######
echo -------- One symbol without LN file test ------
call :startTest one_symbol.txt empty ######
echo ---------- One symbol with LN file test -------
call :startTest one_symbol_with_ln.txt empty ######
echo ---------------- Non result test --------------
call :startTest non_result.txt haha ######
echo -------------------- 1231234 ------------------
call :startTest 1231234.txt 1231234 @@@@@@@
echo ------------------ Cycle word -----------------
call :startTest haha.txt ha haha
echo ---------- Result in begin of the word --------
call :startTest begin_word.txt prop 123456
echo ----------- Result in end of the word ---------
call :startTest end_word.txt ties 123456
echo ----------- Result in begin of the file -------
call :startTest begin_file.txt short 123456
echo ------------- Result in end of the file -------
call :startTest end_file.txt choice 123456
echo ------------- Non existent in file ------------
echo replace.exe .\correct\in\non_existent.txt .\correct\out\non_existent.txt empty ######
replace.exe .\correct\in\non_existent.txt .\correct\out\non_existent.txt empty ######
echo --------------- Zero string find --------------
call :startTest empty_search.txt "" haha
echo ----------- Start without parameters ----------
echo replace.exe
replace.exe
echo ****************** End tests ******************
echo %resultTests%
exit 0

:startTest
set "pathIn=.\correct\in\"
set "pathOut=.\correct\out\"
set "pathCmp=.\correct\compare\"
set "inFile=%pathIn%%1"
set "outFile=%pathOut%%1"
set "cmpFile=%pathCmp%%1"
set searchWord=%2
set newWord=%3
echo replace.exe %inFile% %outFile% %searchWord% %newWord%
replace.exe %inFile% %outFile% %searchWord% %newWord%
fc %outFile% %cmpFile%
if errorlevel 1 (
    echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!
    set "resultTests=Test is not Ok"
) else (
    echo ----------------------Ok-----------------------
)
exit /b