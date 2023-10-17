/*
Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i ucitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int NoOfStud();
int registration(int noRows, Student* studenti);
int print(int NoStud, Student* studenti);
int main() {
	int NoStud = 0; //broj studenata
	Student* studenti;

	NoStud = NoOfStud();

	studenti = (Student*)malloc(NoStud * sizeof(Student));

	if (registration(NoStud, studenti)) //nije potpuno
		return 0;
	
	if (print(NoStud, studenti))
		return 0;


	return EXIT_SUCCESS;
}

//ucitava broj studenata iz datoteke
int NoOfStud() {
	FILE* filePointer = NULL;
	Student temp;
	int counter = 0;
	filePointer = fopen("Student.txt", "r");
	//Ako se datoteka ne otvorit, program zavrsava
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	while (fscanf(filePointer, "%s %s %lf", temp.name, temp.surname, &temp.points) == 3) {
		counter++;
	}

	fclose(filePointer);
	return counter;
}

//funkcija sprema podatke it datoteke u nizstruktura
int registration(int NoStud, Student* studenti) {
	FILE* filePointer = NULL;
	int i = 0;

	filePointer = fopen("Student.txt", "r");
	//Ako se datoteka ne otvorit, program zavrsava
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	for (i = 0; i < NoStud; i++) {
		fscanf(filePointer, "%s %s %lf", studenti[i].name, studenti[i].surname, &studenti[i].points);
	}

	fclose(filePointer);
	return 0;
}

//ispisuje studente 
int print(int NoStud, Student* studenti) {
	int i = 0;
	double MaxPoints = 0;
	
	//pronalazi max bodove
	for (i = 0; i < NoStud; i++) {
		if (studenti[i].points > MaxPoints)
			MaxPoints = studenti[i].points;
	}
	
	for (i = 0; i < NoStud; i++) {
		printf("%s %s %lf %lf\n", studenti[i].name, studenti[i].surname, studenti[i].points, studenti[i].points/MaxPoints*100);
		
	}

	return 0;
}