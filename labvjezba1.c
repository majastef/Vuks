#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_FILE_NAME (256)

typedef struct {
	char ime[15];
	char prezime[15];
	int bodovi;
}student;

int brojStudenata(char* );
void UcitajStudente(char* , int , student*);
void IspisiStudente(int , student*);

int main()
{
	int br_stud;
	student* stud = NULL;
	char f[MAX_FILE_NAME] = { 0 };

	//printf("Unesi ime datoteke: ");
	//scanf(" %s", f);

	//printf("Broj studenata u datoteci %s je %d", f, brojStudenata((char *)"student.txt"));

	br_stud = brojStudenata((char *)"c:\\tmp\\student.txt");
	stud = (student*)malloc(br_stud * (sizeof(student)));
	if (stud == NULL)
	{
		printf("Greška pri alociranju memorije!");
	}

	UcitajStudente((char *)"c:\\tmp\\student.txt", br_stud, stud);
	IspisiStudente(br_stud, stud);
	free(stud);

	return 0;
}

void UcitajStudente(char* file, int broj, student* s)
{
	int i;
	FILE* f = NULL;
	f = fopen(file, "r");
	if (f == NULL)
	{
		printf("Greška pri otvaranju datoteke!");
		return;
	}

	for (i = 0;i < broj;i++)
	{
		fscanf(f, "%s %s %d", (s + i)->ime, (s + i)->prezime, &(s + i)->bodovi);
	}

	fclose(f);
	return;

}

int brojStudenata(char* f) {
	FILE* fp = NULL;
	int count = 0;

	fp = fopen(f, "r");
	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila!\n", f);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp)) {
		if (fgetc(fp) == '\n')
			count++;
	}

	rewind(fp);
	fclose(fp);

	return (count -1);

}

void IspisiStudente(int broj, student* s)
{
	int i;
	for (i = 0;i < broj;i++)
		printf("Student: %s %s\n Apsolutni broj bodova: %d\n Relativni broj bodova: %f\n", (s + i)->ime, (s + i)->prezime, (s + i)->bodovi, ((double)(s + i)->bodovi / 50 * 100));
	return;
}
