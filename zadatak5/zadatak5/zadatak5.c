/*
 5. Napisati program koji iz datoteke cita postfiks izraz i zatim koristenjem stoga racuna
rezultat. Stog je potrebno realizirati preko vezane liste
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 1024

struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement {
	int number;
	Position next;
} StackElement;

Position CreateNewElement(int number);
int ReadFromFile(char* buffer);
int push(Position head, int number);
int pop(Position head);
int print(Position head);
int Pop_DoOperation_push(Position head, char operation);
int StringToStack(Position head, char* buffer);

int main() {
	char buffer[MAX_LENGHT] = { 0 };

	StackElement head = { .number = 0, .next = NULL };

	ReadFromFile(buffer);

	StringToStack(&head, buffer);

	print(&head);

	return 0;
}

Position CreateNewElement(int number) {
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(StackElement));

	if (!newElement) {
		printf("Error in creating new element");
		return NULL;
	}

	newElement->number = number;

	return newElement;
}

int ReadFromFile(char* buffer) {

	FILE* filepointer;
	filepointer = fopen("postfix.txt", "r");

	if (!filepointer) {
		printf("Error in open file!");
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LENGHT, filepointer);
	printf("|%s|\n", buffer);

	fclose(filepointer);
	return EXIT_SUCCESS;
}

int push(Position head, int number) {
	Position newElement = NULL;

	newElement = CreateNewElement(number);

	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}

int pop(Position head) {
	int number;
	Position first;

	first = head->next;

	head->next = head->next->next;

	number = first->number;

	free(first);

	return number;
}

int print(Position head) {
	Position Current = head->next;

	while (Current) {
		printf("%d\n", Current->number);
		Current = Current->next;
	}
	return EXIT_SUCCESS;
}

int Pop_DoOperation_push(Position head, char operation) {
	int number1 = 0, number2 = 0, result = 0;

	number2 = pop(head);
	number1 = pop(head);


	switch (operation)
	{
	case '+':
		result = number1 + number2;
		break;
	case '-':
		result = number1 - number2;
		break;
	case '*':
		result = number1 * number2;
		break;
	case '/':
		result = number1 / number2;
		break;
	default:
		return EXIT_FAILURE;
		break;
	}
	push(head, result);
	return EXIT_SUCCESS;
}

int StringToStack(Position head, char* buffer) {
	char* CurrentBuffer = buffer;
	Position NewElement = NULL;
	int NumberBytes = 0, status = 0, CurrentNumber = 0;
	char operation = 0;

	while (strlen(CurrentBuffer)>0){
		NumberBytes = 0;
		status = sscanf(CurrentBuffer, " %d %n", &CurrentNumber, &NumberBytes);
		if (status==1) {
			push(head, CurrentNumber);
		}
		if (status != 1) {
			sscanf(CurrentBuffer, "%c %n", &operation, &NumberBytes);
			Pop_DoOperation_push(head, operation);
		}
		CurrentBuffer += NumberBytes;
	}
	return EXIT_SUCCESS;
}

