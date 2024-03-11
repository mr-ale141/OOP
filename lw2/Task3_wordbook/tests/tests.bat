echo off
chcp 65001
copy ..\x64\Debug\bookword.exe bookword.exe
copy in\smoke.txt out\smoke.txt
bookword.exe out\smoke.txt <in\smoke_cmd.txt
fc out\smoke.txt compare\smoke.txt
