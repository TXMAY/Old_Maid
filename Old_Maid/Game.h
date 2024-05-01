#pragma once
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>
#include <conio.h>

#include "Player.h"
#include "Common.h"
#include "Card.h"

void Init() // 기본 설정
{
	// 배열에 진행할 순서대로 플레이어 넣기
	players[0] = &player1;
	players[1] = &player2;
	players[2] = &player3;
	players[3] = &player4;

	// 손패 초기화
	for (int i = 0; i < 4; i++)
	{
		players[i]->hand = NULL;
	}

	//이름 설정
	player1.name = "Player 1";
	player2.name = "Player 2";
	player3.name = "Player 3";
	player4.name = "Player 4";

	srand(time(NULL));

	int tmp = 0;

	// 손패 뽑기
	for (int i = 0; i < 53; i++)
	{
		card[i] = 0;
	}

	// 뽑은 카드는 중복 뽑기를 방지하기 위해 배열에 저장
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
	// 뽑지 않은 카드 한 장을 4번째 플레이어에 패에 추가
	for (int i = 0; i < 53; i++)
	{
		if (card[i] == 0)
		{
			Insert(&player4.hand, i);
			break;
		}
	}

	// 내가 카드를 뽑아올 플레이어 설정
	player1.drawPlayer = &player4;
	player2.drawPlayer = &player1;
	player3.drawPlayer = &player2;
	player4.drawPlayer = &player3;
}

void RemoveCard(Node **head) // 숫자가 같은 카드 2장 또는 4장 제거
{
	int count[14] = {0};
	int index = 0;
	Node *current = *head;
	Node *prev = NULL;

	while (current != NULL) // 같은 숫자를 몇 장 가지고 있는지 확인
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
			if (count[index] == 3) // 숫자가 같은 카드를 3장 가지고 있으면 첫 카드만 남기고 나머지 2장 제거
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
				Node *temp = current;
				current = current->next;
				free(temp);
				continue;
			}
		}
		prev = current;
		current = current->next;
	}
}

int DrawCard(Node **head, int index) // 다른 플레이어가 들고 있는 카드 뽑기
{
	Node *temp = *head;
	Node *prev = NULL;
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

void RemovePlayer(Player *player) // 내가 손패를 뽑을 플레이어의 손패가 0장이면 손패를 뽑을 플레이어를 변경
{
	while (Length(player->drawPlayer->hand) == 0)
	{
		player->drawPlayer = player->drawPlayer->drawPlayer;
	}
}

int GameEnd(Player *player) // 게임 종료
{
	return player == player->drawPlayer; // 플레이어와 카드를 뽑아올 플레이어가 같은지 확인
}

void PrintLines() // 선 출력(x : 14 ~ 224, y : 4 ~ 62)
{
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
					if (j == 14)
						printf("├");
					else if (j == 224)
						printf("┤");
					else
						printf("─");
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

void PrintInfo(int option) // 플레이어 이름과 게임 상태 출력, 0 : 카드 선택 메세지, 1 ~ 3: 다른 플레이어 턴 메세지
{
	MoveCursor(46, 6);
	printf("%s", player2.name);
	MoveCursor(116, 6);
	printf("%s", player3.name);
	MoveCursor(186, 6);
	printf("%s", player4.name);

	if (option == 0)
	{
		MoveCursor(113, 39);
		printf("Draw the card");
	}
	else
	{
		MoveCursor(110, 39);
		printf("%s's turn...", players[option]->name);
	}
}

void PrintGameScreen(int option)	// 게임 화면(선, 내 손패, 상대 손패, 이름 및 현재 상황) 출력
{
	system("cls");
	PrintLines();
	PrintHandCards(player1);
	PrintBackCards(player2, 16, 8);
	PrintBackCards(player3, 86, 8);
	PrintBackCards(player4, 156, 8);
	PrintInfo(option);
}

void PrintPauseMenu()	// 일시 정지 메뉴 출력
{
	char key;
	int option = 0, x = 105, y = 18;
	char *pause[5] =
		{
			"####    #   #  #  ###  #####",
			"#   #  # #  #  # #     #",
			"####   ###  #  #  ###  #####",
			"#     #   # #  #     # #",
			"#     #   #  ##   ###  #####"};
	if (flagPause)
	{
		system("cls");
		PrintLines();
		for (int i = 0; i < 5; i++)
		{
			MoveCursor(x, y++);
			printf("%s", pause[i]);
		}
		MoveCursor(113, y + 2);
		printf("▶");
		MoveCursor(117, y + 2);
		printf("Resume");
		MoveCursor(117, y + 4);
		printf("Exit");
	}
	while (flagPause)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 10 || key == 13)
			{
				switch (option)
				{
				case 0:	// 일시 정지 해제
					flagPause = !flagPause;
					PrintGameScreen(0);
					/*system("cls");
					PrintLines();
					PrintHandCards(player1);
					PrintBackCards(player2, 16, 8);
					PrintBackCards(player3, 86, 8);
					PrintBackCards(player4, 156, 8);*/
					PrintDrawHandCards(*player1.drawPlayer);
					//PrintInfo(0);
					break;
				case 1:	// 게임 종료
					exit(1);
					break;
				}
			}
			if (key == -32)	// 위아래 방향키로 옵션 변경
			{
				key = _getch();
				MoveCursor(113, y + (2 * (option + 1)));
				switch (key)
				{
				case UP:
					option--;
					break;
				case DOWN:
					option++;
					break;
				}
				if (option < 0)
				{
					option = 1;
				}
				if (option > 1)
				{
					option = 0;
				}
				printf("　");
				MoveCursor(113, y + (2 * (option + 1)));
				printf("▶");
			}
		}
	}
}

