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
Position insertInTree(Position, Position);
int cityCmp(Position, Position);
int printList(Pos);
int printTree(Position);
int printOption(Pos, char*, int);
int printCities(Position, int);

int main()
{
	char optionName[MAX_LINE] = { 0 };
	int optionNumber = 0;
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
		fscanf(f, "%s %s", cntry, cty);

		insertInList(Head, cntry, cty);
	}

	printList(Head->Next);

	printf("Unesi ime drzave:");
	scanf(" %s", optionName);

	printf("Unesi broj stanovnika:");
	scanf("%d", &optionNumber);

	printOption(Head->Next, optionName, optionNumber);

	return SUCCESS;
}

int insertInList(Pos P, char* name, char* file)
{
	char word[MAX_LINE] = { 0 };
	int number = 0;
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
		fscanf(fp, "%s %d", word, &number);

		Position New = NULL;
		New = (Position)malloc(sizeof(tree));

		if (NULL == New)
		{
			printf("Greska pri alociranju memorije.");
			return ERROR;
		}

		New->Right = NULL;
		New->Left = NULL;
		strcpy(New->city, word);
		New->residents = number;

		Q->Down = insertInTree(Q->Down, New);
	}

	return SUCCESS;
}

Position insertInTree(Position R, Position N)
{
	int result = 0;

	if (NULL == R)
		return N;

	result = cityCmp(R, N);

	if (result > 0)
		R->Right = insertInTree(R->Right, N);

	else if (result < 0)
		R->Left = insertInTree(R->Left, N);

	else
		free(N);

	return R;
}

int cityCmp(Position C1, Position C2)
{
	int res = 0;
	res = (C1->residents) - (C2->residents);

	if (0 == res)
		res = strcmp(C1->city, C2->city);

	return res;
}

int printList(Pos P)
{
	if (NULL == P)
	{
		printf("Lista je prazna.");
		return ERROR;
	}

	while (P != NULL)
	{
		printf("%s - ", P->country);
		printTree(P->Down);
		P = P->Next;
	}

	return SUCCESS;
}

int printTree(Position R)
{
	if (NULL == R)
		return SUCCESS;

	printTree(R->Left);
	printf("%s %d, ", R->city, R->residents);
	printTree(R->Right);
}

int printOption(Pos P, char* name, int number)
{
	while (P != NULL && P->country != name)
		P = P->Next;

	printCities(P->Down, number);

	return SUCCESS;
}

int printCities(Position R, int number)
{
	if (NULL == R)
		return SUCCESS;

	if (R->residents <= number)
		printCities(R->Right, number);

	else if (R->residents > number)
		printf("%s %d ", R->city, R->residents);

	return SUCCESS;
}
