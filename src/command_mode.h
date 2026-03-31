#ifndef COMMAND_MODE_H
#define COMMAND_MODE_H
#include "document_buffer.h"

// List of commands:
// :q -> change the exit_status of doc_buf, causing the program to quit
//
// Planned commands:
// :w
// :wq
void command_mode(DocBuffer* doc_buf);

#endif
