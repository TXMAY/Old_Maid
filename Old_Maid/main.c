#include <stdio.h>
#include <Windows.h>

#include "Game.h"
#include "Card.h"

int main(void)
{
	// ��üȭ�� ����(�Լ��� 32��Ʈ(x86)�����̶� ����� ��带 x86���� �����ؾ� ��)
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode con:cols=237 lines=67");

	// ��Ʈ �� ��Ʈ ũ�� ����
	COORD fontSize = { 8, 16 };	// ��Ʈ �� �� �ʺ�(����ü 16pt ����)
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;	// 0�� ��Ʈ�� �⺻���� ���
	cfi.dwFontSize = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, LF_FACESIZE, L"����ü");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	// ���콺 �Է� ����
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevMode = GetConsoleMode(hInput, &prevMode);

	SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);

	// Ŀ�� �����
	CONSOLE_CURSOR_INFO cursor = { 0, };
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