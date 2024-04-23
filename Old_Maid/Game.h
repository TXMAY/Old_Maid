#pragma once
#include <stdlib.h>
#include <time.h>

#include "Player.h"

Player player1;
Player player2;
Player player3;
Player player4;

Player players[4];

int card[53] = { 0, };	// 카드를 나눠줄 때, 중복 방지를 위해 뽑은 카드를 등록하는 배열
// 0 : 조커
// 1 ~ 13 : 스페이드 A ~ 13
// 14 ~ 26 : 다이아 A ~ 13
// 27 ~ 39 : 하트 A ~ 13
// 40 ~ 52 : 클로버 A ~ 13

void Init()	// 기본 설정
{
	player1.hand = NULL;
	player2.hand = NULL;
	player3.hand = NULL;
	player4.hand = NULL;

	srand(time(NULL));

	int i = 0;
	int tmp = 0;

	// 손패 뽑기
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53;
		if (card[tmp] == 0)
		{
			Insert(&player1.hand, tmp);
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53;
		if (card[tmp] == 0)
		{
			Insert(&player2.hand, tmp);
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53;
		if (card[tmp] == 0)
		{
			Insert(&player3.hand, tmp);
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53;
		if (card[tmp] == 0)
		{
			Insert(&player4.hand, tmp);
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}
	for (i = 0; i < 53; i++)
	{
		if (card[i] == 0)
		{
			Insert(&player4.hand, i);
			break;
		}
	}

	// 내가 카드를 뽑아올 플레이어 설정 (뽑는 순서는 1 -> 2 -> 3 -> 4 -> 1...)
	player1.prevPlayer = &player4;
	player2.prevPlayer = &player1;
	player3.prevPlayer = &player2;
	player4.prevPlayer = &player3;

	// 손패 설정(4번이 14장)
	player1.nextPlayer = &player2;
	player2.nextPlayer = &player3;
	player3.nextPlayer = &player4;
	player4.nextPlayer = &player1;

	players[0] = player1;
	players[1] = player2;
	players[2] = player3;
	players[3] = player4;
}

//void PrintCard(int num)	// 숫자에 따른 카드 출력
//{
//	if (num == 0)
//	{
//		printf("조커 ");
//	}
//	else
//	{
//		switch ((num - 1) / 13)
//		{
//		case 0:
//			printf("♠");
//			break;
//		case 1:
//			printf("◆");
//			break;
//		case 2:
//			printf("♥");
//			break;
//		case 3:
//			printf("♣");
//			break;
//		}
//		printf("%d ", (num - 1) % 13 + 1);
//	}
//	printf("\n");
//}

void PrintCards(Node* head)	// 들고 있는 카드 패 출력
{
	while (head != NULL)
	{
		if (head->num == 0)
		{
			printf("조커 ");
		}
		else
		{
			switch ((head->num - 1) / 13)
			{
			case 0:
				printf("♠");
				break;
			case 1:
				printf("◆");
				break;
			case 2:
				printf("♥");
				break;
			case 3:
				printf("♣");
				break;
			}
			printf("%d ", (head->num - 1) % 13 + 1);
		}
		head = head->next;
	}
	printf("\n");
}

void RemoveCard(Node** head)	// 숫자가 같은 카드 2장 또는 4장 제거
{
	int count[14] = { 0 };
	int index = 0;
	Node* current = *head;
	Node* prev = NULL;

	while (current != NULL)
	{
		index = (current->num - 1) % 13 + 1;
		count[index]++;
		current = current->next;
	}

	/*for (int i = 0; i < 14; i++)
	{
		printf("%d ", count[i]);
	}
	printf("\n");*/

	current = *head;
	while (current != NULL)
	{
		index = (current->num - 1) % 13 + 1;
		if (count[index] == 2 || count[index] == 3)
		{
			if (count[index] == 3)
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

	/*for (int i = 0; i < 14; i++)
	{
		printf("%d ", count[i]);
	}
	printf("\n");*/
}

int DrawCard(Node** head, int index)	// 다른 플레이어가 들고 있는 카드 뽑기(1 ~ n)
{
	Node* temp = *head;
	Node* prev = NULL;
	int num = 0;
	int count = 1;

	if (index == 1)
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

void RemovePlayer(Player player)	// 패가 0장이 된 플레이어 게임에서 제외
{
	if (Length(player.hand) == 0 && (player.prevPlayer != NULL || player.nextPlayer != NULL))
	{
		player.prevPlayer->nextPlayer = player.nextPlayer;
		player.nextPlayer->prevPlayer = player.prevPlayer;
		player.prevPlayer = NULL;
		player.nextPlayer = NULL;
	}
}

int GameEnd(Player player)	// 게임 종료
{
	if (player.prevPlayer != NULL && player.nextPlayer != NULL)
	{
		return (&player == player.prevPlayer) && (&player == player.nextPlayer);
	}
}