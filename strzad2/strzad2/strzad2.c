#define <stdio.h>

#define MAX_NAME (1024)
#define EXIT_SUCCESS (0)

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
	char ime [MAX_NAME];
	char prezime [MAX_NAME];
	int godrodenja;
	Pozicija next;
}osoba;

int insertBefore(osoba, Pozicija);
int ispisListe(Pozicija);

int main()
{
	osoba head = {
		.ime = {0},
		.prezime = {0},
		.godrodenja = 0,
		.next = NULL
	};
	
	Pozicija p = &head;
	osoba* nova_osoba = NULL;

	insertBefore(nova_osoba, p);
	ispisListe(p);

	return EXIT_SUCCESS;
}

int inertBefore(osoba nova_osoba, Pozicija p)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(struct osoba));

	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int ispisListe(Pozicija p)
{
	while (p != NULL)
	{
		printf("Ime: %s, Prezime: %s, Godina rođenja: %d", p->ime, p->prezime, p->godrodenja);
		p = p->next;
	}
	
	return EXIT_SUCCESS;
}