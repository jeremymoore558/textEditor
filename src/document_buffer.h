#ifndef DOCUMENT_BUFFER_H
#define DOCUMENT_BUFFER_H

#define GAP_BUFFER_SIZE 2000

// The main data structure for the text editor is a gap buffer, 
// which is just a char array filled with mostly null-chars. 
// The DocBuffer type contains the gap buffer, the filename, 
// an exit status that determines when the program will close,
// and importantly, a Cursor.
//
// The Cursor type is just a struct
// with two integers marking the leading edge of the text in 
// the gap buffer, and the lagging edge on the right hand side 
// of the gap. This allows very fast movement of characters between the left and right 
// hand sides. Characters move during vim-style motions, 
// but as new text is added, it simply fills in the gap, meaning that while moving,
// the gap buffer is being updated, but while typing, it is as fast as writing to an array. 
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
	int exit_status;
}DocBuffer;

void read_text_file(char* filename, DocBuffer* doc_buf);

void print_buffer(DocBuffer* doc_buf);

#endif

