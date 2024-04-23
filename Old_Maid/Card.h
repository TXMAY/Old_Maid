#pragma once
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
// 카드 모양은 2칸, 카드 테두리는 1칸

void PrintCard(int num)
{
	setlocale(LC_ALL, "");
	wchar_t shape[4] =
	{
		L'♠',
		L'◆',
		L'♥',
		L'♣'
	};
	wchar_t* number[13] =
	{
		L"Ａ",
		L"２",
		L"３",
		L"４",
		L"５",
		L"６",
		L"７",
		L"８",
		L"９",
		L"10",
		L"Ｊ",
		L"Ｑ",
		L"Ｋ",

	};

	printf("┌─────────┐\n");
	printf("│%C       │\n", shape[0]);
	printf("│%S       │\n", number[9]);
	printf("│         │\n");
	printf("│    ♠   │\n");
	printf("│         │\n");
	printf("│         │\n");
	printf("│         │\n");
	printf("└─────────┘\n");
}