void SelectCard(Player player, int length) // 뽑아올 카드 선택
{
	char key;
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 122) // z키의 ASCII 코드는 122
			{
				break;
			}
			if (key == 27)
			{
				flagPause = !flagPause;
			}
			PrintPauseMenu();
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
				if (index < 0) // 인덱스 초과 방지
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

void EndGame(int win)	// 게임 종료
{
	char key;
	int option = 0, x = 116, y = 18;

	system("cls");
	PrintLines();

	MoveCursor(x, y);
	if (win != 0)	// 마지막에 조커를 가지고 있으면 패배, 그 전에 패를 모두 버리면 승리
	{
		printf("You Win!");
	}
	else
	{
		printf("You Lose");
	}

	MoveCursor(113, y + 2);
	printf("▶");
	MoveCursor(117, y + 2);
	printf("Restart");
	MoveCursor(117, y + 4);
	printf("Exit");

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 10 || key == 13)
			{
				if (option == 0)	// 다시하기
				{
					break;
				}
				else	// 종료
				{
					exit(1);
				}
			}
			if (key == -32)
			{
				key = _getch();
				MoveCursor(113, y + (2 * (option + 1)));
				switch (key)
				{
				case UP:
					option--;
					break;
				case DOWN:
					option++;
					break;
				}
				if (option < 0)
				{
					option = 1;
				}
				if (option > 1)
				{
					option = 0;
				}
				printf("　");
				MoveCursor(113, y + (2 * (option + 1)));
				printf("▶");
			}
		}
	}
}

void PrintMain()	// 메인 화면 출력
{
	PrintLines();
	char key;
	int x = 97, y = 18;
	char *title[5] =
		{
			" ###  #     ####    #   #   #   ##### ####",
			"#   # #     #   #   ## ##  # #    #   #   #",
			"#   # #     #   #   # # #  ###    #   #   #",
			"#   # #     #   #   #   # #   #   #   #   #",
			" ###  ##### ####    #   # #   # ##### ####"};
	for (int i = 0; i < 5; i++)
	{
		MoveCursor(x, y++);
		printf("%s", title[i]);
	}
	MoveCursor(110, y + 4);
	printf("Press Enter to Begin");

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 10 || key == 13)
				break;
		}
	}
}

void PlayGame()
{
	int i = 0;
	Init();

	for (int i = 0; i < 4; i++)
	{
		RemoveCard(&players[i]->hand);
	}
	for (int i = 0; i < 4; i++)
	{
		RemovePlayer(players[i]);
	}

	while (1)
	{
		PrintGameScreen(i);

		if (Length(players[i]->hand))
		{
			//MoveCursor(0, 0);
			RemovePlayer(players[i]); // 플레이어 제거
			if (GameEnd(players[i]))  // 게임 종료 조건 충족 시 정지
			{
				break;
			}
			if (i == 0)
			{
				index = 0;
				PrintDrawHandCards(*players[i]->drawPlayer);									 // 손패 가져올 플레이어의 손패 출력
				SelectCard(*players[i]->drawPlayer, Length(players[i]->drawPlayer->hand));		 // 가져올 손패 선택
				InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, index)); // 손패 가져옴
			}
			else
			{
				index = rand() % Length(players[i]->drawPlayer->hand);							 // 가져올 손패 선택
				Sleep(1000);																	 // 생각 중(인 것처럼 보이게 하기)
				InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, index)); // 손패 가져옴
			}
			printf("\n");
			PrintGameScreen(i); // 가져온 후 손패 표시
			Sleep(1000);
			RemoveCard(&players[i]->hand); // 카드 제거
			PrintGameScreen(i);			   // 제거한 후 손패 표시
			Sleep(1000);
		}
		i++;
		if (i > 3)
		{
			i = 0;
		}
	}
	EndGame(i);
}