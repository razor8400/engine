cd ..
cd ..
cd ..
cd ..

xcopy "ThirdParty\freetype\win32\freetype.dll" ""Editor\Build\Win32\Debug" /Y
xcopy "ThirdParty\GLFW3\win32\glew32.dll" ""Editor\Build\Win32\Debug" /Y
xcopy "Editor\Assets" ""Editor\Build\Win32\Debug\Assets\" /Y /E /I