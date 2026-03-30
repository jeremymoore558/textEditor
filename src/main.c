#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

#include "document_buffer.h"
#include "input_handler.h"

struct termios orig_termios;

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(){
	atexit(disableRawMode);
	
	tcgetattr(STDIN_FILENO, &orig_termios);
	struct termios raw;
	raw = orig_termios;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= ~(CS8); 
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1; 

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void print_inputs(char c){
		if (iscntrl(c)){
			printf("%d\r\n", c);
		}
		else{
			printf("%d ('%c')\r\n", c, c);
		}
}

void clear_screen(){
	printf("\033c");
}

int main(){
	enableRawMode();

	// Read file
	char filename[100] = "test.txt";
	printf("%s\r\n", filename);

	DocBuffer *doc_buf;
	doc_buf = (DocBuffer*)malloc(sizeof(DocBuffer));
	doc_buf->exit_status = 0;
	read_text_file(filename, doc_buf);
	print_buffer(doc_buf);

	// Initialize DocunemtBuffer Struct

	char c;
	while (1) {
		c = '\0';
		read(STDIN_FILENO, &c, 1); 
		handle_inputs(c, doc_buf);
		clear_screen();
		//print_inputs(c);
		print_buffer(doc_buf);
		if (doc_buf->exit_status == 1) break;	
	};
	return 0;
}
