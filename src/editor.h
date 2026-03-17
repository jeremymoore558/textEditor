#ifndef EDITOR_H
#define EDITOR_H

typedef struct{
	/* The cursor tracks the position of the gap buffer.
	 * Left is where new text will be inserted, and right is where 
	 * characters will be inserted as the left cursor moves.
	 */
	int left;
	int right;
	char filename[100];
}Cursor;


/* Prints document buffer to screen, and indicates cursor position
 * with |
 */
void printBuffer(char* buffer, Cursor* cursor);

/* Insert input text at cursor position. 
 * 	Assumes cursor.left points to the character at the left end of the gap buffer.
 * 	Inserts input into the gap buffer
 */
void writeBuffer(char* buffer, char* input, Cursor* cursor);

/*Parses input[0]. 
 *
 * Mappings:
 * 	h : move cursor left
 * 	l : move cursor right
 * 	j : move cursor down a line
 * 	k : move cursor up a line
 *
 * While moving cursor, also moves the position of the gap buffer.
 */
void moveCursor(char* buffer, char* input, Cursor* cursor);

/* Adds newline at current cursor position.
 *	Is run when user inputs 'o' in normal mode. Reverts to normal mode immediately.
 */
void addLinebreak(char* buffer, Cursor* cursor);

/* Receive command from list:
 * 	 : return with no action
 * 	w:write to file
 */
void commandMode(char* buffer, Cursor* cursor, char command);

#endif

