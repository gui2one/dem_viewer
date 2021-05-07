@REM call .\build__clean.bat
@REM cmake -B ./build -S .
del .\build\Release\dem_viewer.exe
cmake --build ./build --config Release -j4
cd build/Release
dem_viewer.exe