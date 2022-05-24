@echo off
mkdir ..\..\build
pushd ..\..\build
cl -Zi ..\game-project\code\win32_kalevalapeli.cpp user32.lib Gdi32.lib
popd
