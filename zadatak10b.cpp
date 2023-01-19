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
int printOption(Position, char*, int);
int printCities(Pos, int);
int deleteAll(Position);
int deleteList(Pos);

int main()
{
	char optionName[MAX_LINE] = { 0 };
	int optionNumber = 0;
	Position Root = NULL;
	Pos Head = NULL;

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

		Root = Read(Root, Head, cntry, cty);
	}

	printTree(Root);
	printf("\n");

	printf("Unesi ime drzave:");
	scanf(" %s", optionName);

	printf("Unesi broj stanovnika:");
	scanf("%d", &optionNumber);

	printf("\n");

	printOption(Root, optionName, optionNumber);

	deleteAll(Root);

	return SUCCESS;
}

Position Read(Position R, Pos P, char* name, char* file)
{
	char word[MAX_LINE] = { 0 };
	int number = 0;
	FILE* fp = NULL;
	fp = fopen(file, "r");

	if (NULL == fp)
	{
		P = (Pos)malloc(sizeof(list));
		Position Q = NULL;
		Q = (Position)malloc(sizeof(tree));

		if (NULL == Q && NULL == P)
			printf("Greska pri alociranju memorije.");

		P->Next = NULL;
		Q->Left = NULL;
		Q->Right = NULL;
		Q->Down = P;
		strcpy(Q->country, name);

		R = insertInTree(R, Q);

		return R;
	}

	P = (Pos)malloc(sizeof(list));
	Position Q = NULL;
	Q = (Position)malloc(sizeof(tree));

	if (NULL == Q && NULL == P)
		printf("Greska pri alociranju memorije.");

	P->Next = NULL;
	Q->Left = NULL;
	Q->Right = NULL;
	Q->Down = P;
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

	if (P->Next != NULL && P->Next->residents == N->residents)
	{
		while (P->Next != NULL && strcmp(P->Next->city, N->city) > 0)
			P = P->Next;
	}

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
	printList(R->Down->Next);
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

int printOption(Position R, char* name, int number)
{
	if (NULL == R)
		return SUCCESS;

	if (strcmp(R->country, name) < 0)
		printOption(R->Right, name, number);

	else if (strcmp(R->country, name) > 0)
		printOption(R->Left, name, number);

	else
		printCities(R->Down->Next, number);

	return SUCCESS;
}

int printCities(Pos P, int number)
{
	while (P != NULL)
	{
		if (P->residents > number)
			printf("%s\n", P->city);
		P = P->Next;
	}

	return SUCCESS;
}

int deleteAll(Position R)
{
	if (NULL == R)
		return SUCCESS;

	deleteAll(R->Left);
	deleteAll(R->Right);
	deleteList(R->Down);
	free(R->Down);
	free(R);
	return SUCCESS;
}

int deleteList(Pos P)
{
	Pos temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}

	return SUCCESS;
}
