#pragma once
#include <Windows.h>

void MoveCursor(int x, int y)	// Ŀ�� �̵�
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}