#include <termios.h>
#include <unistd.h>
#include "document_buffer.h"
#include "main.h"

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

void cursor_motion(char c, DocBuffer* doc_buf){
	int new_line_counter;
	switch (c){
		case 'h':
			if (doc_buf->cursor.left >= 0){
				doc_buf->buffer[doc_buf->cursor.right] = 
					doc_buf->buffer[doc_buf->cursor.left];
				doc_buf->buffer[doc_buf->cursor.left] = '\0';
				doc_buf->cursor.left -= 1;
				doc_buf->cursor.right -= 1;
			}
			break;
		case 'l':
			if (doc_buf->cursor.right < GAP_BUFFER_SIZE-1){
				doc_buf->cursor.left += 1;
				doc_buf->cursor.right += 1;
				doc_buf->buffer[doc_buf->cursor.left] = 
					doc_buf->buffer[doc_buf->cursor.right];
				doc_buf->buffer[doc_buf->cursor.right] = '\0';
			}
			break;
		case 'j':
			doc_buf->cursor.left += 1;
			doc_buf->cursor.right += 1;
			doc_buf->buffer[doc_buf->cursor.left] = 
				doc_buf->buffer[doc_buf->cursor.right];
			doc_buf->buffer[doc_buf->cursor.right] = '\0';
			while (doc_buf->buffer[doc_buf->cursor.left] != '\n' &&
					doc_buf->cursor.right < GAP_BUFFER_SIZE){
				doc_buf->cursor.left += 1;
				doc_buf->cursor.right += 1;
				doc_buf->buffer[doc_buf->cursor.left] = 
					doc_buf->buffer[doc_buf->cursor.right];
				doc_buf->buffer[doc_buf->cursor.right] = '\0';
			}
			break;
		case 'k':
			new_line_counter = 0;
			while (new_line_counter < 2 && doc_buf->cursor.left >= 0){
				if (doc_buf->buffer[doc_buf->cursor.left] == '\n'){new_line_counter += 1;}
				if (new_line_counter < 2){
					doc_buf->buffer[doc_buf->cursor.right] = 
						doc_buf->buffer[doc_buf->cursor.left];
					doc_buf->buffer[doc_buf->cursor.left] = '\0';
					doc_buf->cursor.left -= 1;
					doc_buf->cursor.right -= 1;
				}
			}
			break;
		case 'i':
			insert_mode(doc_buf);
			break;
	}		
}

void handle_inputs(char c, DocBuffer* doc_buf){
	switch (c){
		case 'q':
			return;
		case 'i':
			insert_mode(doc_buf);
			return;
		default:
			cursor_motion(c, doc_buf);
	}
}

