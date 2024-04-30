#pragma once
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <Windows.h>

#include "Player.h"
#include "Common.h"

void PrintHandCards(Player player)	// 손패 출력(앞면)
{
	int length = Length(player.hand);
	Node* temp = player.hand;
	int color;

	wchar_t* shape[4] = {	// 유니코드를 저장하기 위해 wchar_t 사용
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
		L"", // 모양
		L"      │",
		L"│ ",
		L"", // 숫자
		L"      │",
		L"│         │",
		L"│    ",
		L"", // 모양
		L"   │",
		L"│         │",
		L"│       ",
		L"", // 숫자
		L"│",
		L"│       ",
		L"", // 모양
		L"│",
		L"└─────────┘"
	};

	int x = (240 - (10 * length + ((length - 1) * 4))) / 2 - 1, y = 53; // 가운데 정렬을 위한 위치 계산(카드 : 10, 공백 : 4)
	// ((전체 길이 - ((카드 길이 * 카드 장수) + (공백 * 공백 수))) / 2 - 1
	COORD pos = { x, y };

	if (temp != NULL)
	{
		int num = temp->num;
		for (int i = 0; i < length; i++)
		{
			if ((num - 1) / 13 == 1 || (num - 1) / 13 == 2) // 색 설정
			{
				color = 4;
			}
			else
			{
				color = 7;
			}

			if (num != 0) // 카드 아스키 아트에 모양과 숫자 삽입
			{
				card[2] = card[9] = card[16] = shape[(num - 1) / 13];
				card[5] = card[13] = number[(num - 1) % 13];
			}
			else	// 조커
			{
				card[2] = card[9] = card[16] = L":P";
				card[5] = card[13] = L"  ";
			}

			MoveCursor(x, y);

			for (int j = 0; j < 19; j++)
			{
				if (j == 1 || j == 4 || j == 7 || j == 8 || j == 11 || j == 12 || j == 15 || j == 18) // 줄 바꿈
				{
					MoveCursor(x, ++y);
				}
				if (j == 2 || j == 5 || j == 9 || j == 13 || j == 16) // 색 변경
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				}
				printf("%S", card[j]);	// 출력
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			printf("\n");

			temp = temp->next;

			if (temp != NULL)
			{
				num = temp->num;
			}

			x += 14;	// 카드 1장 + 공백 만큼 옆으로 이동
			y = 53;	// 원래 위치로 이동
		}
	}
}

void PrintDrawHandCards(Player player)	// 내가 뽑을 손패 출력(뒷면)
{
	int length = Length(player.hand);
	Node* temp = player.hand;

	char* card[9] =
	{
		"┌─────────┐",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"└─────────┘"
	};
	int x = (240 - (10 * length + ((length - 1) * 4))) / 2 - 1, y = 42;
	COORD pos = { x, y };

	for (int i = 0; i < length; i++)
	{
		MoveCursor(x, y);

		for (int j = 0; j < 9; j++)
		{
			MoveCursor(x, y++);
			printf("%s\n", card[j]);
		}
		x += 14;
		y = 42;
	}
}

void PrintBackCards(Player player, int x, int y)	// 손패 출력(뒷면)
{
	int length = Length(player.hand);
	int tmp = x;
	char* card[9] =
	{
		"┌─────────┐",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"│ ▩▩▩▩│",
		"└─────────┘"
	};

	// 한 줄에 5개씩 출력
	for (int i = 0; i < (length - 1) / 5 + 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if ((i * 5) + j + 1 > length)
			{
				break;
			}
			for (int k = 0; k < 9; k++)
			{
				MoveCursor(x, y++);
				printf("%s\n", card[k]);
			}
			x += 14;
			y -= 9;
		}
		x = tmp;
		y += 10;
	}
}

void PrintSelector(Player player, int index)	// 가져올 카드를 고르는 셀렉터 출력
{
	int x = ((240 - (10 * Length(player.hand) + ((Length(player.hand) - 1) * 4))) / 2 - 1) + (14 * index);

	MoveCursor(x - 2, 41);
	printf("┌");
	MoveCursor(x + 12, 41);
	printf("┐");
	MoveCursor(x + 12, 51);
	printf("┘");
	MoveCursor(x - 2, 51);
	printf("└");
}

void RemoveSelector(Player player, int index)	// 셀렉터 삭제
{
	int x = ((240 - (10 * Length(player.hand) + ((Length(player.hand) - 1) * 4))) / 2 - 1) + 14 * index;

	MoveCursor(x - 2, 41);
	printf(" ");
	MoveCursor(x + 12, 41);
	printf(" ");
	MoveCursor(x + 12, 51);
	printf(" ");
	MoveCursor(x - 2, 51);
	printf(" ");
}