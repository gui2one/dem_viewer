@REM call .\build__clean.bat
@REM cmake -B ./build -S .
del .\build\Release\starter_project.exe
cmake --build ./build --config Release
cd build/Release
starter_project.exe