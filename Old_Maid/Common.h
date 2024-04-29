#pragma once
#define LEFT 75
#define RIGHT 77

#include <Windows.h>

int index;

Player player1;
Player player2;
Player player3;
Player player4;

Player* players[4];

void MoveCursor(int x, int y)	// 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}