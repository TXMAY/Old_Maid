#pragma once
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>

#include <conio.h>

#include "Player.h"
#include "Common.h"
#include "Card.h"

int card[53] = { 0, }; // 카드를 나눠줄 때, 중복 방지를 위해 뽑은 카드를 등록하는 배열
// 0 : 조커
// 1 ~ 13 : 스페이드 A ~ 13
// 14 ~ 26 : 다이아 A ~ 13
// 27 ~ 39 : 하트 A ~ 13
// 40 ~ 52 : 클로버 A ~ 13

void Init() // 기본 설정
{
	// 전체화면 설정
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode con:cols=240 lines=67");

	// 마우스 입력 방지
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevMode = GetConsoleMode(hInput, &prevMode);

	SetConsoleMode(hInput, prevMode & ~ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO cursor = { 0, };
	cursor.dwSize = 1;
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	// 유니코드를 출력하기 위한 설정
	setlocale(LC_CTYPE, "");

	players[0] = &player1;
	players[1] = &player2;
	players[2] = &player3;
	players[3] = &player4;

	player1.hand = NULL;
	player2.hand = NULL;
	player3.hand = NULL;
	player4.hand = NULL;

	player1.name = "Player1";
	player2.name = "Player2";
	player3.name = "Player3";
	player4.name = "Player4";

	srand(time(NULL));

	int tmp = 0;

	// 손패 뽑기

	for (int i = 0; i < 53; i++)
	{
		if (card[i] == 0)
		{
			Insert(&player4.hand, i);
			break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			tmp = rand() % 53;
			if (card[tmp] == 0)
			{
				Insert(&players[i]->hand, tmp);
				card[tmp] = 1;
			}
			else
			{
				j--;
			}
		}
	}

	// 내가 카드를 뽑아올 플레이어 설정
	player1.drawPlayer = &player4;
	player2.drawPlayer = &player1;
	player3.drawPlayer = &player2;
	player4.drawPlayer = &player3;

}

void RemoveCard(Node** head) // 숫자가 같은 카드 2장 또는 4장 제거
{
	int count[14] = { 0 };
	int index = 0;
	Node* current = *head;
	Node* prev = NULL;

	while (current != NULL)	// 같은 숫자를 몇 장 가지고 있는지 확인
	{
		index = (current->num - 1) % 13 + 1;
		count[index]++;
		current = current->next;
	}

	current = *head;
	while (current != NULL)
	{
		index = (current->num - 1) % 13 + 1;
		if (count[index] > 1)
		{
			if (count[index] == 3)	// 숫자가 같은 카드를 3장 가지고 있으면 첫 카드만 남기고 나머지 2장 제거
			{
				count[index]--;
			}
			else
			{
				if (prev == NULL)
				{
					*head = current->next;
				}
				else
				{
					prev->next = current->next;
				}
				Node* temp = current;
				current = current->next;
				free(temp);
				continue;
			}
		}
		prev = current;
		current = current->next;
	}
}

int DrawCard(Node** head, int index) // 다른 플레이어가 들고 있는 카드 뽑기
{
	Node* temp = *head;
	Node* prev = NULL;
	int num = 0;
	int count = 0;

	if (index == 0)
	{
		if (temp != NULL)
		{
			*head = temp->next;
			num = temp->num;
			free(temp);
		}
	}
	else
	{
		while (temp != NULL && count < index)
		{
			prev = temp;
			temp = temp->next;
			count++;
		}
		if (temp != NULL)
		{
			if (prev != NULL)
			{
				prev->next = temp->next;
			}
			num = temp->num;
			free(temp);
		}
	}
	return num;
}

void RemovePlayer(Player player) // 패가 0장이 된 플레이어 게임에서 제외
{
	if (Length(player.drawPlayer->hand) == 0)
	{
		player.drawPlayer = player.drawPlayer->drawPlayer;
	}
}

int GameEnd(Player player) // 게임 종료
{
	return &player == player.drawPlayer;	// 플레이어와 카드를 뽑아올 플레이어가 같은지 확인
}

void PrintLines()	// 선 출력(x : 14 ~ 224, y : 4 ~ 62)
{
	int divide = 2;
	//MoveCursor(14, 5);
	for (int i = 4; i < 63; i++)
	{
		MoveCursor(14, i);
		if (i != 4 && i != 37 && i != 52 && i != 62)
		{
			printf("│");
			if (i < 38)
			{
				MoveCursor(84, i);
				printf("│");
				MoveCursor(154, i);
				printf("│");
			}
			MoveCursor(224, i);
			printf("│");
		}
		else
		{
			for (int j = 14; j < 225; j++)
			{
				if (i == 4 || i == 37 || i == 52 || i == 62)
				{
					if (j == 14) printf("├");
					else if (j == 224) printf("┤");
					else printf("─");
				}
			}
		}
	}
	MoveCursor(14, 4);
	printf("┌");
	MoveCursor(224, 4);
	printf("┐");
	MoveCursor(224, 62);
	printf("┘");
	MoveCursor(14, 62);
	printf("└");
	MoveCursor(84, 4);
	printf("┬");
	MoveCursor(154, 4);
	printf("┬");
	MoveCursor(84, 37);
	printf("┴");
	MoveCursor(154, 37);
	printf("┴");
}

void SelectCard(Player player, int length)	// 뽑아올 카드 선택
{
	char key;
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 10 || key == 13)	// Enter키의 ASCII 코드는 10(LF) 또는 13(CR)
			{
				break;
			}
			if (key == -32)
			{
				RemoveSelector(player, index);
				key = _getch();
				switch (key)
				{
				case LEFT:
					index--;
					break;
				case RIGHT:
					index++;
					break;
				}
				if (index < 0)	// 인덱스 초과 방지
				{
					index = length - 1;
				}
				else if (index > length - 1)
				{
					index = 0;
				}
			}
		}
		PrintSelector(player, index);
	}
}

void PlayeGame()
{


	int i = 0;
	Init();

	RemoveCard(&player1.hand);
	RemoveCard(&player2.hand);
	RemoveCard(&player3.hand);
	RemoveCard(&player4.hand);

	RemovePlayer(player1);
	RemovePlayer(player2);
	RemovePlayer(player3);
	RemovePlayer(player4);

	while (1)
	{
		MoveCursor(0, 0);

		MoveCursor(47, 6);
		printf("playerx");
		MoveCursor(113, 39);
		printf("Draw the card");

		PrintLines();
		PrintHandCards(player1);
		PrintBackCards(player2, 16, 8);
		PrintBackCards(player3, 86, 8);
		PrintBackCards(player4, 156, 8);

		if (Length(players[i]->hand))
		{
			if (i == 0)
			{
				index = 0;
				PrintDrawHandCards(*players[i]->drawPlayer);
				SelectCard(*players[i]->drawPlayer, Length(players[i]->drawPlayer->hand));
				InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, index));
				PrintHandCards(player1);
				Sleep(1000);
			}
			else
			{
				index = rand() % Length(players[i]->drawPlayer->hand);
				Sleep(1000);
				InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, index));
			}
			RemoveCard(&players[i]->hand);
			RemovePlayer(*players[i]);
		}
		i++;
		if (i > 3) i = 0;
		system("cls");
	}
}