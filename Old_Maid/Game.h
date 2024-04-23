#pragma once
#include <stdlib.h>
#include <time.h>

#include "Player.h"

Player player1;
Player player2;
Player player3;
Player player4;

Player players[4];

int card[53] = { 0, };	// ī�带 ������ ��, �ߺ� ������ ���� ���� ī�带 ����ϴ� �迭
// 0 : ��Ŀ
// 1 ~ 13 : �����̵� A ~ 13
// 14 ~ 26 : ���̾� A ~ 13
// 27 ~ 39 : ��Ʈ A ~ 13
// 40 ~ 52 : Ŭ�ι� A ~ 13

void Init()	// �⺻ ����
{
	player1.hand = NULL;
	player2.hand = NULL;
	player3.hand = NULL;
	player4.hand = NULL;

	srand(time(NULL));

	int i = 0;
	int tmp = 0;

	// ���� �̱�
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

	// ���� ī�带 �̾ƿ� �÷��̾� ���� (�̴� ������ 1 -> 2 -> 3 -> 4 -> 1...)
	player1.prevPlayer = &player4;
	player2.prevPlayer = &player1;
	player3.prevPlayer = &player2;
	player4.prevPlayer = &player3;

	// ���� ����(4���� 14��)
	player1.nextPlayer = &player2;
	player2.nextPlayer = &player3;
	player3.nextPlayer = &player4;
	player4.nextPlayer = &player1;

	players[0] = player1;
	players[1] = player2;
	players[2] = player3;
	players[3] = player4;
}

//void PrintCard(int num)	// ���ڿ� ���� ī�� ���
//{
//	if (num == 0)
//	{
//		printf("��Ŀ ");
//	}
//	else
//	{
//		switch ((num - 1) / 13)
//		{
//		case 0:
//			printf("��");
//			break;
//		case 1:
//			printf("��");
//			break;
//		case 2:
//			printf("��");
//			break;
//		case 3:
//			printf("��");
//			break;
//		}
//		printf("%d ", (num - 1) % 13 + 1);
//	}
//	printf("\n");
//}

void PrintCards(Node* head)	// ��� �ִ� ī�� �� ���
{
	while (head != NULL)
	{
		if (head->num == 0)
		{
			printf("��Ŀ ");
		}
		else
		{
			switch ((head->num - 1) / 13)
			{
			case 0:
				printf("��");
				break;
			case 1:
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("��");
				break;
			}
			printf("%d ", (head->num - 1) % 13 + 1);
		}
		head = head->next;
	}
	printf("\n");
}

void RemoveCard(Node** head)	// ���ڰ� ���� ī�� 2�� �Ǵ� 4�� ����
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

int DrawCard(Node** head, int index)	// �ٸ� �÷��̾ ��� �ִ� ī�� �̱�(1 ~ n)
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

void RemovePlayer(Player player)	// �а� 0���� �� �÷��̾� ���ӿ��� ����
{
	if (Length(player.hand) == 0 && (player.prevPlayer != NULL || player.nextPlayer != NULL))
	{
		player.prevPlayer->nextPlayer = player.nextPlayer;
		player.nextPlayer->prevPlayer = player.prevPlayer;
		player.prevPlayer = NULL;
		player.nextPlayer = NULL;
	}
}

int GameEnd(Player player)	// ���� ����
{
	if (player.prevPlayer != NULL && player.nextPlayer != NULL)
	{
		return (&player == player.prevPlayer) && (&player == player.nextPlayer);
	}
}