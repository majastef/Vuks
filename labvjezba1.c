#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS (0)
#define FILE_DIDNT_OPEN_ERROR (-1)
#define DID_NOT_ALLOCATE (-2)
#define MAX_FILE_NAME (256)
#define MAX_LINE (1024)

typedef struct {
	char ime[MAX_FILE_NAME];
	char prezime[MAX_FILE_NAME];
	int bodovi;
}student;

int brojStudenata(char* );
void UcitajStudente(char* , int , student*);
void IspisiStudente(int , student*);

int main()
{
	int br_stud = 0;
	student* stud = NULL;
	char f[MAX_FILE_NAME] = { 0 };

	printf("Unesi ime datoteke: ");
	scanf(" %s", f);

	br_stud = brojStudenata(f);
	printf("Broj studenata u datoteci %s je %d", f, br_stud);
	
	stud = (student*)malloc(br_stud * (sizeof(student)));
	
	if (stud == NULL)
	{
		printf("Greška pri alociranju memorije!");
		return DID_NOT_ALLOCATE;
	}

	UcitajStudente(F, br_stud, stud);
	IspisiStudente(br_stud, stud);
	
	free(stud);

	return EXIT_SUCCESS;
}

int UcitajStudente(char* file, int broj, student* s)
{
	int i = 0;
	FILE* f = NULL;
	f = fopen(file, "r");
	
	if (f == NULL)
	{
		printf("Greška pri otvaranju datoteke!");
		return FILE_DIDNT_OPEN_ERROR;
	}

	for (i = 0;i < broj;i++)
	{
		fscanf(f, "%s %s %d", (s + i)->ime, (s + i)->prezime, &(s + i)->bodovi);
	}

	fclose(f);
	return EXIT_SUCCESS;

}

int brojStudenata(char* f) {
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = {0};

	fp = fopen(f, "r");
	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila!\n", f);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp)) 
	{
		fgets(buffer, MAX_LINE, fp);
		if(strcmp("\n", buffer) != 0)
			count++;
	}

	fclose(fp);

	return count;

}

int IspisiStudente(int broj, student* s)
{
	int i = 0;
	for (i = 0;i < broj;i++)
		printf("Student: %s %s\n Apsolutni broj bodova: %d\n Relativni broj bodova: %f\n", (s + i)->ime, (s + i)->prezime, (s + i)->bodovi, ((double)(s + i)->bodovi / 50 * 100));
	return EXIT_SUCCESS;
}
