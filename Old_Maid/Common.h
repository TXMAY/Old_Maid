#pragma once
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#include <Windows.h>

int index;	// ���� ���� ����
int flagPause;	// �Ͻ� ���� Ȯ�� ����

int card[53] = { 0, }; // ī�带 ������ ��, �ߺ� ������ ���� ���� ī�带 ����ϴ� �迭
// 0 : ��Ŀ
// 1 ~ 13 : �����̵� A ~ 13
// 14 ~ 26 : ���̾� A ~ 13
// 27 ~ 39 : ��Ʈ A ~ 13
// 40 ~ 52 : Ŭ�ι� A ~ 13


Player player1;
Player player2;
Player player3;
Player player4;

Player* players[4];

void MoveCursor(int x, int y)	// Ŀ�� �̵�
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}