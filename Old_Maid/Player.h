#pragma once
// 플레이어가 들고 있는 패는 연결 리스트로 구현(made by gpt)
#include <stdlib.h>

typedef struct Node	// 연결 리스트의 노드 정의
{
	int num;
	struct Node* next;
}Node;

Node* Create(int num)	// 노드 생성
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) return NULL;
	newNode->num = num;
	newNode->next = NULL;
	return newNode;
}

void Insert(Node** head, int num)	// 노드 추가
{
	/*Node* newNode = Create(num);
	newNode->next = *head;
	*head = newNode;*/

	Node* newNode = Create(num);
	//newNode->next = NULL;
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}
		Node* temp = *head;
		while (temp->next!=NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
}

int Length(Node* head)	// 연결 리스트의 길이 구하기
{
	int length = 0;
	Node* current = head;
	while (current != NULL)
	{
		length++;
		current = current->next;
	}
	return length;
}

void InsertRandom(Node** head, int num)	// 랜덤한 위치에 노드 추가 (현재 문제 발생 추정 장소, 노드 제대로 연결 되는지 확인)
{
	int length = Length(*head);
	int position = rand() % (length + 1);

	Node* newNode = Create(num);
	if (position == 0)
	{
		newNode->next = *head;
		*head = newNode;
	}
	else
	{
		Node* temp = *head;
		for (int i = 0; i < position - 1; i++)
		{
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

typedef struct Player	// 연결 리스트를 손패로 사용하는 플레이어 구조체 생성(nextPlayer 없애기(순서는 배열에 넣고 사용할 예정)
{
	Node* hand;	// 들고 있는 카드(패)
	char* name;	// 플레이어 이름
	struct Player* drawPlayer;	// 내가 카드를 뽑을 플레이어
}Player;