#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define enter 13
#define isExtended -32
#define up 72
#define down 80
#define home 71
#define end 79

#define row 10
#define col 35

#define black 0
#define blue 1
#define green 2
#define cyan 3
#define red 4
#define magenta 5
#define brown 6
#define lightgray 7
#define darkgray 8
#define lightblue 9
#define lightgreen 10
#define lightcyan 11
#define lightred 12
#define lightmagenta 13
#define yellow 14
#define white 15


#define lightcyan 11

#define brown 6

//#define loop 1
#define true 1
#define false 0

void SetColor(int ForgC){
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
void gotoxy(int x,int y){
   COORD coord={0,0};
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
