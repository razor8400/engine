cd ..
cd ..
cd ..
cd ..

xcopy "ThirdParty\freetype\win64\freetype.dll" "Test App\Build\Win32\x64\Debug" /Y
xcopy "ThirdParty\GLFW3\win64\glew32.dll" "Test App\Build\Win32\x64\Debug" /Y
xcopy "Test App\Assets" "Test App\Build\Win32\x64\Debug\Assets\" /Y /E /I