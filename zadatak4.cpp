#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define MAX_FILE_NAME 50
#define MAX_LINE 1024
#define FILE_DIDNT_OPEN_ERROR -1
#define ERROR -2

struct polinom;
typedef struct polinom* Position;
typedef struct polinom
{
	int c;
	int e;
	Position Next;
};

int insertSort(char*, Position);
int insertSortList(int, int, Position);
int printList(Position);

int main()
{
	Position Head = NULL;
	Head = (Position)malloc(sizeof(polinom));

	if (Head == NULL)
	{
		printf("Nije dobro alocirana memorija.");
		return ERROR;
	}

	Head->Next = NULL;

	char filename[MAX_FILE_NAME] = { 0 };

	printf("Unesi ime file-a s polinomima:");
	scanf(" %[^\n]", filename);

	insertSort(filename, Head);

	return SUCCESS;
}

int insertSort(char* f, Position P)
{
	char buffer1[MAX_LINE] = { 0 };
	char buffer2[MAX_LINE] = { 0 };
	char* B1 = buffer1;
	char* B2 = buffer2;

	Position P1 = NULL;
	P1 = (Position)malloc(sizeof(polinom));
	P1->Next = NULL;
	Position P2 = NULL;
	P2 = (Position)malloc(sizeof(polinom));
	P2->Next = NULL;

	int n = 0;
	int i = 0;
	int koef = 0;
	int exp = 0;
	FILE* fp = NULL;

	fp = fopen(f, "r");

	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila!\n", f);
		return FILE_DIDNT_OPEN_ERROR;
	}

	for (i = 0; i < 2; i++)
	{
		fgets(B1, MAX_LINE, fp);
		fgets(B2, MAX_LINE, fp);
	}

	while (strlen(B1) > 0)
	{
		sscanf(B1, "%d %d %n", &koef, &exp, &n);
		insertSortList(koef, exp, P1);
		B1 += n;
	}

	while (strlen(B2) > 0)
	{
		sscanf(B2, "%d %d %n", &koef, &exp, &n);
		insertSortList(koef, exp, P2);
		B2 += n;
	}

	printList(P1);
	printList(P2);

	return SUCCESS;
}

int insertSortList(int koef, int exp, Position P)
{
	Position temp = NULL;
	Position head = NULL;
	temp = (Position)malloc(sizeof(polinom));

	if (koef == 0)
	{
		printf("Koeficijent je 0 pa se ovaj unos nece obaviti.");
		return SUCCESS;
	}

	while (P->Next != NULL && P->Next->e > exp)
		P = P->Next;

	if (P->Next != NULL && P->Next->e == exp)
		P->Next->c += koef;

	else
	{
		temp->e = exp;
		temp->c = koef;
		temp->Next = P->Next;
		P->Next = temp;
	}

	return SUCCESS;
}

int printList(Position P)
{
	if (P == NULL)
	{
		printf("Lista je prazna!\n");
		return ERROR;
	}

	while (P != NULL)
	{
		printf("%d %d ", P->c, P->e);
		P = P->Next;
	}

	printf("\n");

	return SUCCESS;
}