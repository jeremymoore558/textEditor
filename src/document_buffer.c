#include <stdio.h>
#include <string.h>
#include "document_buffer.h"

// Initialize DocBuffer struct by reading in from file.
void read_text_file(char* filename, DocBuffer* doc_buf){
	FILE *fptr;
	fptr = fopen(filename, "r");

	int c;
	while ((c = getc(fptr)) != EOF){
		doc_buf->buffer[doc_buf->cursor.left] = c;
		doc_buf->cursor.left += 1;
	}
	doc_buf->cursor.right = GAP_BUFFER_SIZE-1;

	strcpy(doc_buf->filename, filename);
}

void print_buffer(DocBuffer* doc_buf){
	for (int i=0; i<GAP_BUFFER_SIZE; i++){
		switch (doc_buf->buffer[i]){
			case '\0':
				break;
			case '\n':
				printf("\r");
			default:
				printf("%c", doc_buf->buffer[i]);
		}

		if (i == doc_buf->cursor.left){
			printf("|");
		}
	}
	printf("\r\n");
}
