#pragma once
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>

#include <conio.h>

#include "Player.h"
#include "Common.h"
#include "Card.h"

Player player1;
Player player2;
Player player3;
Player player4;

Player* players[4];

int card[53] = { 0, }; // ī�带 ������ ��, �ߺ� ������ ���� ���� ī�带 ����ϴ� �迭
// 0 : ��Ŀ
// 1 ~ 13 : �����̵� A ~ 13
// 14 ~ 26 : ���̾� A ~ 13
// 27 ~ 39 : ��Ʈ A ~ 13
// 40 ~ 52 : Ŭ�ι� A ~ 13

void Init() // �⺻ ����
{
	CONSOLE_CURSOR_INFO cursor = {
		0,
	};
	cursor.bVisible = FALSE;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	setlocale(LC_CTYPE, "");

	player1.hand = NULL;
	player2.hand= NULL;
	player3.hand= NULL;
	player4.hand= NULL;

	player1.name = "Player1";
	player2.name = "Player2";
	player3.name = "Player3";
	player4.name = "Player4";

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
	player1.drawPlayer = &player4;
	player2.drawPlayer = &player1;
	player3.drawPlayer = &player2;
	player4.drawPlayer = &player3;

	// ���� ����(4���� 14��)
}

// void PrintCard(int num)	// ���ڿ� ���� ī�� ���
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
// }

