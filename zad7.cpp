#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define ERROR -1
#define SUCCESS 0

struct Directory;
typedef struct Directory* DPosition;
typedef struct Directory
{
	char name[MAX];
	DPosition child;
	DPosition sibling;
};

struct Stack;
typedef struct Stack* SPosition;
typedef struct Stack
{
	DPosition dir;
	SPosition Next;
};

int Menu(DPosition, DPosition, DPosition, SPosition);
int makeDirectory(DPosition, char*);
int printDirectory(DPosition);
DPosition findDirectory(DPosition, char*,SPosition);
int Push(DPosition, SPosition);
DPosition returnToPrev(SPosition);
DPosition Pop(SPosition);
int DeleteAll(DPosition);

int main()
{
	DPosition root = NULL;

	if (NULL == root)
	{
		printf("Greska u alociranju memorije!");
	}

	root->child = NULL;
	root->sibling = NULL;

	return SUCCESS;
}

int Menu(DPosition root, DPosition current, DPosition previous, SPosition st)
{
	char option[MAX] = { 0 };
	char directoryName[MAX] = { 0 };

	do {
		printf("Izaberite:\nmd: dodaj direktorij\ncd : otvori direktorij\ncd..:vrati na prethodni direktorij\ndir : ispis direktorija u trenutnom direktoriju\n");
		scanf(" %s", option);

		if (strcmp(option, "md") == 0)
		{
			printf("Ime direktorija:");
			scanf(" %s", directoryName);
			makeDirectory(root, directoryName);
		}
		else if (strcmp(option, "dir") == 0)
		{
			printDirectory(root);
		}
		else if (strcmp(option, "cd") == 0)
		{
			current = findDirectory(root, directoryName,st);
		}
		else if (strcmp(option, "cd dir") == 0)
		{
			previous = returnToPrev(st);
		}
	}while(strcmp(option,"exit")!=0);

	DeleteAll(root);
	return SUCCESS;
}

int makeDirectory(DPosition current, char* nameNewDir)
{
	DPosition newDirectory;
	newDirectory = (DPosition)malloc(sizeof(Directory));

	if (NULL == newDirectory)
	{
		printf("Greska u alociranju memorije!");
		return ERROR;
	}

	newDirectory->child = NULL;
	newDirectory->sibling = NULL;
	strcpy(newDirectory->name, nameNewDir);

	if (current->child == NULL) {
		current->child = newDirectory;
	}

	else {
		if (strcmp(current->child->name, nameNewDir) > 0) {
			newDirectory->child = current->child;
			current->child = newDirectory;
		}
		else {
			current = current->child;
			while (strcmp(current->sibling->name, nameNewDir) < 0)
				current = current->sibling;
			newDirectory->sibling = newDirectory;
			current->sibling = newDirectory;
		}
	}
	
	return SUCCESS;
}

int printDirectory(DPosition current)
{
	if (current->child == NULL) {
		printf("Direktorij je prazan!");
		return SUCCESS;
	}
	current = current->child;


	return SUCCESS;
}

DPosition findDirectory(DPosition current, char* nameNewDir,SPosition p)
{
	current = current->child;
	if (strcmp(current->name, nameNewDir) == 0)
		return current;

	while (current != NULL && strcmp(current->name, nameNewDir) != 0)
		current = current->sibling;

	if (current == NULL || strcmp(current->name, nameNewDir) != 0)
	{
		printf("Direktorij nije pronaden!");
		return current;
	}

	else Push(current, p);

	return current;
}

int Push(DPosition current, SPosition shead)
{
	SPosition NewEl = NULL;
	NewEl = (SPosition)malloc(sizeof(Stack));

	if (NewEl == NULL)
	{
		printf("Greska u alociranju!");
		return ERROR;
	}

	NewEl->dir = current;
	NewEl->Next = shead->Next;
	shead->Next = NewEl;

	return SUCCESS;
}

DPosition returnToPrev(SPosition s)
{
	return Pop(s);
}

DPosition Pop(SPosition head)
{
	if (head->Next == NULL)
	{
		printf("Stog je prazan!");
		return NULL;
	}

	SPosition temp = head->Next;
	DPosition ReturnedEl = head->Next->dir;
	head->Next = temp->Next;
	free(temp);

	return ReturnedEl;
}

int DeleteAll(DPosition)
{

	return SUCCESS;
}
