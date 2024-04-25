#pragma once
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <Windows.h>

#include "Player.h"
// ī�� ����� 2ĭ, ī�� �׵θ��� 1ĭ

void PrintHandCards(Player player)
{
	int length = Length(player.hand);
	Node* temp = player.hand;
	int color;

	wchar_t* shape[4]={
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

	int x = 120 - (5 * length + (length - 1 * 1)) - 1; // ��� ������ ���� ��ġ ���(ī�� �� �� : 10, ���� : 2)
	COORD pos = { x, 0 };

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

			pos.Y = 57;
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

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			for (int j = 0; j < 19; j++)
			{
				if (j == 1 || j == 4 || j == 7 || j == 8 || j == 11 || j == 12 || j == 15 || j == 18) // �� �ٲ�
				{
					pos.Y++;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
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
			pos.X += 12; // ī�� 1�� + ���� ��ŭ ������ �̵�
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
