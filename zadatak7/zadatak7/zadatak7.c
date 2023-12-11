/*
7. Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i
povratak u prethodni direktorij. Tocnije program treba preko menija simulirati
koristenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LENGTH 50


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct _directori;
typedef struct _directory* Position;
typedef struct _directory {
	char name[MAX_NAME_LENGTH];
	Position subDirectories;
	Position next; 
} Directory;

Position CreateNewDirectory(char name[MAX_NAME_LENGTH]);
int CreateDirectory(Position Head);
int CreateSubDirectory(Position currentDirectory);
int PrintDirectoryContents(Position CurrenDirectory);
Position ChangeDirectory(Position CurrentDirectory);
Position GoUpOneDirectory(Position CurrentDirectory, Position RootDirectory);
int Menu(Position CurrentDirectory);

int main() {
	Directory Head = { .name = 0,.next = NULL,.subDirectories = NULL };


	Position RootDirectory = CreateNewDirectory("C:");
	Head.next = RootDirectory;

	Menu(RootDirectory);

	return 0;
}

Position CreateNewDirectory(char name[MAX_NAME_LENGTH]) {
	Position NewDirectory = NULL;

	NewDirectory = (Position)malloc(sizeof(Directory));

	if (!NewDirectory) {
		printf("Error! Failed to create new directory\n");
		return NULL;
	}

	strcpy(NewDirectory->name, name);
	NewDirectory->next = NULL;
	NewDirectory->subDirectories = NULL;

return NewDirectory;
}


int Menu(Position RootDirectory) {
	Position CurrentDirectory = RootDirectory;

	int selection = 0;
	while (1) {
		printf("MENU:\n");
		printf("1 - md (Create Directory)\n");
		printf("2 - cd dir (Change Directory)\n");
		printf("3 - cd.. (Go Up)\n");
		printf("4 - dir (List Contents)\n");
		printf("5 - exit\n");

		scanf(" %d", &selection);

		switch (selection)
		{
		case 1:
			CreateSubDirectory(CurrentDirectory);
			break;
		case 2:
			CurrentDirectory = ChangeDirectory(CurrentDirectory);
			break;
		case 3:
			CurrentDirectory = GoUpOneDirectory(CurrentDirectory, RootDirectory);
			break;
		case 4:
			PrintDirectoryContents(CurrentDirectory);
			break;
		case 5:
			return EXIT_SUCCESS;
			break;
		default:
			printf("wrong entry!");
			break;
		}
	}

	return EXIT_SUCCESS;
}

int CreateDirectory(Position Head) {
	char name[MAX_NAME_LENGTH] = { 0 };
	Position New = NULL;;

	printf("Enter directory name: \n");
	scanf(" %s", name);

	New = CreateNewDirectory(name);

	New->next = Head->next;
	Head->next = New;

	return 0;
}

int CreateSubDirectory(Position currentDirectory) {
	char name[MAX_NAME_LENGTH] = { 0 };
	Position New = NULL;;

	printf("Enter directory name: \n");
	scanf(" %s", name);

	New = CreateNewDirectory(name);

	New->next = currentDirectory->subDirectories;
	currentDirectory->subDirectories = New;

	return 0;
}

Position ChangeDirectory(Position CurrentDirectory) {
	char nameofSubdirectory[MAX_NAME_LENGTH] = { 0 };
	Position New = NULL;;

	printf("Enter subdirectory name: \n");
	scanf(" %s", nameofSubdirectory);

	while (CurrentDirectory->subDirectories && strcmp(CurrentDirectory->subDirectories->name, nameofSubdirectory) != 0)
	{
		CurrentDirectory->subDirectories = CurrentDirectory->subDirectories->next;
	}
	if (CurrentDirectory->subDirectories && strcmp(CurrentDirectory->subDirectories->name, nameofSubdirectory) == 0) {
		return CurrentDirectory->subDirectories;
	}
	else {
		printf("the requested directory does not exist\n");
		return CurrentDirectory;
	}
}

Position GoUpOneDirectory(Position CurrentDirectory, Position RootDirectory) {
	Position Root = RootDirectory;
	while (1) {
		while (Root->subDirectories && strcmp(Root->subDirectories->name, CurrentDirectory->next) != 0) {
			Root->subDirectories = Root->subDirectories->next;
		}
		if (strcmp(Root->subDirectories->name, CurrentDirectory->next) == 0){
			return Root;
		}
		
	}
}

int PrintDirectoryContents(Position CurrentDirectory) {
	Position Current = CurrentDirectory->subDirectories;

	printf("Contents of %s directory:\n", CurrentDirectory->name);

	if (CurrentDirectory->subDirectories == NULL) {
		printf(" - Empty Directory\n");
	}

	while (Current != NULL ) {
		printf(" - %s\n", Current->name);
		Current = Current->next;
	}

	return 0;
}