#include <stdio.h>
#include <Windows.h>

#include "Game.h"
#include "Card.h"

int main(void)
{
	// 전체화면 설정(함수가 32비트(x86)전용이라 디버깅 모드를 x86으로 설정해야 함)
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode con:cols=237 lines=67");

	// 폰트 및 폰트 크기 설정
	COORD fontSize = { 8, 16 };	// 폰트 폭 및 너비(굴림체 16pt 기준)
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;	// 0번 폰트를 기본으로 사용
	cfi.dwFontSize = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, LF_FACESIZE, L"굴림체");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	// 마우스 입력 방지
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevMode = GetConsoleMode(hInput, &prevMode);

	SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO cursor = { 0, };
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