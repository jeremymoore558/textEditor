#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"
#include "main.h"
#include "editor.h"

void emptyInputBuffer(){
	while (getchar() != '\n'){
		
	}
}

static char switchMode(char* input){
	char mode;
	if (input[0] == 'i'){
		mode = 'i';
	}else if (input[0] == 'q'){
		mode = 'q';
	}else if (input[0] == 'o'){
		mode = 'o';
	}else if (strcmp(input, "-h")==0){
		mode = 'h';	
	}else if (input[0] == ':'){
		mode = ':';
	}else{
		mode = 'n';
	}
	return mode;
}

int main(int argc, char** argv){
	// Inputs: expects a file name
	FILE *fptr;
	//fptr = fopen(argv[1], "r");
	fptr = fopen("test.txt", "r");

	// Modes
	/*List of modes:
		n : normal mode
			controls: h move cursor left, 
						j move cursor down line
						k move cursror up line
						l move cursor right
	 * i : insert
	  		scanf a single line of input text. Append at cursor.
		q : Quit mode : if in this mode, program exits
		h : Help mode : displays help page
	*/
	char mode = 'n'; 

	// Initialize String buffer to store input and cursor
	char buffer[DOC_BUFFER] = {0};
	int c;
	Cursor *cursor = (Cursor* )malloc(sizeof(Cursor));
	while((c = getc(fptr)) != EOF){
		buffer[cursor->left] = c;
		cursor->left += 1;
	}
	cursor->right = DOC_BUFFER - 1;
	strcpy(cursor->filename, "test.txt");
	fclose(fptr);

	system("clear");
	printBuffer(buffer, cursor);

	// Main Driver
	char input[INPUT_BUFFER] = {0};
	while (mode != 'q'){
		switch (mode){
			case 'n':
				printf("(Normal): ");
				scanf("%s", input);
				emptyInputBuffer();
				if (input[0]=='h' || input[0]=='l' || input[0]=='j' || input[0]=='k'){
					moveCursor(buffer, input, cursor);
				}else{
					mode = switchMode(input);
				}
				break;
			case 'i':
				printf("(Insert): ");
				scanf("%[^\n]s", input);
				emptyInputBuffer();
				writeBuffer(buffer, input, cursor);
				mode = 'n';
				break;
			case 'o':
				addLinebreak(buffer, cursor);
				mode = 'n';
				break;
			case 'h':
				helpMode();
				mode = 'n';
				break;
			case ':':
				commandMode(buffer, cursor, input[1]);
				mode = 'n';
				break;

		}

		system("clear");
		printBuffer(buffer, cursor);
	}
	return 0;
}
