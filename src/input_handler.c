#include <stdio.h>
#include "document_buffer.h"

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
	}		
}

void insert_mode(DocBuffer* doc_buf){
	//TODO Finish
	printf("Insert Mode");
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

