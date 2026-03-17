#include "help.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void helpMode(void){
	char flag[100];

	while (strcmp(flag, "q") != 0){
		system("clear");
		printf("To exit, type q\n");
		printf("(Help): ");
		scanf("%s", flag);
		emptyInputBuffer();
	}
}
