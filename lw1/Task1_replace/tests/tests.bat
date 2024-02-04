echo off

copy /y ..\cmake-build-debug\replace.exe replace.exe

echo ************* Start correct tests *************

echo ---------------- Empty file test --------------
echo replace.exe .\correct\in\empty.txt .\correct\out\empty.txt empty ######
replace.exe .\correct\in\empty.txt .\correct\out\empty.txt empty ######
fc .\correct\out\empty.txt .\correct\compare\empty.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo ---------------- Non result test --------------
echo replace.exe .\correct\in\readme.txt .\correct\out\non_result.txt haha ######
replace.exe .\correct\in\readme.txt .\correct\out\non_result.txt haha ######
fc .\correct\out\non_result.txt .\correct\in\readme.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo -------------------- 1231234 ------------------
echo replace.exe .\correct\in\1231234.txt .\correct\out\1231234.txt 1231234 @@@@@@@
replace.exe .\correct\in\1231234.txt .\correct\out\1231234.txt 1231234 @@@@@@@
fc .\correct\out\1231234.txt .\correct\compare\1231234.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo ------------------ Cycle word -----------------
echo replace.exe .\correct\in\haha.txt .\correct\out\haha.txt ha haha
replace.exe .\correct\in\haha.txt .\correct\out\haha.txt ha haha
fc .\correct\out\haha.txt .\correct\compare\haha.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo ---------- Result in begin of the word --------
echo replace.exe .\correct\in\begin_word.txt .\correct\out\begin_word.txt prop 123456
replace.exe .\correct\in\begin_word.txt .\correct\out\begin_word.txt prop 123456
fc .\correct\out\begin_word.txt .\correct\compare\begin_word.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo ----------- Result in end of the word ---------
echo replace.exe .\correct\in\end_word.txt .\correct\out\end_word.txt ties 123456
replace.exe .\correct\in\end_word.txt .\correct\out\end_word.txt ties 123456
fc .\correct\out\end_word.txt .\correct\compare\end_word.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo ----------- Result in begin of the file -------
echo replace.exe .\correct\in\begin_file.txt .\correct\out\begin_file.txt short 123456
replace.exe .\correct\in\begin_file.txt .\correct\out\begin_file.txt short 123456
fc .\correct\out\begin_file.txt .\correct\compare\begin_file.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo ------------- Result in end of the file -------
echo replace.exe .\correct\in\end_file.txt .\correct\out\end_file.txt choice 123456
replace.exe .\correct\in\end_file.txt .\correct\out\end_file.txt choice 123456
fc .\correct\out\end_file.txt .\correct\compare\end_file.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------

echo ************** End correct tests **************
echo ************ Start incorrect tests ************

echo ------------- Non existent in file ------------
echo replace.exe .\incorrect\in\non_existent.txt .\incorrect\out\non_existent.txt empty ######
replace.exe .\incorrect\in\non_existent.txt .\incorrect\out\non_existent.txt empty ######
echo --------------- Zero string find --------------
echo replace.exe .\incorrect\in\haha.txt .\incorrect\out\haha.txt "" haha
replace.exe .\incorrect\in\haha.txt .\incorrect\out\haha.txt "" haha
fc .\incorrect\out\haha.txt .\incorrect\compare\haha.txt
if errorlevel 1 (@echo !!!!!!!!!!!!!!!!!!!!Not Ok!!!!!!!!!!!!!!!!!!!!!) else echo ----------------------Ok-----------------------
echo ------------ Start with 3 parameters ----------
echo replace.exe .\incorrect\in\haha.txt .\incorrect\out\haha.txt haha
replace.exe .\incorrect\in\haha.txt .\incorrect\out\haha.txt haha
echo ------------ Start with 2 parameters ----------
echo replace.exe .\incorrect\in\haha.txt .\incorrect\out\haha.txt
replace.exe .\incorrect\in\haha.txt .\incorrect\out\haha.txt
echo ------------- Start with 1 parameter ----------
echo replace.exe .\incorrect\in\haha.txt
replace.exe .\incorrect\in\haha.txt
echo ----------- Start without parameters ----------
echo replace.exe
replace.exe

echo ************* End incorrect tests *************