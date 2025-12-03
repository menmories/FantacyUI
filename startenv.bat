mkdir build
cd build
::cmake ../ -G "Visual Studio 15 2017" -A x64
cmake ../ -G "Visual Studio 17 2022" -A x64
::set path="E:\Qt\Qt5.12.12\5.12.12\msvc2017_64\bin" /M
::"D:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" /useenv "kplayer.sln"
::"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe" "kplayer.sln"
cd ..
::pause
