#pragma once
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <Windows.h>

#include "Player.h"
#include "Common.h"

#define CARD_Y 53 

void PrintHandCards(Player player)
{
	int length = Length(player.hand);
	Node* temp = player.hand;
	int color;

	wchar_t* shape[4] = {
		L"��",
		L"��",
		L"��",
		L"��"
	};
	wchar_t* number[13] =
	{
		L"��",
		L"��",
		L"��",
		L"��",
		L"��",
		L"��",
		L"��",
		L"��",
		L"��",
		L"10",
		L"��",
		L"��",
		L"��",

	};

	wchar_t* card[19] =
	{
		L"����������������������",
		L"�� ",
		L"", // ���
		L"      ��",
		L"�� ",
		L"", // ����
		L"      ��",
		L"��         ��",
		L"��    ",
		L"", // ���
		L"   ��",
		L"��         ��",
		L"��       ",
		L"", // ����
		L"��",
		L"��       ",
		L"", // ���
		L"��",
		L"����������������������"
	};

	// ���� for������ ���� ��� �ϱ�
	// 1�� : 114, 2�� 108

	int x = (240 - (10 * length + ((length - 1) * 4))) / 2 - 1, y = CARD_Y; // ��� ������ ���� ��ġ ���(ī�� : 10, ���� : 4)
	// ((��ü ���� - ((ī�� ���� * ī�� ���) + (���� * ���� ��))) / 2 - 1
	COORD pos = { x, y };

	if (temp != NULL)
	{
		int num = temp->num;
		for (int i = 0; i < length; i++)
		{
			if ((num - 1) / 13 == 1 || (num - 1) / 13 == 2) // �� ����
			{
				color = 4;
			}
			else
			{
				color = 7;
			}

			//pos.Y = 41;
			if (num != 0) // ī�� �ƽ�Ű ��Ʈ�� ���� ���� ����
			{
				card[2] = card[9] = card[16] = shape[(num - 1) / 13];
				card[5] = card[13] = number[(num - 1) % 13];
			}
			else
			{
				card[2] = card[9] = card[16] = L":P";
				card[5] = card[13] = L"  ";
			}

			MoveCursor(x, y);

			for (int j = 0; j < 19; j++)
			{
				if (j == 1 || j == 4 || j == 7 || j == 8 || j == 11 || j == 12 || j == 15 || j == 18) // �� �ٲ�
				{
					MoveCursor(x, ++y);
				}
				if (j == 2 || j == 5 || j == 9 || j == 13 || j == 16) // �� ����
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				}
				printf("%S", card[j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			temp = temp->next;

			if (temp != NULL)
			{
				num = temp->num;
			}
			//pos.X += 12; // ī�� 1�� + ���� ��ŭ ������ �̵�
			x += 14;
			y = CARD_Y;
		}
		
	}
	// printf("\n");
	/*for (int i = 1; i <= 240; i++)
	{
		printf("%d", i % 10);
	}*/
	/*printf("����������������������\n");
	printf("�� ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%C", shape[(num - 1) / 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("      �� \n");
	printf("�� ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%S", number[(num - 1) % 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("      ��\n");
	printf("��         ��\n");
	printf("��    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%C", shape[(num - 1) / 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("   ��\n");
	printf("��         ��\n");
	printf("��       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%S", number[(num - 1) % 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("��\n");
	printf("��       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%C", shape[(num - 1) / 13]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("��\n");
	printf("����������������������");*/
	// printf("%d %d\n", length, x);
}

void PrintBackCards(Player player, int x, int y)
{
	int length = Length(player.hand);
	Node* temp = &player.hand;
	int tmp = x;
	char* card[9] =
	{
		"����������������������",
		"�� �̢̢̢̦�",
		"�� �̢̢̢̦�",
		"�� �̢̢̢̦�",
		"�� �̢̢̢̦�",
		"�� �̢̢̢̦�",
		"�� �̢̢̢̦�",
		"�� �̢̢̢̦�",
		"����������������������"
	};
	for (int i = 0; i < (length - 1) / 5 + 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if ((i * 5) + j + 1 > length)
			{
				break;
			}
			//MoveCursor(x, y);
			for (int k = 0; k < 9; k++)
			{
				MoveCursor(x, y++);
				printf("%s", card[k]);
			}
			x += 14;
			y -= 9;
		}
		x = tmp;
		y += 10;
	}

}

void PrintPointer(Player player, int index)
{
	int x = ((240 - (10 * Length(player.hand) + ((Length(player.hand) - 1) * 4))) / 2 - 1) + 14 * index;

	MoveCursor(x - 2, 41);
	printf("��");
	MoveCursor(x + 12, 41);
	printf("��");
	MoveCursor(x + 12, 51);
	printf("��");
	MoveCursor(x - 2, 51);
	printf("��");
}
// �÷��̾� �� ĭ : 78
// ī�� �� ĭ : 10
// ����(����) : 4
// ����(����) : 1
// 12 * 5 - 2 = 58
// 20ĭ ����