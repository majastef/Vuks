#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

#define ERROR (-1)
#define SUCCESS (0)

struct osoba;
typedef struct osoba* Pozicija;
typedef struct osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godina;
	Pozicija Next;
};

int Unos(Pozicija);
int UnosPocetak(Pozicija);
int UnosKraj(Pozicija);
int IspisListe(Pozicija);
Pozicija PronadiElement(char*, Pozicija);
int BrisiElement(char*, Pozicija);
Pozicija TraziPrethodnog(char*, Pozicija);
int UnosIza(char*, Pozicija);
int UnosIspred(char*, Pozicija);
int BrisiSve(Pozicija);



int main()
{
	char prez[MAX] = { 0 };
	Pozicija Head = NULL;
	Head = (Pozicija)malloc(sizeof(osoba));
	Head->Next = NULL;

	printf("Unos na pocetak liste:\n");
	UnosPocetak(Head);


	printf("Unos na kraj liste:\n");
	UnosKraj(Head);

	IspisListe(Head->Next);

	printf("Brisanje korisnika!\n");
	printf("Unesite prezime korisnika:\n");
	scanf(" %[^\n]", prez);
	BrisiElement(prez, Head);
	IspisListe(Head->Next);

	printf("Unos nove osobe!\n");
	printf("Unesi prezime osobe iza koje zelis unijeti novu osobu:");
	scanf(" %[^\n]", prez);
	UnosIza(prez, Head);
	IspisListe(Head->Next);

	printf("Unos nove osobe!\n");
	printf("Unesi prezime osobe ispred koje zelis unijeti novu osobu:");
	scanf(" %[^\n]", prez);
	UnosIspred(prez, Head);
	IspisListe(Head->Next);

	BrisiSve(Head);

	return SUCCESS;
}


int UnosPocetak(Pozicija P)
{
	Pozicija Q = NULL;
	Q = (Pozicija)malloc(sizeof(osoba));
	if (Q == NULL)
	{
		printf("Greska u alociranju!");
		return ERROR;
	}
	Unos(Q);

	Q->Next = P->Next;
	P->Next = Q;

	return SUCCESS;
}

int UnosKraj(Pozicija P)
{
	Pozicija Q = NULL;
	Q = (Pozicija)malloc(sizeof(osoba));
	if (Q == NULL)
	{
		printf("Greska u alociranju!");
		return ERROR;
	}
	Unos(Q);

	while (P->Next != NULL)
		P = P->Next;

	Q->Next = P->Next;
	P->Next = Q;

	return SUCCESS;
}

Pozicija PronadiElement(char* x, Pozicija P)
{
	while (P != NULL && strcmp(P->prezime, x))
		P = P->Next;

	return P;
}

int Unos(Pozicija Q)
{
	printf("Ime:");
	scanf(" %[^\n]", Q->ime);
	printf("Prezime:");
	scanf(" %[^\n]", Q->prezime);
	printf("Godina:");
	scanf("%d", &Q->godina);
	return SUCCESS;
}


int IspisListe(Pozicija P)
{
	if (P == NULL)
	{
		printf("Lista je prazna!");
		return ERROR;
	}

	while (P != NULL)
	{
		printf("\nIme: %s\nPrezime: %s\nGodina rodenja:%d\n", P->ime, P->prezime, P->godina);
		printf("\n");
		P = P->Next;
	}
	return SUCCESS;
}

Pozicija TraziPrethodnog(char* x, Pozicija P)
{
	Pozicija Pret = P;
	P = P->Next;
	while (P != NULL && strcmp(P->prezime, x))
	{
		Pret = Pret->Next;
		P = P->Next;
	}

	if (P == NULL)
		return NULL;
	else
		return Pret;
}

int BrisiElement(char* x, Pozicija P)
{
	Pozicija Pret, temp;
	Pret = TraziPrethodnog(x, P);
	if (Pret->Next == NULL)
	{
		printf("Nema prethodnika!");
		return ERROR;
	}

	temp = Pret->Next;
	Pret->Next = temp->Next;
	free(temp);

	return SUCCESS;
}

int UnosIza(char* x, Pozicija P)
{
	Pozicija Q;
	P = PronadiElement(x, P);
	
	if (P == NULL)
	{
		printf("Element ne postoji.");
		return ERROR;
	}

	else
	{
		Q = (Pozicija)malloc(sizeof(osoba));
		Unos(Q);
		Q->Next = P->Next;
		P->Next = Q;
	}
	return SUCCESS;
}

int UnosIspred(char* x, Pozicija P)
{
	Pozicija Q;
	P = TraziPrethodnog(x, P);
	if (P == NULL)
	{
		printf("Element ne postoji.");
		return ERROR;
	}

	else
	{
		Q = (Pozicija)malloc(sizeof(osoba));
		Unos(Q);
		Q->Next = P->Next;
		P->Next = Q;
	}
	return SUCCESS;
}

int BrisiSve(Pozicija P)
{
	Pozicija temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	free(P);
	return SUCCESS;
}