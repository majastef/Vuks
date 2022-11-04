#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define MAX_FILE_NAME 50
#define MAX_LINE 1024
#define FILE_DIDNT_OPEN_ERROR -1

struct polinom;
typedef struct polinom* Position;
typedef struct polinom
{
	int c;
	int e;
	Position Next;
};

int insertSort(char* , Position);

int main()
{
	Position Head = NULL;
	Head = (Position)malloc(sizeof(polinom));
	Head->Next = NULL;

	char filename[MAX_FILE_NAME] = { 0 };

	printf("Unesi ime file-a s polinomima:");
	scanf(" %[^\n]", filename);

	insertSort(filename, Head);

	return SUCCESS;
}

int insertSort(char* f, Position P)
{
	char buffer[MAX_LINE] = { 0 };
	char* B = buffer;
	int n = 0;
	Position P1 = NULL;
	Position P2 = NULL;
	FILE* fp = NULL;
	fp = fopen(f, "r");

	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila!\n", f);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while(!feof(fp))
	{
		fgets(B, MAX_LINE, fp);
		while (strlen(B) > 0)
		{
			sscanf(B, "%d %d %n", &P1->c, &P1->e, &n);
			B += n;
		}
		P1 = P2;
	}

	return SUCCESS;
}
