#include <stdio.h>
#include <Windows.h>

#include "Game.h"
#include "Card.h"

int main(void)
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode con:lines=67");

	PrintCard(1);

	int index,length;
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
		// 기능 테스트 중
		// 현재 가져온 카드가 제대로 패에 있지 않고 이상하게 증발하는 현상이 있음
		printf("player 1 : ");
		PrintCards(player1.hand);
		printf("player 2 : ");
		PrintCards(player2.hand);
		printf("player 3 : ");
		PrintCards(player3.hand);
		printf("player 4 : ");
		PrintCards(player4.hand);

		scanf_s("%d", &index);

		if (Length(player1.hand) != 0) 
		{
			//PrintCard(DrawCard(&player1.prevPlayer->hand, index));
			InsertRandom(&player1.hand, DrawCard(&player1.prevPlayer->hand, index));
			RemoveCard(&player1.hand);
			RemovePlayer(player1);
		}
		if (Length(player2.hand) != 0) 
		{
			length = rand() % Length(player2.prevPlayer->hand) + 1;
			//PrintCard(DrawCard(&player2.prevPlayer->hand, length));
			InsertRandom(&player2.hand, DrawCard(&player2.prevPlayer->hand, length));
			RemoveCard(&player2.hand);
			RemovePlayer(player2);
		}
		if (Length(player3.hand) != 0)
		{
			length = rand() % Length(player3.prevPlayer->hand) + 1;
			//PrintCard(DrawCard(&player3.prevPlayer->hand, length));
			InsertRandom(&player3.hand, DrawCard(&player3.prevPlayer->hand, length));
			RemoveCard(&player3.hand);
			RemovePlayer(player3);
		}
		if (Length(player4.hand) != 0) 
		{
			length = rand() % Length(player4.prevPlayer->hand) + 1;
			//PrintCard(DrawCard(&player4.prevPlayer->hand, length));
			InsertRandom(&player4.hand, DrawCard(&player4.prevPlayer->hand, length));
			RemoveCard(&player4.hand);
			RemovePlayer(player4);
		}
	}


	return 0;
}