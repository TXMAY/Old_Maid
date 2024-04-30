#pragma once
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#include <Windows.h>

int index;	// 손패 선택 변수
int flagPause;	// 일시 정지 확인 변수

int card[53] = { 0, }; // 카드를 나눠줄 때, 중복 방지를 위해 뽑은 카드를 등록하는 배열
// 0 : 조커
// 1 ~ 13 : 스페이드 A ~ 13
// 14 ~ 26 : 다이아 A ~ 13
// 27 ~ 39 : 하트 A ~ 13
// 40 ~ 52 : 클로버 A ~ 13


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