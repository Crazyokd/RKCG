@echo off

echo "用法：.\make.bat <源文件不带扩展名>"
echo "例如：.\make.bat hello"

g++ -fdiagnostics-color=always ^
    -g %1.cpp ^
    -o %1.exe ^
    -I include ^
    -L lib ^
    -lgraphics64 ^
    -luuid ^
    -lmsimg32 ^
    -lgdi32 ^
    -limm32 ^
    -lole32 ^
    -loleaut32 ^
    -lwinmm ^
    -lgdiplus ^