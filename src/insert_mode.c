#include <termios.h>
#include <unistd.h>
#include "main.h"
#include "document_buffer.h"

void write_char_to_buffer(char c, DocBuffer* doc_buf){
	if (c == '\0'){return;}

	doc_buf->cursor.left += 1;
	doc_buf->buffer[doc_buf->cursor.left] = c;
}

void delete_char_from_buffer(DocBuffer* doc_buf){
	doc_buf->buffer[doc_buf->cursor.left] = '\0';
	doc_buf->cursor.left -= 1;
}

void insert_mode(DocBuffer* doc_buf){
	//TODO Finish
	char c;
	while (1){
		c = '\0';
		read(STDIN_FILENO, &c, 1);
		if (c == 27){break;}

		switch (c){
			case '\0':
				break;
			case 13:
				write_char_to_buffer('\n', doc_buf);
				break;	
			case 127:
				delete_char_from_buffer(doc_buf);
				break;
			default:
				write_char_to_buffer(c, doc_buf);
				break;
		}

		clear_screen();
		print_buffer(doc_buf);
	}
}
