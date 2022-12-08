#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define ERROR -1
#define FILE_DIDNT_OPEN_ERROR -2
#define MAX_FILE_NAME 50
#define MAX_LINE 1024

struct stack;
typedef struct stack* Position;
typedef struct stack
{
    int el;
    Position Next;
};

int push(Position, int);
int pop(Position);
int readFromFile(char*, Position);

int main()
{
    int rez = 0;
    char filename[MAX_FILE_NAME] = { 0 };
    Position Head = NULL;
    Head = (Position)malloc(sizeof(stack));

    if (Head == NULL)
    {
        printf("Greska u alociranju memorije.");
        return ERROR;
    }

    Head->Next = NULL;

    printf("Unesi ime file-a: ");
    scanf(" %s", filename);

    rez = readFromFile(filename, Head);
    if(rez>0)
        printf("Rezultat je %d.", rez);

    return SUCCESS;
}

int readFromFile(char* f, Position P)
{
    int x = 0;
    int number = 0;
    char symbol[MAX_LINE] = {0};
    int n = 0;
    int value = 0;
    int first = 0, second = 0, result = 0;
    char buffer[MAX_LINE] = { 0 };
    char* B = buffer;
    FILE* fp = NULL;
    fp = fopen(f, "r");
    if (fp == NULL)
    {
        printf("Datoteka se nije otvorila.");
        return FILE_DIDNT_OPEN_ERROR;
    }

    fgets(B, MAX_LINE, fp);

    while (strlen(B) > 0)
    {
        value = sscanf(B, "%d %n", &number, &n);
        if (value == 1)
            push(P, number);
        else
        {
           sscanf(B, "%c %n", symbol, &n);
            if (strcmp(symbol, "+") == 0)
            {
                first = pop(P);
                second = pop(P);
                result = first + second;
                push(P, result);
            }

            else if (strcmp(symbol, "-") == 0)
            {
                first = pop(P);
                second = pop(P);
                result = second - first;
                push(P, result);
            }

            else if (strcmp(symbol, "*") == 0)
            {
                first = pop(P);
                second = pop(P);
                result = second * first;
                push(P, result);
            }

            else if (strcmp(symbol, "/") == 0)
            {
                first = pop(P);
                second = pop(P);
                result = second / first;
                push(P, result);
            }

            else
            {
                printf("Krivo napisan postfix izraz!");
                return ERROR;
            }
        }
        B += n;
    }

    x = P->Next->el;
    return x;
}

int push(Position P, int newel)
{
    Position Q = NULL;
    Q = (Position)malloc(sizeof(stack));

    if (Q == NULL)
    {
        printf("Greska u alociranju memorije.");
        return ERROR;
    }

    Q->el = newel;
    Q->Next = P->Next;
    P->Next = Q;

    return SUCCESS;
}

int pop(Position P)
{
    int x = 0;
    Position temp = NULL;
    temp = P->Next;
    while (P->Next != NULL)
    {
        P = P->Next;
        temp = temp->Next;
    }

    x = temp->el;
    P->Next = temp->Next;
    free(temp);
    return SUCCESS;
}
