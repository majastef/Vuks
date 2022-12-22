#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define ERROR -1
#define MAX 50

struct tree;
typedef struct tree* Position;
typedef struct tree
{
	int br;
	Position left;
	Position right;
};

Position insertNew(Position, Position);
int printInOrder(Position);
int printPreOrder(Position);
int printPostOrder(Position);
int printLevelOrder(Position);
Position deleteEl(Position, int);
Position findEl(Position, int);
Position findMax(Position);
Position findMin(Position);
int height(Position);
int printThisLevel(Position, int);
int deleteAll(Position);

int main()
{
	char option[MAX] = { 0 };
	int number = 0;
	Position root = NULL;

	while (strcmp(option, "h") != 0)
	{
		printf("a) Unos novog elementa\nb) Ispis inorder\nc) Ispis preorder\nd) Ispis postorder\ne) Ispis level order\nf) Brisanje elementa\ng) Pronalazenje elementa\nh) Kraj!\n");
		printf("\nOdaberi opciju:");
		scanf(" %[^\n]", option);

		if (strcmp(option, "a") == 0)
		{
			Position Q = NULL;
			Q = (Position)malloc(sizeof(tree));

			if (NULL == Q)
				return ERROR;

			Q->right = NULL;
			Q->left = NULL;

			printf("Unesi broj:");
			scanf("%d", &number);

			Q->br = number;

			root = insertNew(root, Q);
			printf("\n");
		}

		else if (strcmp(option, "b") == 0)
		{
			if (NULL == root)
				printf("Lista je prazna.\n");

			else
				printInOrder(root);

			printf("\n");
		}

		else if (strcmp(option, "c") == 0)
		{
			if (NULL == root)
				printf("Lista je prazna.\n");

			else
				printPreOrder(root);

			printf("\n");
		}

		else if (strcmp(option, "d") == 0)
		{
			if (NULL == root)
				printf("Lista je prazna.\n");

			else
				printPostOrder(root);

			printf("\n");
		}

		else if (strcmp(option, "e") == 0)
		{
			if (NULL == root)
				printf("Lista je prazna.\n");

			else 
				printLevelOrder(root);

			printf("\n");
		}

		else if (strcmp(option, "f") == 0)
		{
			printf("Unesi broj koji zelis obrisati:");
			scanf("%d", &number);
			root = deleteEl(root, number);
			printf("\n");
		}

		else if (strcmp(option, "g") == 0)
		{
			Position El = NULL;
			printf("Unesite broj koji zelite pronaci:");
			scanf("%d", &number);
			El = findEl(root, number);

			if (NULL == El)
				printf("Element ne postoji.\n");
	
			else
				printf("Element postoji.\n");

			printf("\n");
		}

		else if (strcmp(option, "h") == 0)
		{
			deleteAll(root);
			printf("\nKraj!\n");
			return SUCCESS;
		}

		else
		{
			printf("Ta opcija ne postoji.\n");
			printf("\n");
		}
	}

	return SUCCESS;
}

Position insertNew(Position P, Position Q)
{
	if (NULL == P)
		return Q;

	if (P->br < Q->br)
		P->right = insertNew(P->right, Q);
	else if (P->br > Q->br)
		P->left = insertNew(P->left, Q);
	else
		free(Q);

	return P;
}

int printInOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printInOrder(P->left);
	printf("%d ", P->br);
	printInOrder(P->right);

	return SUCCESS;
}

int printPreOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printf("%d ", P->br);
	printInOrder(P->left);
	printInOrder(P->right);

	return SUCCESS;
}

int printPostOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printInOrder(P->left);
	printInOrder(P->right);
	printf("%d ", P->br);

	return SUCCESS;
}

int printLevelOrder(Position P)
{
	int h = height(P);
	int i = 0;
	for (i = h; i >= 1; i--)
	{
		printThisLevel(P, i);
		printf("\n");
	}


	return SUCCESS;
}

int height(Position P)
{
	int Left = 0;
	int Right = 0;
	if (NULL == P)
		return SUCCESS;
	else
	{
		Left = height(P->left);
		Right = height(P->right);

		if (Left > Right)
			return(Left + 1);
		else
			return(Right + 1);
	}
}

int printThisLevel(Position P, int level)
{
	if (NULL == P)
		return SUCCESS;
	if (1 == level)
		printf("%d ", P->br);
	else if (level > 1)
	{
		printThisLevel(P->left, level - 1);
		printThisLevel(P->right, level - 1);
	}
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

Position findEl(Position P, int el)
{
	if (NULL == P)
		return NULL;

	if (el < P->br)
		return findEl(P->left, el);
	else if (el > P->br)
		return findEl(P->right, el);
	else
		return P;
}

int deleteAll(Position P)
{
	if (NULL == P)
		return SUCCESS;

	deleteAll(P->left);
	deleteAll(P->right);
	free(P);

	return SUCCESS;
}
