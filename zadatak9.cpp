#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1
#define MAX 50

struct tree;
typedef struct tree* Position;
typedef struct tree
{
	int br;
	Position Left;
	Position Right;
};

struct stack;
typedef struct stack* Pos;
typedef struct stack
{
	int br;
	Pos Next;
};

Position insert(Position, Position);
int printInOrder(Position);
int replace(Position);
int add(Position, int);
int read(Pos, Position);
int insertFile(char*, Pos);
int deleteAllTree(Position);
int deleteAllStack(Pos);

int main()
{
	char file_name[MAX] = { 0 };
	Position Root = NULL;
	Pos Head = NULL;
	Head = (Pos)malloc(sizeof(stack));

	if (NULL == Head)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	Head->Next = NULL;

	int i = 0;
	int line[10] = { 2,5,7,8,11,1,4,2,3,7 };

	while (i < 10)
	{
		Position Q = NULL;
		Q = (Position)malloc(sizeof(tree));

		if (NULL == Q)
		{
			printf("Greška u alociranju memorije.");
			return ERROR;
		}

		Q->Left = NULL;
		Q->Right = NULL;
		Q->br = line[i];

		Root = insert(Root, Q);

		i++;
	}

	read(Head, Root);

	printf("Unesi ime datoteke u koju zelis spremiti brojeve nakon prvog dijela zadatka:");
	scanf(" %s", file_name);

	insertFile(file_name, Head);

	deleteAllStack(Head);

	replace(Root);

	read(Head, Root);

	printf("Unesi ime datoteke u koju zelis spremiti brojeve nakon drugog dijela zadatka:");
	scanf(" %s", file_name);

	insertFile(file_name, Head);

	deleteAllTree(Root);
	deleteAllStack(Head);
	free(Head);

	return SUCCESS;
}

Position insert(Position P, Position Q)
{
	if (NULL == P)
		return Q;

	if (P->br > Q->br)
		P->Right = insert(P->Right, Q);
	else if ((P->br < Q->br) || (P->br == Q->br))
		P->Left = insert(P->Left, Q);

	return P;
}

int printInOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printInOrder(P->Left);
	printf("%d ", P->br);
	printInOrder(P->Right);

	return SUCCESS;
}

int replace(Position P)
{
	if (NULL == P)
		return SUCCESS;

	int zbr = 0;
	zbr = add(P, zbr) - P->br;

	P->br = zbr;

	replace(P->Left);
	replace(P->Right);

	return SUCCESS;
}

int add(Position P, int number)
{
	if (NULL == P)
		return SUCCESS;

	int left = 0;
	int right = 0;

	left = add(P->Left, number);
	right = add(P->Right, number);
	number += left + right;

	if (number == 0)
		return P->br;
	
	else
		return (number + P->br);
}

int read(Pos S, Position P)
{
	if (NULL == P)
		return SUCCESS;

	read(S, P->Left);

	Pos Q = NULL;
	Q = (Pos)malloc(sizeof(stack));

	if (NULL == Q)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	Q->Next = NULL;
	Pos temp = S;

	while (temp->Next != NULL)
		temp = temp->Next;

	Q->Next = temp->Next;
	temp->Next = Q;
	Q->br = P->br;
	
	read(S, P->Right);

	return SUCCESS;
}

int insertFile(char* f, Pos P)
{
	FILE* file = NULL;
	int i = 0;
	file = fopen(f, "w");

	if (NULL == file)
	{
		printf("Greska pri otvaranju datoteke.");
		return ERROR;
	}

	while(i<10)
	{
		fprintf(file, "%d ", P->Next->br);
		P = P->Next;
		i++;
	}

	fclose(file);
}

int deleteAllTree(Position P)
{
	if (NULL == P)
		return SUCCESS;

	deleteAllTree(P->Left);
	deleteAllTree(P->Right);
	free(P);

	return SUCCESS;
}

int deleteAllStack(Pos P)
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
