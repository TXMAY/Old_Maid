#include <stdio.h>
#include <Windows.h>

#include "Game.h"
#include "Card.h"

int main(void)
{

	/*int index, length, i = 0;
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
		PrintLines();
		PrintHandCards(player1);
		PrintBackCards(player2,16,8);
		PrintBackCards(player3,86,8);
		PrintBackCards(player4,156,8);

		MoveCursor(20, 6);
		printf("name test");
		MoveCursor(100, 39);
		printf("info test");

		PrintPointer(player1, 2);

		if (i == 0) scanf_s("%d", &index);

		if(Length(players[i].hand)!=0)
		{
			InsertRandom(players[i].hand, DrawCard(players[i].drawPlayer->hand, index));
			RemoveCard(players[i].hand);
			RemovePlayer(players[i]);
		}

		i++;
		if (i > 3) i = 0;

		if (Length(player1.hand) != 0)
		{
			//PrintCard(DrawCard(&player1.drawPlayer->hand, index));
			InsertRandom(&player1.hand, DrawCard(&player1.drawPlayer->hand, index));
			RemoveCard(&player1.hand);
			RemovePlayer(player1);
		}
		if (Length(player2.hand) != 0)
		{
			length = rand() % Length(player2.drawPlayer->hand) + 1;
			//PrintCard(DrawCard(&player2.drawPlayer->hand, length));
			InsertRandom(&player2.hand, DrawCard(&player2.drawPlayer->hand, length));
			RemoveCard(&player2.hand);
			RemovePlayer(player2);
		}
		if (Length(player3.hand) != 0)
		{
			length = rand() % Length(player3.drawPlayer->hand) + 1;
			//PrintCard(DrawCard(&player3.drawPlayer->hand, length));
			InsertRandom(&player3.hand, DrawCard(&player3.drawPlayer->hand, length));
			RemoveCard(&player3.hand);
			RemovePlayer(player3);
		}
		if (Length(player4.hand) != 0)
		{
			length = rand() % Length(player4.drawPlayer->hand) + 1;
			//PrintCard(DrawCard(&player4.drawPlayer->hand, length));
			InsertRandom(&player4.hand, DrawCard(&player4.drawPlayer->hand, length));
			RemoveCard(&player4.hand);
			RemovePlayer(player4);
		}
		system("cls");
	}*/
	PlayeGame();
	return 0;
}