#pragma once
#include <stdlib.h>
#include <time.h>

#include "Player.h"

Player player1;
Player player2;
Player player3;
Player player4;

int card[53] = { 0, }; // 카드를 나눠줄 때, 중복 방지를 위해 뽑은 카드를 등록하는 배열
// 0 : 조커
// 1 ~ 13 : 스페이드 A ~ 13
// 14 ~ 26 : 다이아 A ~ 13
// 27 ~ 39 : 하트 A ~ 13
// 40 ~ 52 : 클로버 A ~ 13

void Init()
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

	// 다음 플레이어 설정
	player1.nextPlayer = &player2;
	player2.nextPlayer = &player3;
	player3.nextPlayer = &player4;
	player4.nextPlayer = &player1;
} // 손패 설정(4번이 14장)

void PrintCards(Node* head)
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
			printf("%d ", head->num % 13 + 1);
		}
		head = head->next;
	}
	printf("\n");
}

void RemoveCard(Node** head)
{
	int count[14] = { 0 };
	int index = 0;
	Node* current = *head;
	Node* prev = NULL;


	while (current != NULL)
	{
		index = current->num % 13 + 1;
		count[index]++;
		current = current->next;
	}

	current = *head;
	while (current != NULL)
	{
		index = current->num % 13 + 1;
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
}

int DrawCard(Node** head, int index)
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
			prev->next = temp->next;
			num = temp->num;
			free(temp);
		}
	}
	return num;
} // 현재 오류 발생