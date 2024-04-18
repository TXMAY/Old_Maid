#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Queue.h"

typedef struct Player
{
	Queue hand[14];
	Player* nextPlayer;
}Player;

Player player1;
Player player2;
Player player3;
Player player4;

int card[54] = { 0, }; // ī�带 ������ ��, �ߺ� ������ ���� ���� ī�带 ����ϴ� �迭
// 0 : ����(����)
// 1 ~ 13 : �����̵� A ~ 13
// 14 ~ 26 : ���̾� A ~ 13
// 27 ~ 39 : ��Ʈ A ~ 13
// 40 ~ 52 : Ŭ�ι� A ~ 13
// 53 : ��Ŀ

void Init()
{
	srand(time(NULL));

	int i = 0;
	int tmp = 0;

	// ���� �̱�
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53 + 1;
		if (card[tmp] == 0)
		{
			player1.hand[i] = tmp;
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53 + 1;
		if (card[tmp] == 0)
		{
			player2.hand[i] = tmp;
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53 + 1;
		if (card[tmp] == 0)
		{
			player3.hand[i] = tmp;
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}
	for (i = 0; i < 13; i++)
	{
		tmp = rand() % 53 + 1;
		if (card[tmp] == 0)
		{
			player4.hand[i] = tmp;
			card[tmp] = 1;
		}
		else
		{
			i--;
		}
	}

	// ���� �÷��̾� ����
	player1.nextPlayer = &player2;
	player2.nextPlayer = &player3;
	player3.nextPlayer = &player4;
	player4.nextPlayer = &player1;
}


int main(void)
{
	return 0;
}