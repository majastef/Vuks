#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1
#define MAX 50

struct dir;
typedef struct dir* dPosition;
typedef struct dir
{
	char ime;
	dPosition brother;
	dPosition child;
};

struct stack;
typedef struct stack* sPosition;
typedef struct stack
{
	sPosition direktorij;
	sPosition Next;
	sPosition Prev;
};

int main()
{
	char option[MAX] = { 0 };
	dPosition root = NULL;
	sPosition Head = NULL;
	root = (dPosition)malloc(sizeof(dir));
	Head = (sPosition)malloc(sizeof(stack));

	if (NULL == root || NULL == Head)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	root->brother = NULL;
	root->child = NULL;
	Head->Next = NULL;
	Head->Prev = NULL; 

	while (strcmp(option, "exit") != 0)
	{
		printf("md: dodaj direktorij\ncd: otvori direktorij\ncd..:vrati na prethodni direktorij\ndir:ispis direktorija u trenutnom direktoriju\n");
		printf("\nNaredba:");
		scanf(" %s", option);

		if (strcmp(option, "md") == 0)
		{

		}
	}
	return SUCCESS;
}
