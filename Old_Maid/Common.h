#pragma once
#include <Windows.h>

void MoveCursor(int x, int y)	// 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}