void PrintCards(Node* head) // ��� �ִ� ī�� �� ���(�׽�Ʈ ��)
{
	//head = head->next;
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

void RemoveCard(Node** head) // ���ڰ� ���� ī�� 2�� �Ǵ� 4�� ���� (���� ���� �߻� ���� ���, ��� ���� �� ���� �� �Ǵ��� Ȯ��)
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

	current = *head;
	while (current != NULL)
	{
		index = (current->num - 1) % 13 + 1;
		if (count[index] > 1)
		{
			if (count[index] ==3)
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

int DrawCard(Node** head, int index) // �ٸ� �÷��̾ ��� �ִ� ī�� �̱�(1 ~ n)
{
	Node* temp = *head;
	Node* prev = NULL;
	int num = 0;
	int count = 1;

	if (index == 1)
	{
		Node* toDelete = *head;
		if (toDelete != NULL)
		{
			*head = toDelete->next;
			num = toDelete->num;
			free(toDelete);
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

void RemovePlayer(Player player) // �а� 0���� �� �÷��̾� ���ӿ��� ����
{
	if (Length(player.drawPlayer->hand) == 0)
	{
		player.drawPlayer = player.drawPlayer->drawPlayer;
	}
}

int GameEnd(Player player) // ���� ����
{
	return &player == player.drawPlayer;
}

void PrintLines()	// �� ���(x : 14 ~ 224, y : 4 ~ 62)
{
	int divide = 2;
	//MoveCursor(14, 5);
	for (int i = 4; i < 63; i++)
	{
		MoveCursor(14, i);
		if (i != 4 && /*i != 7 &&*/ i != 37 && i != 52 && i != 62)
		{
			printf("��");
			if (i < 38)
			{
				MoveCursor(84, i);
				printf("��");
				MoveCursor(154, i);
				printf("��");
			}
			MoveCursor(224, i);
			printf("��");
		}
		else
		{
			for (int j = 14; j < 225; j++)
			{
				/*if (i == 0 && j == 0) printf("��");
				else if (i == 0 && j == 238) printf("��");
				else if (i == 66 && j == 0) printf("��");
				else if (i == 66 && j == 238) printf("��");
				else */
				if (i == 4 || /*i == 7 ||*/ i == 37 || i == 52 || i == 62)
				{
					if (j == 14) printf("��");
					else if (j == 224) printf("��");
					//else if (i == 7 && (j == 84 || j == 154)) printf("��");
					else printf("��");
				}
			}
		}
	}
	MoveCursor(14, 4);
	printf("��");
	MoveCursor(224, 4);
	printf("��");
	MoveCursor(224, 62);
	printf("��");
	MoveCursor(14, 62);
	printf("��");
	MoveCursor(84, 4);
	printf("��");
	MoveCursor(154, 4);
	printf("��");
	MoveCursor(84, 37);
	printf("��");
	MoveCursor(154, 37);
	printf("��");
}

void PlayeGame()
{
	int index, length, i = 0;
	Init();

	players[0] = &player1;
	players[1] = &player2;
	players[2] = &player3;
	players[3] = &player4;

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
		printf("current Player : %s\n",players[i]->name);
		/*printf("player 1 : ");
		PrintCards(player1.hand);*/
		printf("player 2 : ");
		PrintCards(player2.hand);
		printf("player 3 : ");
		PrintCards(player3.hand);
		printf("player 4 : ");
		PrintCards(player4.hand);

		PrintLines();
		PrintHandCards(player1);
		PrintBackCards(player2, 16, 8);
		PrintBackCards(player3, 86, 8);
		PrintBackCards(player4, 156, 8);

		MoveCursor(20, 6);
		printf("name test");
		MoveCursor(100, 39);
		printf("info test");

		PrintPointer(player1, 0);

		//if (i == 0) scanf_s("%d", &index);
		if (i == 0) index = 1;
		index = 1;
		//Sleep(1000);
		_getch();

		if (i == 0)
		{
			InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, index));
		}
		else
		{
			length = rand() % Length(players[i]->drawPlayer->hand) + 1;
			InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, length));
		}
		RemoveCard(&players[i]->hand);
		RemovePlayer(*players[i]);
		/*switch (i)
		{
		case 0:
			InsertRandom(player1.hand, DrawCard(player1.drawPlayer->hand, index));
			RemoveCard(player1.hand);
			RemovePlayer(player1);
			break;
		case 1:
			length = rand() % Length(player2.drawPlayer->hand) + 1;
			InsertRandom(player2.hand, DrawCard(player2.drawPlayer->hand, length));
			RemoveCard(player2.hand);
			RemovePlayer(player2);
			break;
		case 2:
			length = rand() % Length(player3.drawPlayer->hand) + 1;
			InsertRandom(player2.hand, DrawCard(player3.drawPlayer->hand, length));
			RemoveCard(player3.hand);
			RemovePlayer(player3);
			break;
		case 3:
			length = rand() % Length(player3.drawPlayer->hand) + 1;
			InsertRandom(player3.hand, DrawCard(player3.drawPlayer->hand, length));
			RemoveCard(player3.hand);
			RemovePlayer(player3);
			break;
		}*/
		/*if (Length(players[i].hand) != 0)
		{
			InsertRandom(&players[i].hand, DrawCard(&players[i].drawPlayer->hand, index));
			RemoveCard(&players[i].hand);
			RemovePlayer(players[i]);
		}
		else
		{
			length = rand() % Length(players[i].drawPlayer->hand) + 1;
			InsertRandom(&players[i].hand, DrawCard(&players[i].drawPlayer->hand, length));
			RemoveCard(&players[i].hand);
			RemovePlayer(players[i]);
		}*/

		i++;
		if (i > 3) i = 0;

		/*if (Length(player1.hand) != 0)
		{
			//PrintCard(DrawCard(&player1.drawPlayer->hand, index));
			InsertRandom(&player1.hand, DrawCard(&player1.drawPlayer->hand, index));
			RemoveCard(&player1.hand);
			//RemovePlayer(&player1);
			if (Length(player1.hand) == 0)
			{
				player2.drawPlayer = player1.drawPlayer;
			}
		}
		if (Length(player2.hand) != 0)
		{
			length = rand() % Length(player2.drawPlayer->hand) + 1;
			//PrintCard(DrawCard(&player2.drawPlayer->hand, length));
			InsertRandom(&player2.hand, DrawCard(&player2.drawPlayer->hand, length));
			RemoveCard(&player2.hand);
			//RemovePlayer(&player2);
			if (Length(player2.hand) == 0)
			{
				player3.drawPlayer = player2.drawPlayer;
			}
		}
		if (Length(player3.hand) != 0)
		{
			length = rand() % Length(player3.drawPlayer->hand) + 1;
			//PrintCard(DrawCard(&player3.drawPlayer->hand, length));
			InsertRandom(&player3.hand, DrawCard(&player3.drawPlayer->hand, length));
			RemoveCard(&player3.hand);
			//RemovePlayer(&player3);
			if (Length(player3.hand) == 0)
			{
				player4.drawPlayer = player3.drawPlayer;
			}
		}
		if (Length(player4.hand) != 0)
		{
			length = rand() % Length(player4.drawPlayer->hand) + 1;
			//PrintCard(DrawCard(&player4.drawPlayer->hand, length));
			InsertRandom(&player4.hand, DrawCard(&player4.drawPlayer->hand, length));
			RemoveCard(&player4.hand);
			//RemovePlayer(&player4);
			if (Length(player4.hand) == 0)
			{
				player1.drawPlayer = player4.drawPlayer;
			}
		}*/
		system("cls");
	}
}
// ���� : 67
// ��� �� : 1
// ���� : 1
// ��� �÷��̾� �̸� : 1
// ���� : 1
// ��� ī�� ����(�ִ�ġ) : 9 * 3 = 27
// �߰� �� : 1
// ī�� ���� �ȳ� �޼��� : 1
// ���� : 1
// ī�� ���� â(����) : 11
// �߰� �� : 1
// �÷��̾� �̸� : 1
// ���� : 1
// �÷��̾� ī�� ���� : 9
// �ϴ� �� : 1
// �� 62

// ���� : 240/���� �ʿ� ���� 188(ī�� ���� : 60, �� : 2 * 4 = 8 (���μ��� ��ĭó�� �������� ��ĭ �����)
// 3��� : 80