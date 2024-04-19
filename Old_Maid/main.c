#include <stdio.h>

#include "Game.h"

int main(void)
{
	Init();
	
	PrintCards(player1.hand);
	PrintCards(player2.hand);
	PrintCards(player3.hand);
	PrintCards(player4.hand);

	RemoveCard(&player1.hand);
	RemoveCard(&player2.hand);
	RemoveCard(&player3.hand);
	RemoveCard(&player4.hand);

	PrintCards(player1.hand);
	PrintCards(player2.hand);
	PrintCards(player3.hand);
	PrintCards(player4.hand);

	int index;
	scanf_s("%d", &index);

	DrawCard(&player1.nextPlayer, index);

	PrintCards(player1.hand);
	PrintCards(player2.hand);
	PrintCards(player3.hand);
	PrintCards(player4.hand);
	return 0;
}