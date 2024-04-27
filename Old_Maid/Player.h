#pragma once
// �÷��̾ ��� �ִ� �д� ���� ����Ʈ�� ����(made by gpt)
#include <stdlib.h>

typedef struct Node	// ���� ����Ʈ�� ��� ����
{
	int num;
	struct Node* next;
}Node;

Node* Create(int num)	// ��� ����
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) return NULL;
	newNode->num = num;
	newNode->next = NULL;
	return newNode;
}

void Insert(Node** head, int num)	// ��� �߰�
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

int Length(Node* head)	// ���� ����Ʈ�� ���� ���ϱ�
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

void InsertRandom(Node** head, int num)	// ������ ��ġ�� ��� �߰� (���� ���� �߻� ���� ���, ��� ����� ���� �Ǵ��� Ȯ��)
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

typedef struct Player	// ���� ����Ʈ�� ���з� ����ϴ� �÷��̾� ����ü ����(nextPlayer ���ֱ�(������ �迭�� �ְ� ����� ����)
{
	Node* hand;	// ��� �ִ� ī��(��)
	char* name;	// �÷��̾� �̸�
	struct Player* drawPlayer;	// ���� ī�带 ���� �÷��̾�
}Player;