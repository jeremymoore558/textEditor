#include <stdio.h>
#include "main.h"
#include "document_buffer.h"

void command_mode(DocBuffer* doc_buf){
	char input[100];
	disableRawMode();
	printf(":");
	scanf("%s", input);
	enableRawMode();

	if (input[0] == 'w'){
		write_buffer_to_txt(doc_buf);
	}

	if (input[0] == 'q' || input[1] == 'q'){
		doc_buf->exit_status = 1;
	}
}
