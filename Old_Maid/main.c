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

int card[54] = { 0, }; // 카드를 나눠줄 때, 중복 방지를 위해 뽑은 카드를 등록하는 배열
// 0 : 공백(없음)
// 1 ~ 13 : 스페이드 A ~ 13
// 14 ~ 26 : 다이아 A ~ 13
// 27 ~ 39 : 하트 A ~ 13
// 40 ~ 52 : 클로버 A ~ 13
// 53 : 조커

void Init()
{
	srand(time(NULL));

	int i = 0;
	int tmp = 0;

	// 손패 뽑기
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

	// 다음 플레이어 설정
	player1.nextPlayer = &player2;
	player2.nextPlayer = &player3;
	player3.nextPlayer = &player4;
	player4.nextPlayer = &player1;
}


int main(void)
{
	return 0;
}