#pragma once
#define MAX_QUEUE_SIZE 14
// 플레이어가 들고 있는 카드 패를 구현하기 위한 원형 큐 구현 코드
typedef struct Queue
{
	int data[MAX_QUEUE_SIZE];
	int rear, front;
}Queue;

void InitQueue(Queue* q)
{
	q->front = q->rear = 0;
}

int IsEmpty(Queue* q)
{
	return(q->front == q->rear);
}

int IsFull(Queue* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void Enqueue(Queue* q, int item)
{
	if (IsFull(q))
	{
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

int Dequeue(Queue* q)
{
	if (IsEmpty(q))
	{
		return -1;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}