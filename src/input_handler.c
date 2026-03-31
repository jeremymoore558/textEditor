#include <termios.h>
#include <unistd.h>
#include "document_buffer.h"
#include "insert_mode.h"
#include "command_mode.h"

void move_cursor_down(DocBuffer* doc_buf){
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
}

void move_cursor_up(DocBuffer* doc_buf){
	int new_line_counter;
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

}

void move_cursor_left(DocBuffer* doc_buf){
	if (doc_buf->cursor.left >= 0){
		doc_buf->buffer[doc_buf->cursor.right] = 
			doc_buf->buffer[doc_buf->cursor.left];
		doc_buf->buffer[doc_buf->cursor.left] = '\0';
		doc_buf->cursor.left -= 1;
		doc_buf->cursor.right -= 1;
	}
}

void move_cursor_right(DocBuffer* doc_buf){
	if (doc_buf->cursor.right < GAP_BUFFER_SIZE-1){
		doc_buf->cursor.left += 1;
		doc_buf->cursor.right += 1;
		doc_buf->buffer[doc_buf->cursor.left] = 
			doc_buf->buffer[doc_buf->cursor.right];
		doc_buf->buffer[doc_buf->cursor.right] = '\0';
	}
}



void cursor_motion(char c, DocBuffer* doc_buf){
	switch (c){
		case 'h':
			move_cursor_left(doc_buf);
			break;
		case 'l':
			move_cursor_right(doc_buf);
			break;
		case 'j':
			move_cursor_down(doc_buf);
			break;
		case 'k':
			move_cursor_up(doc_buf);
			break;
	}		
}

void handle_inputs(char c, DocBuffer* doc_buf){
	switch (c){
		case 'i':
			insert_mode(doc_buf);
			return;
		case 'o':
			move_cursor_down(doc_buf);
			move_cursor_left(doc_buf);
			write_char_to_buffer('\n', doc_buf);
			insert_mode(doc_buf);
			return;
		case ':':
			command_mode(doc_buf);
			break;
		default:
			cursor_motion(c, doc_buf);
	}
}

