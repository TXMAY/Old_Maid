#pragma once
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
// ī�� ����� 2ĭ, ī�� �׵θ��� 1ĭ

void PrintCard(int num)
{
	setlocale(LC_ALL, "");
	wchar_t shape[4] =
	{
		L'��',
		L'��',
		L'��',
		L'��'
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

	printf("����������������������\n");
	printf("��%C       ��\n", shape[0]);
	printf("��%S       ��\n", number[9]);
	printf("��         ��\n");
	printf("��    ��   ��\n");
	printf("��         ��\n");
	printf("��         ��\n");
	printf("��         ��\n");
	printf("����������������������\n");
}