# Cross-platform Makefile for digit recognition project

# Linux version (using pkg-config for SDL2)
linux-run:
	gcc main.c -o app $$(pkg-config --cflags --libs sdl2) -lm && ./app
	
# Windows version (using MinGW with SDL2 development libraries)  
win-run:
	gcc main.c -o app.exe -I"C:\SDL2\SDL2-2.30.0\x86_64-w64-mingw32\include" -L"C:\SDL2\SDL2-2.30.0\x86_64-w64-mingw32\lib" -lmingw32 -lsdl2main -lsdl2 -lm
	copy "C:\SDL2\SDL2-2.30.0\x86_64-w64-mingw32\bin\SDL2.dll" . >nul 2>nul
	app.exe

# Clean up build artifacts
clean:
	rm -f app app.exe
	