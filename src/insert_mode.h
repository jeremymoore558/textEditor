#ifndef INSERT_MODE_H
#define INSERT_MODE_H
#include "document_buffer.h"

// Function to add one character to the document buffer. 
// Adjusts position of cursor automatically to track addition of 
// new characters.
// Use judiciously. Currently only used in one place outside of insert mode:
// 		In the input hadler to effect newlines. Consider moving this functionality 
// 		to insert mode. 
void write_char_to_buffer(char c, DocBuffer* doc_buf);

// Entry into insert mode. Primary entry point into
// this module.
void insert_mode(DocBuffer* doc_buf);

#endif
