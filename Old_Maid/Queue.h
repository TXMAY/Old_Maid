#pragma once
// �÷��̾ ��� �ִ� ī�� �и� �����ϱ� ���� ���� ť ���� �ڵ�
typedef struct Queue
{
	int data[14];
	int rear, front;
}Queue;

void InitQueue(Queue* q)
{
	q->front = q->rear = 0;
}