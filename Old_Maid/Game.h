#pragma once
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>
#include <conio.h>

#include "Player.h"
#include "Common.h"
#include "Card.h"

void Init() // �⺻ ����
{
	// �迭�� ������ ������� �÷��̾� �ֱ�
	players[0] = &player1;
	players[1] = &player2;
	players[2] = &player3;
	players[3] = &player4;

	// ���� �ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		players[i]->hand = NULL;
	}

	//�̸� ����
	player1.name = "Player 1";
	player2.name = "Player 2";
	player3.name = "Player 3";
	player4.name = "Player 4";

	srand(time(NULL));

	int tmp = 0;

	// ���� �̱�
	for (int i = 0; i < 53; i++)
	{
		card[i] = 0;
	}

	// ���� ī��� �ߺ� �̱⸦ �����ϱ� ���� �迭�� ����
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
	// ���� ���� ī�� �� ���� 4��° �÷��̾ �п� �߰�
	for (int i = 0; i < 53; i++)
	{
		if (card[i] == 0)
		{
			Insert(&player4.hand, i);
			break;
		}
	}

	// ���� ī�带 �̾ƿ� �÷��̾� ����
	player1.drawPlayer = &player4;
	player2.drawPlayer = &player1;
	player3.drawPlayer = &player2;
	player4.drawPlayer = &player3;
}

void RemoveCard(Node **head) // ���ڰ� ���� ī�� 2�� �Ǵ� 4�� ����
{
	int count[14] = {0};
	int index = 0;
	Node *current = *head;
	Node *prev = NULL;

	while (current != NULL) // ���� ���ڸ� �� �� ������ �ִ��� Ȯ��
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
			if (count[index] == 3) // ���ڰ� ���� ī�带 3�� ������ ������ ù ī�常 ����� ������ 2�� ����
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

int DrawCard(Node **head, int index) // �ٸ� �÷��̾ ��� �ִ� ī�� �̱�
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

void RemovePlayer(Player *player) // ���� ���и� ���� �÷��̾��� ���а� 0���̸� ���и� ���� �÷��̾ ����
{
	while (Length(player->drawPlayer->hand) == 0)
	{
		player->drawPlayer = player->drawPlayer->drawPlayer;
	}
}

int GameEnd(Player *player) // ���� ����
{
	return player == player->drawPlayer; // �÷��̾�� ī�带 �̾ƿ� �÷��̾ ������ Ȯ��
}

void PrintLines() // �� ���(x : 14 ~ 224, y : 4 ~ 62)
{
	for (int i = 4; i < 63; i++)
	{
		MoveCursor(14, i);
		if (i != 4 && i != 37 && i != 52 && i != 62)
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
				if (i == 4 || i == 37 || i == 52 || i == 62)
				{
					if (j == 14)
						printf("��");
					else if (j == 224)
						printf("��");
					else
						printf("��");
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

void PrintInfo(int option) // �÷��̾� �̸��� ���� ���� ���, 0 : ī�� ���� �޼���, 1 ~ 3: �ٸ� �÷��̾� �� �޼���
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

void PrintGameScreen(int option)	// ���� ȭ��(��, �� ����, ��� ����, �̸� �� ���� ��Ȳ) ���
{
	system("cls");
	PrintLines();
	PrintHandCards(player1);
	PrintBackCards(player2, 16, 8);
	PrintBackCards(player3, 86, 8);
	PrintBackCards(player4, 156, 8);
	PrintInfo(option);
}

void PrintPauseMenu()	// �Ͻ� ���� �޴� ���
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
		printf("��");
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
				case 0:	// �Ͻ� ���� ����
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
				case 1:	// ���� ����
					exit(1);
					break;
				}
			}
			if (key == -32)	// ���Ʒ� ����Ű�� �ɼ� ����
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
				printf("��");
				MoveCursor(113, y + (2 * (option + 1)));
				printf("��");
			}
		}
	}
}

void SelectCard(Player player, int length) // �̾ƿ� ī�� ����
{
	char key;
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 122) // zŰ�� ASCII �ڵ�� 122
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
				if (index < 0) // �ε��� �ʰ� ����
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

void EndGame(int win)	// ���� ����
{
	char key;
	int option = 0, x = 116, y = 18;

	system("cls");
	PrintLines();

	MoveCursor(x, y);
	if (win != 0)	// �������� ��Ŀ�� ������ ������ �й�, �� ���� �и� ��� ������ �¸�
	{
		printf("You Win!");
	}
	else
	{
		printf("You Lose");
	}

	MoveCursor(113, y + 2);
	printf("��");
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
				if (option == 0)	// �ٽ��ϱ�
				{
					break;
				}
				else	// ����
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
				printf("��");
				MoveCursor(113, y + (2 * (option + 1)));
				printf("��");
			}
		}
	}
}

void PrintMain()	// ���� ȭ�� ���
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
			RemovePlayer(players[i]); // �÷��̾� ����
			if (GameEnd(players[i]))  // ���� ���� ���� ���� �� ����
			{
				break;
			}
			if (i == 0)
			{
				index = 0;
				PrintDrawHandCards(*players[i]->drawPlayer);									 // ���� ������ �÷��̾��� ���� ���
				SelectCard(*players[i]->drawPlayer, Length(players[i]->drawPlayer->hand));		 // ������ ���� ����
				InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, index)); // ���� ������
			}
			else
			{
				index = rand() % Length(players[i]->drawPlayer->hand);							 // ������ ���� ����
				Sleep(1000);																	 // ���� ��(�� ��ó�� ���̰� �ϱ�)
				InsertRandom(&players[i]->hand, DrawCard(&players[i]->drawPlayer->hand, index)); // ���� ������
			}
			printf("\n");
			PrintGameScreen(i); // ������ �� ���� ǥ��
			Sleep(1000);
			RemoveCard(&players[i]->hand); // ī�� ����
			PrintGameScreen(i);			   // ������ �� ���� ǥ��
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