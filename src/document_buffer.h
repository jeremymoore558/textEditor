#ifndef DOCUMENT_BUFFER_H
#define DOCUMENT_BUFFER_H

#define GAP_BUFFER_SIZE 2000

typedef struct{
	/* The cursor tracks the position of the gap buffer.
	 * Left is where new text will be inserted, and right is where 
	 * characters will be inserted as the left cursor moves.
	 */
	int left;
	int right;
}Cursor;

typedef struct{
	char buffer[GAP_BUFFER_SIZE];
	char filename[100];
	Cursor cursor;
}DocBuffer;

void read_text_file(char* filename, DocBuffer* doc_buf);

void print_buffer(DocBuffer* doc_buf);

#endif

