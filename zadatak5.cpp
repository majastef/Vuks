#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define ERROR -2
#define FILE_DIDNT_OPEN_ERROR -1
#define MAX_FILE_NAME 50
#define MAX_LINE 1024

struct stack;
typedef struct stack* Position;
typedef struct stack
{
	int el;
	Position Next;
};

int readFromFile(char*, Position);
int insertList(int, Position);
int calculation(char, Position);

int main()
{
  char filename[MAX_FILE_NAME] = { 0 };
  Position Head = NULL;
  Head = (Position)malloc(sizeof(stack));
  
  if(Head == NULL)
  {
    printf("Greska u alociranju memorije.");
    return ERROR;
  }
  
  Head->Next = NULL;
  
  printf("Unesi ime file-a: ");
  scanf(" %[^\n]", filename);
  
  readFromFile(filename, Head);
  
  return SUCCESS;
}

int readFromFile(char* f, Position P)
{
  int number = 0;
  char symbol = { 0 };
  int n = 0;
  int value = 0;
  char buffer[MAX_LINE] = { 0 };
  char* B = buffer;
  FILE* fp = NULL;
  fp = fopen(f, "r");
  if(fp == NULL)
  {
    printf("Datoteka se nije otvorila.");
    return FILE_DIDNT_OPEN_ERROR; 
  }
  
  fgets(B, MAX_LINE, fp);
  
  while(strlen(B) > 0)
  {
    value = sscanf(B, "%d %n", &number, &n);
    if(value == 1)
      insertList(number, P);
    else 
    {
      sscanf(B, "%s %n", symbol, &n);
      calculation(symbol, Head);
    }  
    B += n;
  }
  return SUCCESS;
}

int insertList(int number, Position P)
{
  Position Q = NULL;
  Q = (Position)malloc(sizeof(stack));
  if(Q == NULL)
  {
    printf("Greska u alociranju memorije.");
    return ERROR;
  }
  
  while(P->Next != NULL)
    P = P->Next;
  
  Q->el = number;
  P->Next = Q;
  Q->Next = NULL;
  
  return SUCCESS;
}

int calculation(char* symbol, Position P)
{
  Position temp = NULL;
  while()
  
  return SUCCESS;
}
