#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include "document_buffer.h"

// Accepts an input character c and parses the input from 
// normal mode:
// 		hjkl : lead to vim-style motions
// 		o : insert newline, and enter insert mode
// 		: : enter command mode
// Deprecated behaviors:
// 		q : used to quit program. Now, done through :q
void handle_inputs(char c, DocBuffer* doc_buf);

#endif
