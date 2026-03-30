#ifndef INSERT_MODE_H
#define INSERT_MODE_H
#include "document_buffer.h"

void write_char_to_buffer(char c, DocBuffer* doc_buf);

void insert_mode(DocBuffer* doc_buf);

#endif
