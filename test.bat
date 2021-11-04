@echo off

echo "用法：.\test.bat <源文件不带扩展名>"
echo "例如：.\test.bat hello"

.\make.bat %1 && .\%1.exe