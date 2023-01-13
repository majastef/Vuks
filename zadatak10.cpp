#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define ERROR -1
#define MAX 50
#define MAX_LINE 1024

struct tree;
typedef struct tree* Position;
typedef struct tree
{
	char city[MAX];
	int residents;
	Position Left;
	Position Right;
};

struct list;
typedef struct list* Pos;
typedef struct list
{
	char country[MAX_LINE];
	Pos Next;
	Position Down;
};

int insertInList(Pos, char*, char*);

int main()
{
	Position Root = NULL;
	Pos Head = NULL;
	Head = (Pos)malloc(sizeof(list));

	if (NULL == Head)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	Head->Next = NULL;
	Head->Down = Root;

	char file[MAX] = { 0 };
	char cntry[MAX_LINE] = { 0 };
	char cty[MAX_LINE] = { 0 };
	FILE* f = NULL;

	printf("Unesi ime datoteke:");
	scanf(" %s", file);

	f = fopen(file, "r");

	if (NULL == f)
	{
		printf("Greska pri otvaranju datoteke.");
		return ERROR;
	}

	while (!feof(f))
	{
		fgets(cntry, MAX_LINE, f);
		fgets(cty, MAX_LINE, f);

		insertInList(Head, cntry, cty);
	}

	return SUCCESS;
}

int insertInList(Pos P, char* name, char* file)
{
	char word[MAX_LINE] = { 0 };
	FILE* fp = NULL;
	fp = fopen(file, "r");

	if (NULL == fp)
	{
		printf("Greska pri otvaranju datoteke.");
		return ERROR;
	}

	Pos Q = NULL;
	Q = (Pos)malloc(sizeof(list));

	if (NULL == Q)
	{
		printf("Greska pri alociranju memorije.");
		return ERROR;
	}

	Q->Next = NULL;

	while ((P->Next != NULL) && (strcmp(P->country, name) > 0))
		P = P->Next;

	strcpy(Q->country, name);
	Q->Next = P->Next;
	P->Next = Q;

	while (!feof(fp))
	{
		fgets(word, MAX_LINE, fp);
		
	}

	return SUCCESS;
}
