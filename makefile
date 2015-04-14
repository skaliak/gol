#Detect OS
UNAME := $(shell uname)

# Build based on OS name
DetectOS:
	make $(UNAME)

Linux: main.cpp cell.cpp Point.cpp Warden.cpp
	g++ -std=c++0x main.cpp cell.cpp Point.cpp Warden.cpp -o Life.o -lncurses

Darwin: main.cpp cell.cpp Point.cpp Warden.cpp
	g++ main.cpp cell.cpp Point.cpp Warden.cpp -o Life.o -lncurses

Windows32: main.cpp cell.cpp Point.cpp Warden.cpp
	g++ -std=c++0x main.cpp cell.cpp Point.cpp Warden.cpp -o Life.exe -lpdcurses
