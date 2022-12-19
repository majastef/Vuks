#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (50)
#define SUCCESS (0)
#define ERROR (-1)

struct tree;
typedef struct tree* Position;
typedef struct tree
{
	int br;
	Position left;
	Position right;
};

Position insertNew(Position);
int printInOrder(Position);
int printPreOrder(Position);
int printPostOrder(Position);
int printLevelOrder(Position);
Position deleteEl(Position, int);
Position findMax(Position);
Position findMin(Position);
Position findEl(Position, int);

int main()
{
	char option = { 0 };
	int number = 0;
	int element = 0;

	Position root = NULL;
	root = (Position)malloc(sizeof(tree));

	if (root == NULL)
	{
		printf("Greska u alociranju!");
		return ERROR;
	}

	root->right = NULL;
	root->left = NULL;

	do
	{
		printf("a) Unos novog elementa\nb) Ispis inorder\nc) Ispis preorder\nd) Ispis postorder\ne) Ispis level order\nf) Brisanje elementa\ng)Pronalazenje elementa\nh) Kraj!\n ");
		scanf("%c", &option);

		switch (option)
		{
			case 'a':
			{
				printf("Unesi broj koji zelis dodati: ");
				scanf("&d", &number);

				root = insertNew(root);
			}
			case 'b':
			{
				printInOrder(root);
			}
			case 'c':
			{
				printPreOrder(root);
			}
			case 'd':
			{
				printPostOrder(root);
			}
			case 'e':
			{
				printLevelOrder(root);
			}
			case 'f':
			{
				printf("Unesite broj koji zelite obrisati: ");
				scanf("%d", &element);
				root = deleteEl(root, element);
			}
			case 'g':
			{
				printf("Unesite broj koji zelite pronaci: ");
				scanf("%d", &element);
				findEl(root, element);
			}
		}
	} while (strcmp(option,"h") != 0);
	
	return SUCCESS;
}

Position insertNew(Position P)
{
	Position Q = NULL;
	Q = (Position)malloc(sizeof(tree));

	if (NULL == P)
		return Q;
	if (P->br < Q->br)
		P->right = insertNew(P->right);
	else if (P->br > Q->br)
		P->left = insertNew(P->left);
	else
		free(Q);

	return P;
}

int printfInOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printInOrder(P->left);
	printf("%d", P->br);
	printInOrder(P->right);

	return SUCCESS;
}

int printPreOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printf("%d", P->br);
	printPreOrder(P->left);
	printPreOrder(P->right);

	return SUCCESS;
}

int printPostOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printPostOrder(P->left);
	printPostOrder(P->right);
	printf("%d", P->br);

	return SUCCESS;
}

int printLevelOrder(Position P)
{
	return SUCCESS;
}

Position deleteEl(Position P, int el)
{
	if (NULL == P)
		return NULL;

	if (P->br < el)
		P->right = deleteEl(P->right, el);
	else if (P->br > el)
		P->left = deleteEl(P->left, el);
	else
	{
		if (P->left)
		{
			Position temp = findMax(P->left);
			P->br = temp->br;
			P->left = deleteEl(P->left, temp->br);
		}

		else if (P->right)
		{
			Position temp = findMin(P->right);
			P->br = temp->br;
			P->right = deleteEl(P->right, temp->br);
		}

		else
		{
			free(P);
			return NULL;
		}
	}
	return P;
}

Position findMax(Position P)
{
	if (NULL == P)
	{
		return NULL;
	}
	else if (P->right == NULL)
	{
		return P;
	}
	else
		return findMax(P->right);
}

Position findMin(Position P)
{
	if (NULL == P)
	{
		return NULL;
	}
	else if (P->left == NULL)
	{
		return P;
	}
	else
		return findMin(P->left);
}

Position findEl(Position P, int el)
{
	if (NULL == P)
		return NULL;
	else if (el < P->br)
		return findEl(P->left, el);
	else if (el > P->br)
		return findEl(P->right, el);
	else
		return P;
}
