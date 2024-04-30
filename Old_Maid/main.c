#include <stdio.h>
#include <Windows.h>

#include "Game.h"
#include "Card.h"

int main(void)
{
	// ��üȭ�� ����
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode con:cols=240 lines=67");

	// ���콺 �Է� ����
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevMode = GetConsoleMode(hInput, &prevMode);

	SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);

	// Ŀ�� �����
	CONSOLE_CURSOR_INFO cursor = {
		0,
	};
	cursor.dwSize = 1;
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	// �����ڵ带 ����ϱ� ���� ���� ����
	setlocale(LC_CTYPE, ""); // ��ǻ�� �ý��� �������� ����

	PrintMain();
	while (1)
	{
		PlayGame();
	}
	return 0;
}