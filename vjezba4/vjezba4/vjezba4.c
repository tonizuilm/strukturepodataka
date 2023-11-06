/*
4. Napisati program za zbrajanje i mnozenje polinoma. Koeficijenti i eksponenti se
citaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nuzno sortirani.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coefficient;
	int exponent;
	Position next;
} Element;

Position NewElement(int coefficient, int exponent);
int  ReadFromFile(Position head1, Position head2);
int InsertSorted(Position head, int cofficient, int exponent);
int DeleteAfter(Position previous);
int DeleteList(Position head);
int sum(Position sum, Position head1, Position head2);
int multiply(Position Multiply, Position head1, Position head2);

int main() {

	Element head1 = { .next = NULL, .coefficient = 0, .exponent = 0 };
	Element head2 = { .next = NULL, .coefficient = 0, .exponent = 0 };
	Element Sum = { .next = NULL, .coefficient = 0, .exponent = 0 };
	Element Multiply = { .next = NULL, .coefficient = 0, .exponent = 0 };


	ReadFromFile(&head1, &head2);

	print(&head1);
	print(&head2);

	sum(&Sum, &head1, &head2);
	print(&Sum);

	multiply(&Multiply, &head1, &head2);
	print(&Multiply);

	return 0;
}

Position NewElement(int coefficient, int exponent) {
	Position NewElement = NULL;

	NewElement = (Position)malloc(sizeof(Element));
	if (!NewElement) {
		printf("Error! Failed to allocate memory");
		return NULL;
	}

	NewElement->coefficient = coefficient;
	NewElement->exponent = exponent;
	NewElement->next = NULL;

	return NewElement;
}


int print(Position head) {

	if (!head->next) {
		printf("Empty list!\n");
		return EXIT_FAILURE;
	}

	head = head->next;

	for (; head != NULL; head = head->next)
		printf("%dx^%d ", head->coefficient, head->exponent);

	printf("\n");
	return EXIT_SUCCESS;
}
//read from file njegov naccin
/*
int  ReadFromFile(Position head1, Position head2) {
	int coefficient = 0, exponent = 0;
	char buffer[MAX_LINE] = { 0 };
	char* currentbuffer = buffer;
	int numBytes = 0;
	int status = 0;


	Position newelement = NULL;

	FILE* filepointer = NULL;
	filepointer = fopen("polynoms.txt", "r");

	if (!filepointer) {
		printf("Error!");
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, filepointer);

	while (sscanf(currentbuffer, " %dx^%d %n", &coefficient, &exponent, &numBytes) && strlen(currentbuffer) > 0) {

		newelement = NewElement(coefficient, exponent);
		if (!newelement) {
			return EXIT_FAILURE;
		}

		newelement->next = head2->next;
		head2->next = newelement;
		currentbuffer +=numBytes;
	}

	fclose(filepointer);
	return EXIT_SUCCESS;
}
*/


//read from file moj nacin
int ReadFromFile(Position head1, Position head2) {
	int coefficient = 0, exponent = 0;
	char temp = 0;

	FILE* filepointer;
	filepointer = fopen("polynoms.txt", "r");
	if (!filepointer) {
		printf("Error! can not open file!");
		return FILE_ERROR_OPEN;
	}

	//cita i stvara listu od prog retka
	while (fscanf(filepointer, "%dx^%d%c", &coefficient, &exponent, &temp) == 3){
		
		InsertSorted(head1, coefficient, exponent);

		if (temp == '\n') {
			break;
		}
	}
	
	//cita i stvara listu d drugog retka
	while (fscanf(filepointer, "%dx^%d%c", &coefficient, &exponent, &temp) == 3) {
	
		InsertSorted(head2, coefficient, exponent);

		if (temp == '\n') {
			break;
		}
	}

	fclose(filepointer);
	return EXIT_SUCCESS;
}

//sortira novi element u listu 
int InsertSorted(Position head, int coefficient, int exponent) {
	Position previous = head;
	Position newelement = NULL;

	newelement = NewElement(coefficient, exponent);
	if (!newelement) {
		printf("Error! Fail to create new element!");
		return EXIT_FAILURE;
	}

	if (!head->next) {
		newelement->next = head->next;
		head->next=newelement;
		return EXIT_SUCCESS;
	}

	
	while (previous->next !=NULL && newelement->exponent < previous->next->exponent) {
		previous = previous->next;
	}

	if (previous->next == NULL || newelement->exponent != previous->next->exponent) {
		newelement->next = previous->next;
		previous->next = newelement;
		return EXIT_SUCCESS;
		
	}
	else if(newelement->exponent == previous->next->exponent){
		previous->next->coefficient = previous->next->coefficient + newelement->coefficient;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int DeleteAfter(Position previous) {
	Position toDelete = previous->next;

	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int DeleteList(Position head) {
	
	while (head->next)
		DeleteAfter(head);

	return EXIT_SUCCESS;
}

//zbraja dva polinoma
int sum(Position Sum, Position head1, Position head2) {

	if (!head1->next || !head1->next) {
		printf("Empty list!\n");
		return EXIT_FAILURE;
	}

	while (head1->next) {
		InsertSorted(Sum, head1->next->coefficient, head1->next->exponent);
		head1 = head1->next;
	}
	while (head2->next) {
		InsertSorted(Sum, head2->next->coefficient, head2->next->exponent);
		head2 = head2->next;
	}
	return EXIT_SUCCESS;
}

//mnozi dva polinoma
int multiply(Position Multiply, Position head1, Position head2) {
	Position current1, current2;

	if (!head1->next || !head1->next) {
		printf("Empty list!\n");
		return EXIT_FAILURE;
	}
	current1 = head1;
	current2 = head2;

	while (current1->next) {
		current1 = current1->next;

		while (current2->next) {
			current2 = current2->next;

			InsertSorted(Multiply, current1->coefficient * current2->coefficient, current1->exponent + current2->exponent);
			
		}
		current2 = head2;
	}
	return EXIT_SUCCESS;
}