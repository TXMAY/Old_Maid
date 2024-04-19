#pragma once
// 플레이어가 들고 있는 패는 연결 리스트로 구현(made by gpt)
#include <stdlib.h>

typedef struct Node
{
	int num;
	struct Node* next;
}Node;

Node* Create(int num)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) return NULL;
	newNode->num = num;
	newNode->next = NULL;
	return newNode;
}

void Insert(Node** head, int num)
{
	Node* newNode = Create(num);
	newNode->next = *head;
	*head = newNode;
}

typedef struct Player
{
	Node* hand;
	struct Player* nextPlayer;
}Player;