#include <stdio.h>
#include <Windows.h>

#include "Game.h"
#include "Card.h"

int main(void)
{
	// 전체화면 설정
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode con:cols=240 lines=67");

	// 마우스 입력 방지
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevMode = GetConsoleMode(hInput, &prevMode);

	SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO cursor = {
		0,
	};
	cursor.dwSize = 1;
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	// 유니코드를 출력하기 위한 지역 설정
	setlocale(LC_CTYPE, ""); // 컴퓨터 시스템 지역으로 설정

	PrintMain();
	while (1)
	{
		PlayGame();
	}
	return 0;
}