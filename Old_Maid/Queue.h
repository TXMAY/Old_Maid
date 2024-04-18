#pragma once
// 플레이어가 들고 있는 카드 패를 구현하기 위한 원형 큐 구현 코드
typedef struct Queue
{
	int data[14];
	int rear, front;
}Queue;

void InitQueue(Queue* q)
{
	q->front = q->rear = 0;
}