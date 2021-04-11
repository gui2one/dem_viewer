@REM call .\build__clean.bat
@REM cmake -B ./build -S .
del .\build\Debug\starter_project.exe
cmake --build ./build --config Debug
cd build/Debug
starter_project.exe