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
int BrojElemenataListe(Pozicija);
int SortiranjeListe(Pozicija);

int main()
{
	char prez[MAX] = { 0 };
	Pozicija Head = NULL;
	Head = (Pozicija)malloc(sizeof(osoba));
	Head->Next = NULL;

	char opcija[MAX] = { 0 };

	while (strcmp(opcija, "i") != 0)
	{
		printf("\na) Unos na pocetak liste\nb) Unos na kraj liste\nc) Ispis liste\nd) Brisi element\ne) Unos iza nekog elementa\nf) Unos ispred nekog elementa\ng) Broj elemenata u listi\nh) Sortiranje liste\ni) Kraj\n");
		printf("\nOdaberi opciju:");
		scanf(" %s", &opcija);

		if (strcmp(opcija, "a") == 0)
		{
			UnosPocetak(Head);
		}

		else if (strcmp(opcija, "b") == 0)
		{
			UnosKraj(Head);
		}

		else if (strcmp(opcija, "c") == 0)
		{
			IspisListe(Head->Next);
		}

		else if (strcmp(opcija, "d") == 0)
		{
			printf("Unesite prezime korisnika kojeg zelite obrisati:");
			scanf(" %[^\n]", prez);
			BrisiElement(prez, Head);
		}

		else if (strcmp(opcija, "e") == 0)
		{
			printf("Unesi prezime osobe iza koje zelis unijeti novu osobu:");
			scanf(" %[^\n]", prez);
			UnosIza(prez, Head);
		}

		else if (strcmp(opcija, "f") == 0)
		{
			printf("Unesi prezime osobe ispred koje zelis unijeti novu osobu:");
			scanf(" %[^\n]", prez);
			UnosIspred(prez, Head);
		}

		else if (strcmp(opcija, "g") == 0)
		{
			int BrojEl = 0;
			BrojEl = BrojElemenataListe(Head);
			if (BrojEl > 0)
				printf("Broj elemenata liste: %d\n", BrojEl);
		}

		else if (strcmp(opcija, "h") == 0)
		{
			int n = 0;
			n = BrojElemenataListe(Head);
			SortiranjeListe(Head);
		}

		else if (strcmp(opcija, "i") == 0)
		{
			BrisiSve(Head);
			printf("\nKraj!\n");
			return SUCCESS;
		}

		else
			printf("Ta opcija ne postoji!\n");
	}
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
	printf("\nUnesi ime:");
	scanf(" %[^\n]", Q->ime);
	printf("Unesi prezime:");
	scanf(" %[^\n]", Q->prezime);
	printf("Unesi godinu rodenja:");
	scanf("%d", &Q->godina);
	return SUCCESS;
}


int IspisListe(Pozicija P)
{
	if (P == NULL)
	{
		printf("Lista je prazna!\n");
		return ERROR;
	}

	printf("\nLista:\n");
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

int BrojElemenataListe(Pozicija P)
{
	int brojac = 0;

	while (P->Next != NULL)
	{
		brojac++;
		P = P->Next;
	}

	if (brojac == 0)
	{
		printf("Lista je prazna!\n");
		return SUCCESS;
	}

	else if (brojac < 0)
	{
		return ERROR;
	}

	else
		return brojac;
}

int SortiranjeListe(Pozicija P)
{
	Pozicija j = NULL, prev_j = NULL, temp = NULL, end = NULL;

	while (P->Next != end)
	{
		prev_j = P;
		j = P->Next;
		while (j->Next != end)
		{
			if (strcmp(j->prezime, j->Next->prezime) > 0)
			{
				temp = j->Next;
				prev_j->Next = temp;
				j->Next = temp->Next;
				temp->Next = j;

				j = temp;
			}

			prev_j = j;
			j = j->Next;
		}
		end = j;
	}
	return SUCCESS;
}