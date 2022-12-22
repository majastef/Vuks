#define _CRT_SECURE_NO_WARNINGS
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
DPosition findDirectory(DPosition, char*, SPosition);
int Push(DPosition, SPosition);
DPosition returnToPrev(SPosition);
DPosition Pop(SPosition);
int DeleteAll(DPosition);

int main()
{
	char option[MAX] = { 0 };

	DPosition root = NULL;
	DPosition current = NULL; 
	DPosition prev = NULL;
	//root.child = NULL;
	//root.sibling = NULL;
	//current.child = NULL;
	//current.sibling = NULL;
	/*prev.child = NULL;
	prev.sibling = NULL;*/
	/*DPosition pRoot = &root;*/

	SPosition head = NULL;
	head = (SPosition)malloc(sizeof(Stack));

	if (NULL == head)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	head->Next = NULL;

	Menu(root, current, prev, head);

	return SUCCESS;
}

int Menu(DPosition root, DPosition current, DPosition previous, SPosition st)
{
	char option[MAX] = { 0 };
	char directoryName[MAX] = { 0 };

	do {
		printf("md -> dodaj direktorij\ncd -> otvori direktorij\ncd.. -> vrati na prethodni direktorij\ndir -> ispis direktorija u trenutnom direktoriju\nexit -> exit console\n");
		printf("\nIzaberite funkciju:");
		scanf(" %s", option);

		if (strcmp(option, "md") == 0)
		{
			printf("Ime direktorija:");
			scanf(" %s", directoryName);
			makeDirectory(root, directoryName);
			printf("\n");
		}

		else if (strcmp(option, "cd") == 0)
		{
			printf("Unesi ime direktorija kojeg zelis otvoriti:");
			scanf(" %s", directoryName);

			current = findDirectory(root, directoryName, st);
			
			if (NULL == current)
			{
				printf("Direktorij nije pronaden!");
			}

			else
			{
				printf("Nalazite se u %s direktoriju.", directoryName);
			}

		}

		else if (strcmp(option, "cd..") == 0)
		{
			previous = returnToPrev(st);
		}

		else if (strcmp(option, "dir") == 0)
		{
			printDirectory(root);
		}

		else if (strcmp(option, "exit") != 0)
		{
			printf("Ta opcija ne postoji.");
		}

	} while (strcmp(option, "exit") != 0);

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

	if (current == NULL) {
		current = newDirectory;
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
	printf("Directory of C:\\users %s\n", current->name);

	printf("%s\n", current->name);
	while (current->sibling != NULL)
	{
		printf("%s\n", current->sibling->name);
		current = current->sibling;
	}

	return SUCCESS;
}

DPosition findDirectory(DPosition current, char* nameNewDir, SPosition p)
{
	if (strcmp(current->name, nameNewDir) == 0)
		return current;

	current = current->child;

	while (current != NULL && strcmp(current->name, nameNewDir) != 0)
		current = current->child;
		

	if (current == NULL || strcmp(current->name, nameNewDir) != 0)
	{
		return NULL;
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

int DeleteAll(DPosition Root)
{
	if (NULL == Root)
	{
		return SUCCESS;
	}

	DeleteAll(Root->child);
	DeleteAll(Root->sibling);
	free(Root);

	return SUCCESS;
}
