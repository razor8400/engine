cd ..
cd ..
cd ..

xcopy "ThirdParty\GLFW3\win32\glew32.dll" "Test App\Build\Win32\Debug" /Y
xcopy "Test App\Assets" "Test App\Build\Win32\Debug\Assets\" /Y /E /I