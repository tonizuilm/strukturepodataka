/*
2.
Definirati strukturu osoba(ime, prezime, godina rodenja) i napisati program koji :
A.dinamicki dodaje novi element na pocetak liste,
B.ispisuje listu,
C.dinamicki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.brise određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.

3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int year;
	Position next;
} Person;

int menu(Position head);
int AddToList(Position head);
int print(Position head);
int AddToListEnd(Position head);
int delete(Position head);
int addpersonbeafore(Position head);
int addpersonafter(Position head);
int printtofile(Position head);
int readfromfile(Position head);
int sortedenter(Position head);
int personcounter();
Position findperson(Position head);
Position findpersonbeafore(Position head);

int main() {
	int menureturn = 0;
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .year = 0 };

	do {
		menureturn = menu(&head);
	} while (!menureturn);
	
	return 0;
}

int menu(Position head) {
	char selection = NULL;
	Position temp = NULL;
	int a = 0;
	printf("\n\nMENU\nenter what you want to do\n\na - Add new person to the begining\ne - Add new person to the end of the list\np - Print list\nf - Find person\nd - Delete person\nb - Add person beafore\nn - Add person after\ni - Print to file\nr - Read from file\ns - Sort enter\nx - Exit \n\n");
	scanf("%c", &selection);
	
	switch (selection)
	{
	case 'a':
		AddToList(&head);
		break;
	case 'e':
		AddToListEnd(&head);
		break;
	case 'p':
		print(&head);
		break;
	case 'f':
		temp = findperson(&head);
		printf("%s %s %d", temp->name, temp->surname, temp->year);
		break;
	case 'd':
		delete(&head);
		break;
	case 'b':
		addpersonbeafore(&head);
		break;
	case 'n':
		addpersonafter(&head);
		break;
	case 'i':
		printtofile(&head);
		break;
	case 'r':
		readfromfile(&head);
		break;
	case 's':
		sortedenter(&head);
		break;
	case 'x':
		return 1;
		break;
	default:
		printf("Incorrecr enter!\n");
		break;
	}
	return 0;
}

//stvara novu osobu//
Position CreatePerson() {
	
	Position NewPerson = NULL;

	NewPerson = (Position)malloc(sizeof(Person));
	if (!NewPerson)
	{
		printf("Error! \n");
		return NULL;
	}

	printf("Enter name: \n");
	scanf("%s", NewPerson->name);
	printf("Enter surname: \n");
	scanf("%s", NewPerson->surname);
	printf("Enter birth year: \n");
	scanf("%d", &NewPerson->year);

	return NewPerson;
}

//dodaje novu osobu na početak liste//
int AddToList(Position head) {

	Position NewPerson = NULL;
	NewPerson = CreatePerson();


	NewPerson->next = head->next;
	head->next = NewPerson;

	return EXIT_SUCCESS;
}

//ispisuje listu//
int print(Position head) {

	if (head->next) {
		head = head->next;

		for (; head != NULL; head = head->next)
			printf("%s %s %d\n", head->name, head->surname, head->year);

		return EXIT_SUCCESS;
	}
	else {
		printf("Empty list!\n");
		return NULL;
	}
}

//dodaje na kraj liste//
int AddToListEnd(Position head) {

	Position NewPerson = NULL;
	NewPerson = CreatePerson();

	while (head->next != NULL)
		head = head->next;

	head->next = NewPerson;
	NewPerson->next = NULL;
	return 0;
}

//briše traženu osobu iz liste//
int delete(Position head) {
	Position TargetPerson = NULL, PreviousPerson = NULL;

	PreviousPerson = findpersonbeafore(&head);

	TargetPerson = PreviousPerson->next;
	PreviousPerson->next = PreviousPerson->next->next;
	free(TargetPerson);

	return EXIT_SUCCESS;
}
//dodaje novu osobu prije tražene osobe//
int addpersonbeafore(Position head) {

	Position NewPerson = NULL, PersonBeafore = NULL, Person = NULL;

	PersonBeafore = findpersonbeafore(&head);

	if (!PersonBeafore) {

		NewPerson = CreatePerson();

		Person = PersonBeafore->next;
		PersonBeafore->next = NewPerson;
		NewPerson->next = Person;
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}
//dodaje osobu nakon trazene osobe//
int addpersonafter(Position head) {

	Position NewPerson = NULL, TargetPerson = NULL, NextPerson = NULL;

	NewPerson = CreatePerson();
	TargetPerson = findperson(&head);
	
	NextPerson = TargetPerson->next;
	TargetPerson->next = NewPerson;
	NewPerson->next = NextPerson;
	
	return EXIT_SUCCESS;
}

//ispisuje osobe u datoteku//
int printtofile(Position head) {
	FILE* filePointer = NULL;
	filePointer = fopen("Persons.txt", "w");

	//Ako se datoteka ne otvorit, program zavrsava
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	while (head->next!=NULL){
		fprintf(filePointer, "%s %s %d\n", head->next->name, head->next->surname, head->next->year);
		head = head->next;
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}

//ucitava osobe iz datoteke//
int readfromfile(Position head) {
	head->next = NULL;
	Position temp = head;
	int numberofperson = 0, counter = 0;

	FILE* filepointer = NULL;
	filepointer = fopen("Persons.txt", "r");

	if (!filepointer) {
		printf("Error in opening file!\n");
		return FILE_ERROR_OPEN;
	}

	numberofperson = personcounter();
	for (counter = 0; counter < numberofperson; counter++) {

		Position NewPerson = NULL;
		NewPerson = (Position)malloc(sizeof(Person));

		if (!NewPerson)
		{
			printf("Error! Newperson \n");
			return NULL;
		}

		fscanf(filepointer, "%s %s %d", NewPerson->name, NewPerson->surname, &NewPerson->year);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		NewPerson->next = temp->next;
		temp->next = NewPerson;
		temp = head;
	}

	fclose(filepointer);
	return EXIT_SUCCESS;
}

//sortirani unos
int sortedenter(Position head) {
	Position NewPerson = NULL, next;
	NewPerson = (Position)malloc(sizeof(Person));
	NewPerson = CreatePerson();
	if (!head->next) {
		head->next = NewPerson;
		NewPerson->next = NULL;
	}
	else {
		// strcmp >0 if the first non-matching character in str1 is greater (in ASCII) than that of str2. < 0	if the first non - matching character in str1 is lower(in ASCII) than that of str2.
		while (strcmp(head->next->name, NewPerson->name) < 0)
			head = head->next;
		next = head->next;
		head->next = NewPerson;
		NewPerson->next = next;
	}

	return EXIT_SUCCESS;
}
//ucitava broj osoba iz datoteke//
int personcounter() {
	int numberofperson = 0;
	FILE* filepointer;
	filepointer = fopen("Persons.txt", "r");
	char aa[30];
	char bb[30];
	int kkk;

	while (fscanf(filepointer, "%s %s %d", aa, bb, &kkk) == 3)
		numberofperson++;

	fclose(filepointer);
	return numberofperson;
}
// trazi osobu i vraca adresu traazene osobe//
Position findperson(Position head) {
	char TargetSurname[MAX_SIZE] = { 0 };
	Position Temp = head->next;

	if (!head->next) {
		printf("Empty list!\n");
		return NULL;
	}
		
	
	printf("Enter surname:\n");
	scanf("%s", TargetSurname);
	
	do {
																																															if (strcmp(Temp->surname, TargetSurname) == 0) {
			return Temp;
		}
		else {
			Temp = Temp->next;
		}
	} while (Temp != NULL);

	return NULL;

}

//trazi osobu i vraca adresu od predhodne osobe
Position findpersonbeafore(Position head) {
	char TargetSurname[MAX_SIZE] = { 0 };
	int flag = 0;
	Position BeaforeTemp = NULL, PersonBeafore = NULL;

	if (head->next) {
		BeaforeTemp = head;
		
		if (flag) {
			printf("Enter surname:\n");
			scanf("%s", TargetSurname);
			flag = 1;
		}
		do {
			if (!strcmp(BeaforeTemp->next->surname, TargetSurname))
				PersonBeafore = BeaforeTemp;
			BeaforeTemp = BeaforeTemp->next;
		} while (BeaforeTemp->next->next != NULL && PersonBeafore == NULL);

		if (PersonBeafore == NULL) {
			printf("Person does not exist!\n");
			return NULL;
		}
		else
			return PersonBeafore;
	}
	else {
		printf("Empty list!\n");
		return NULL;
	}
}