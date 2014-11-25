///////////////////////////////////////////////////////////////////
///*SNAKE*/ v 1.0
//CONSOLE GAME
//written by Marcin Chudy
//04.2012
//**********************
//Features:
// --4 difficulty levels
// --Highscores
//works on Windows only(several WINAPI functions have been used)
////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>
#include <string>
#include "Snake.h"
#include "Board.h"
#include "Game.h"
using namespace std;

void cls()
{
	DWORD n;                         
	DWORD size;                     
	COORD coord = {0};               
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo ( h, &csbi );
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
	GetConsoleScreenBufferInfo ( h, &csbi );
	FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
	SetConsoleCursorPosition ( h, coord );
}

void SetColour(int colour)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, colour);
}

int main()
{
	CGame Game;
	while(1)
	{
		int decision = Game.Menu();
		if(decision == 1)
			Game.Play();
		else if(decision == 2)
			Game.ShowHighscore();
		else if(decision == 3)
			Game.SetDifficulty();
		else break;
	}
	return 0;
}
