cd ..
cd ..
cd ..
cd ..

xcopy "ThirdParty\freetype\win64\freetype.dll" ""Editor\Build\Win32\x64\Debug" /Y
xcopy "ThirdParty\GLFW3\win64\glew32.dll" ""Editor\Build\Win32\x64\Debug" /Y
xcopy "Editor\Assets" ""Editor\Build\Win32\x64\Debug\Assets\" /Y /E /I