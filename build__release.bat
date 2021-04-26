@REM call .\build__clean.bat
@REM cmake -B ./build -S .
del .\build\Release\starter_project.exe
cmake --build ./build --config Release
cd build/Release
starter_project.exe C:/gui2one/CODE/DEM_files/F44/N20E080.hgt