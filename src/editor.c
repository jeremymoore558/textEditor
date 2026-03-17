#include <stdio.h>
#include "main.h"
#include "editor.h"

void printBuffer(char* buffer, Cursor* cursor){
	for (int i=0; i<DOC_BUFFER; i++){
		if (buffer[i] != '\0'){
			printf("%c", buffer[i]);
		}
		if (i == cursor->left){
			printf("|");
		}
	}
	printf("\n");
}

void moveCursor(char* buffer, char* input, Cursor* cursor){
	int newlineCounter;
	// TODO:: Implement moving between lines with j and k
	switch (input[0]){
		case 'h':
			buffer[cursor->right] = buffer[cursor->left];
			buffer[cursor->left] = '\0';
			cursor->left -= 1;
			cursor->right -= 1;
			break;
		case 'l':
			cursor->left += 1;
			cursor->right += 1;
			buffer[cursor->left] = buffer[cursor->right];
			buffer[cursor->right] = '\0';
			break;
		case 'j':
			// Same initial operation as 'l'
			cursor->left += 1;
			cursor->right += 1;
			buffer[cursor->left] = buffer[cursor->right];
			buffer[cursor->right] = '\0';
			while (buffer[cursor->left] != '\n' && cursor->right < DOC_BUFFER){
				cursor->left += 1;
				cursor->right += 1;
				buffer[cursor->left] = buffer[cursor->right];
				buffer[cursor->right] = '\0';
			}
			break;
		case 'k':
			// Go back until the second newline you encounter, or BOF
			newlineCounter = 0;
			while (newlineCounter < 2 && cursor->left >= 0){
				if (buffer[cursor->left] == '\n') {newlineCounter += 1;}
				if (newlineCounter < 2){
					buffer[cursor->right] = buffer[cursor->left];
					buffer[cursor->left] = '\0';
					cursor->left -= 1;
					cursor->right -= 1;
				}
			}
			break;

	}
}

void addLinebreak(char* buffer, Cursor* cursor){
	cursor->left += 1;
	buffer[cursor->left] = '\n';
} 

void writeBuffer(char* buffer, char* input, Cursor* cursor){
	int i = 0;
	cursor->left += 1;
	while (input[i] != '\0'){
		buffer[cursor->left] = input[i];
		i += 1;
		cursor->left += 1;
	}cursor->left -= 1;
}

void writeToFile(char* buffer, Cursor* cursor){
	FILE *fptr;
	fptr = fopen(cursor->filename, "w");
	for (int i = 0; i<DOC_BUFFER; i++){
		if (buffer[i] != '\0'){
			putc((int)buffer[i], fptr);
		}
	}
	fclose(fptr);
}

void commandMode(char* buffer, Cursor* cursor, char command){
	if (command == ' ' || command == '\0'){
		return; 
	}
	if (command == 'w'){
		writeToFile(buffer, cursor);
	}
}
