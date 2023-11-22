#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void font_colour(short int colour){
    /*
        (rgb) 100 -> (255,0,0)   rojo
        (rgb) 010 -> (0,255,0)   verde
        (rgb) 001 -> (0,0,255)   azul
        (rgb) 110 -> (255,255,0) amarillo
        (rgb) 011 -> (0,255,255) cyan
        (rgb) 000 -> (0,0,0)     negro
    */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (colour) {
    case 100: // red
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    case 010: // green
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case 001: // blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case 110: // yellow
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case 011: // cyan
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case 111: // white
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
        break;
    default:
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }
}

int main() {
    const short int red=100, green=010, blue=001, yellow=110, cyan=011, original=111;

    return 0;
}
