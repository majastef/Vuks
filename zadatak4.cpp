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

int insertSort(char*, Position, Position);
int insertSortList(int, int, Position);
int printList(Position);
int addition(Position, Position, Position);
int multiplication(Position, Position, Position);
int deleteAll(Position);

int main()
{
	Position P1 = NULL;
	P1 = (Position)malloc(sizeof(polinom));
	Position P2 = NULL;
	P2 = (Position)malloc(sizeof(polinom));
	Position Z = NULL;
	Z = (Position)malloc(sizeof(polinom));
	Position M = NULL;
	M = (Position)malloc(sizeof(polinom));

	if (P1 == NULL || P2 == NULL || Z == NULL || M == NULL)
	{
		printf("Nije dobro alocirana memorija.");
		return ERROR;
	}

	P1->Next = NULL;
	P2->Next = NULL;
	Z->Next = NULL;
	M->Next = NULL;

	char filename[MAX_FILE_NAME] = { 0 };

	printf("Unesi ime file-a s polinomima:");
	scanf(" %[^\n]", filename);

	insertSort(filename, P1, P2);

	printf("Prvi polinom: ");
	printList(P1->Next);
	printf("Drugi polinom: ");
	printList(P2->Next);

	addition(P1->Next, P2->Next, Z);
	printf("\nSuma: ");
	printList(Z->Next);

	multiplication(P1->Next, P2->Next, M);
	printf("Product: ");
	printList(M->Next);

	deleteAll(P1);
	deleteAll(P2);
	deleteAll(Z);
	deleteAll(M);

	return SUCCESS;
}

int insertSort(char* f, Position P1, Position P2)
{
	char buffer1[MAX_LINE] = { 0 };
	char buffer2[MAX_LINE] = { 0 };
	char* B1 = buffer1;
	char* B2 = buffer2;

	int n = 0;
	int i = 0;
	int koef = 0;
	int exp = 0;
	int value = 0;
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
		value = sscanf(B1, "%d %d %n", &koef, &exp, &n);
		if (value == 2)
			insertSortList(koef, exp, P1);
		else
			return ERROR;
		B1 += n;
	}

	while (strlen(B2) > 0)
	{
		value = sscanf(B2, "%d %d %n", &koef, &exp, &n);
		if (value == 2)
			insertSortList(koef, exp, P2);
		else
			return ERROR;
		B2 += n;
	}

	return SUCCESS;
}

int insertSortList(int koef, int exp, Position P)
{
	Position temp = NULL;
	temp = (Position)malloc(sizeof(polinom));
	Position empty = NULL;

	if (temp == NULL)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	temp->Next = NULL;

	if (koef == 0)
	{
		printf("Koeficijent je 0 pa se ovaj unos nece obaviti.");
		return SUCCESS;
	}

	while (P->Next != NULL && P->Next->e > exp)
		P = P->Next;

	if (P->Next != NULL && P->Next->e == exp)
	{
		P->Next->c += koef;
		if (P->Next->c == 0)
		{
			empty = P->Next;
			P->Next = empty->Next;
			free(empty);
		}
	}


	else
	{
		temp->e = exp;
		temp->c = koef;
		temp->Next = P->Next;
		P->Next = temp;
	}

	return SUCCESS;
}

int addition(Position P1, Position P2, Position Z)
{
	while (P1 != NULL && P2 != NULL)
	{
		if (P1->e == P2->e)
		{
			insertSortList(P1->c + P2->c, P1->e, Z);
			P1 = P1->Next;
			P2 = P2->Next;
		}

		else if (P1->e > P2->e)
		{
			insertSortList(P1->c, P1->e, Z);
			P1 = P1->Next;
		}

		else
		{
			insertSortList(P2->c, P2->e, Z);
			P2 = P2->Next;
		}
	}

	if (P2 != NULL && P1 == NULL)
	{
		while (P2 != NULL)
		{
			insertSortList(P2->c, P2->e, Z);
			P2 = P2->Next;
		}
	}

	if (P1 != NULL && P2 == NULL)
	{
		while (P1 != NULL)
		{
			insertSortList(P1->c, P1->e, Z);
			P1 = P1->Next;
		}
	}

	else
		return SUCCESS;

	return SUCCESS;
}

int multiplication(Position P1, Position P2, Position M)
{
	while (P1 != NULL)
	{
		while (P2 != NULL)
		{
			insertSortList(P1->c * P2->c, P1->e + P2->e, M);
			P2 = P2->Next;
		}
		P1 = P1->Next;
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
		printf("%dx^%d ", P->c, P->e);
		P = P->Next;
		if (P != NULL)
			printf("+ ");
	}

	printf("\n");

	return SUCCESS;
}

int deleteAll(Position P)
{
	Position temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	free(P);
	return SUCCESS;
}