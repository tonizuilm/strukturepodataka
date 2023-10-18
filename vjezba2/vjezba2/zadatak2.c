/*
2.
Definirati strukturu osoba(ime, prezime, godina rodenja) i napisati program koji :
A.dinamicki dodaje novi element na pocetak liste,
B.ispisuje listu,
C.dinamicki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.brise određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
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

int AddToList(Position head);
int print(Position head);
int AddToListEnd(Position head);
int find();
int delete();

int main() {
	int NoPerson = 0, i=0;
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .year = 0 };

	printf("unesi broj osoba: \n");
	scanf("%d", &NoPerson);

	for(i=0; i<NoPerson; i++)
		AddToListEnd(&Head);

	print(&Head);

	return 0;
}

//stvara novu osobu
Position CreatePerson() {
	
	Position NewPerson = NULL;

	NewPerson = (Position)malloc(sizeof(Person));
	if (!NewPerson)
	{
		printf("error! \n");
		return NULL;
	}

	printf("unesi ime: \n");
	scanf("%s", NewPerson->name);
	printf("unesi prezime: \n");
	scanf("%s", NewPerson->surname);
	printf("unesi godinu rodenja: \n");
	scanf("%d", &NewPerson->year);

	return NewPerson;
}

//dodaje novu osobu na početak liste
int AddToList(Position head) {

	Position NewPerson = NULL;
	NewPerson = CreatePerson();


	NewPerson->next = head->next;
	head->next = NewPerson;

	return EXIT_SUCCESS;
}

//ispisuje listu
int print(Position head) {

	head = head->next;

	for( ; head != NULL; head = head->next)
		printf("%s %s %d\n", head->name, head->surname, head->year);

	return EXIT_SUCCESS;
}

//dodaje na kraj liste
int AddToListEnd(Position head) {
	
	Position NewPerson = NULL;
	NewPerson = CreatePerson();

	while (head->next != NULL)
		head = head->next;

	head->next = NewPerson;
	NewPerson->next = NULL;

}