@REM call .\build__clean.bat
@REM cmake -B ./build -S .
@REM del .\build\Release\dem_viewer.exe
cmake --build ./build --config Release
cd build/Release
dem_viewer.exe