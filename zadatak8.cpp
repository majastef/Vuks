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
Position findMax(Position);
Position findMin(Position);

int main()
{
	char option[MAX] = { 0 };
	int number = 0;
	int element = 0;
	Position root = NULL;
	root = (Position)malloc(sizeof(tree));

	if (NULL == root)
	{
		printf("Greska u alociranju memorije.");
		return ERROR;
	}

	root->left = NULL;
	root->right = NULL;

	while (strcmp(option, "h") != 0)
	{
		printf("a) Unos novog elementa\nb) Ispis inorder\nc) Ispis preorder\nd) Ispis postorder\ne) Ispis leve lorder\nf) Brisanje elementa\ng) Pronalazenje elementa\nh) Kraj!\n");
		printf("Odaberi opciju:");
		scanf(" %s", option);

		if (strcmp(option, "a") == 0)
		{
			printf("Unesi broj:");
			scanf("%d", &number);

			Position El = NULL;
			El = (Position)malloc(sizeof(tree));
			El->br = number;
			
			root = insertNew(root, El);
		}

		else if (strcmp(option, "b") == 0)
		{
			printInOrder(root);
		}

		else if (strcmp(option, "c") == 0)
		{
			printPreOrder(root);
		}

		else if (strcmp(option, "d") == 0)
		{
			printPostOrder(root);
		}

		else if (strcmp(option, "e") == 0)
		{
			printLevelOrder(root);
		}

		else if (strcmp(option, "f"))
		{
			printf("Unesi broj koji zelis obrisati:");
			scanf("%d", &element);
			root = deleteEl(root, element);
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
	printf("%d", P->br);
	printInOrder(P->right);

	return SUCCESS;
}

int printPreOrder(Position P)
{
	if (NULL == P)
		return SUCCESS;

	printf("%d", P->br);
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
	printf("%d", P->br);

	return SUCCESS;
}

int printLevelOrder(Position P)
{

}

int findMax(Position P)
{

}

int findMin(Position P)
{

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
