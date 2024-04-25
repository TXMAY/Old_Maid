#pragma once
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <Windows.h>

#include "Player.h"
// 카드 모양은 2칸, 카드 테두리는 1칸

void PrintHandCards(Player player)
{
	int length = Length(player.hand);
	Node* temp = player.hand;
	int color;

	setlocale(LC_CTYPE, "");

	wchar_t* shape[4] =
	{
		L"♠",
		L"◆",
		L"♥",
		L"♣"
	};
	wchar_t* number[13] =
	{
		L"Ａ",
		L"２",
		L"３",
		L"４",
		L"５",
		L"６",
		L"７",
		L"８",
		L"９",
		L"10",
		L"Ｊ",
		L"Ｑ",
		L"Ｋ",

	};


	wchar_t* card[19] =
	{
		L"┌─────────┐",
		L"│ ",
		L"",	// 모양
		L"      │",
		L"│ ",
		L"",	// 숫자
		L"      │",
		L"│         │",
		L"│    ",
		L"",	// 모양
		L"   │",
		L"│         │",
		L"│       ",
		L"",	// 숫자
		L"│",
		L"│       ",
		L"",	// 모양
		L"│",
		L"└─────────┘"
	};

	// 이중 for문으로 연속 출력 하기
	// 1장 : 114, 2장 108

	int x = 120 - (5 * length + (length - 1 * 1)) - 1;	// 가운데 정렬을 위한 위치 계산(카드 한 장 : 10, 공백 : 2)
	COORD pos = { x, 0 };

	if (temp != NULL)
	{
		int num = temp->num;
		for (int i = 0; i < length; i++)
		{
			if ((num - 1) / 13 == 1 || (num - 1) / 13 == 2)	// 색 설정
			{
				color = 4;
			}
			else
			{
				color = 7;
			}

			pos.Y = 57;
			if (num != 0)	// 카드 아스키 아트에 모양과 숫자 삽입
			{
				card[2] = card[9] = card[16] = shape[(num - 1) / 13];
				card[5] = card[13] = number[(num - 1) % 13];
			}
			else
			{
				card[2] = card[9] = card[16] = L":P";
				card[5] = card[13] = L"  ";
			}

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			for (int j = 0; j < 19; j++)
			{
				if (j == 1 || j == 4 || j == 7 || j == 8 || j == 11 || j == 12 || j == 15 || j == 18)	// 줄 바꿈
				{
					pos.Y++;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				}
				if (j == 2 || j == 5 || j == 9 || j == 13 || j == 16)	// 색 변경
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				}
				printf("%S", card[j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			temp = temp->next;

			if (temp != NULL)
			{
				num = temp->num;
			}
			pos.X += 12;	// 카드 1장 + 공백 만큼 옆으로 이동
		}
	}
	//printf("\n");
	/*for (int i = 1; i <= 240; i++)
	{
		printf("%d", i % 10);
	}*/
	/*printf("┌─────────┐\n");
	printf("│ ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%C", shape[(num - 1) / 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("      │ \n");
	printf("│ ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%S", number[(num - 1) % 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("      │\n");
	printf("│         │\n");
	printf("│    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%C", shape[(num - 1) / 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("   │\n");
	printf("│         │\n");
	printf("│       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%S", number[(num - 1) % 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("│\n");
	printf("│       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%C", shape[(num - 1) / 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("│\n");
	printf("└─────────┘");*/
	//printf("%d %d\n", length, x);
}
