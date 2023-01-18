#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define ERROR -1
#define MAX 50
#define MAX_LINE 1024

struct list;
typedef struct list* Pos;
typedef struct list
{
	char city[MAX_LINE];
	int residents;
	Pos Next;
};

struct tree;
typedef struct tree* Position;
typedef struct tree
{
	char country[MAX_LINE];
	Position Left;
	Position Right;
	Pos Down;
};

Position Read(Position, Pos, char*, char*);
Position insertInTree(Position, Position);
int insertInList(Pos, Pos);
int printTree(Position);
int printList(Pos);

int main()
{
	//char optionName[MAX_LINE] = { 0 };
	//int optionNumber = 0;
	Position Root = NULL;
	Pos Head = NULL;
	Head = (Pos)malloc(sizeof(list));

	if (NULL == Head)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	Head->Next = NULL;
	//Root->Down = Head;
	Pos temp = Head;

	char file[MAX] = { 0 };
	char cntry[MAX_LINE] = { 0 };
	char cty[MAX_LINE] = { 0 };
	FILE* f = NULL;

	printf("Unesi ime datoteke:");
	scanf(" %s", file);
	printf("\n");

	f = fopen(file, "r");

	if (NULL == f)
	{
		printf("Greska pri otvaranju datoteke.");
		return ERROR;
	}

	while (!feof(f))
	{
		fscanf(f, "%s %s", cntry, cty);

		Root = Read(Root, temp, cntry, cty);
	}

	printTree(Root);
	printf("\n");

	//printf("Unesi ime drzave:");
	//scanf(" %s", optionName);

	//printf("Unesi broj stanovnika:");
	//scanf("%d", &optionNumber);

	//printf("\n");

	//printOption(Head, optionName, optionNumber);

	return SUCCESS;
}

Position Read(Position R, Pos temp, char* name, char* file)
{
	char word[MAX_LINE] = { 0 };
	int number = 0;
	FILE* fp = NULL;
	fp = fopen(file, "r");

	if (NULL == fp)
	{
		Position Q = NULL;
		Q = (Position)malloc(sizeof(tree));

		if (NULL == Q)
		{
			printf("Greska pri alociranju memorije.");
		}

		Q->Left = NULL;
		Q->Right = NULL;
		Q->Down = temp;
		strcpy(Q->country, name);

		R = insertInTree(R, Q);

		return R;
	}

	Position Q = NULL;
	Q = (Position)malloc(sizeof(tree));

	if (NULL == Q)
		printf("Greska pri alociranju memorije.");

	Q->Left = NULL;
	Q->Right = NULL;
	Q->Down = temp;
	strcpy(Q->country, name);

	R = insertInTree(R, Q);

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", word, &number);

		Pos New = NULL;
		New = (Pos)malloc(sizeof(list));

		if (NULL == New)
			printf("Greska pri alociranju memorije.");

		New->Next = NULL;
		New->residents = number;
		strcpy(New->city, word);

		insertInList(Q->Down, New);
	}

	return R;
}

Position insertInTree(Position R, Position N)
{
	if (NULL == R)
		return N;

	if (strcmp(R->country, N->country) < 0)
		R->Right = insertInTree(R->Right, N);

	else if (strcmp(R->country, N->country) > 0)
		R->Left = insertInTree(R->Left, N);

	else
		free(N);

	return R;
}

int insertInList(Pos P, Pos N)
{
	if (NULL == P->Next)
	{
		N->Next = P->Next;
		P->Next = N;
		return SUCCESS;
	}

	while ((P->Next != NULL) && (P->Next->residents > N->residents))
		P = P->Next;

	while (P->Next != NULL && strcmp(P->Next->city, N->city) < 0)
		P = P->Next;

	N->Next = P->Next;
	P->Next = N;

	return SUCCESS;
}

int printTree(Position R)
{
	if (NULL == R)
		return SUCCESS;
		
	printTree(R->Left);
	printf("%s - ", R->country);
	printf("\n");
	printTree(R->Right);

	return SUCCESS;
}

int printList(Pos P)
{
	if (NULL == P)
	{
		printf("ova drzava nema upisanih gradova");
		return SUCCESS;
	}

	while (P != NULL)
	{
		printf("%s %d ", P->city, P->residents);
		P = P->Next;
	}

	return SUCCESS;
}
