#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/uio.h>

#include "node.h"
#include "leaf.h"

int main(int argc, char * argv[]) {
	char input[1024];
	if(argc != 2) {
		printf("usage: %s <filename>\n(the file can be empty)\n", argv[0]);
		exit(-1);
	}
	
	FILE * f = fopen(argv[1], "r");
	
	if(!f) {
		printf("Could not open file \"%s\".\n", argv[1]);
		exit(1);
	}
	
	struct node * root = factory(f);
	fclose(f);
	
	if(!root) {
		puts("Please enter the name of an animal.");
		fgets(input, sizeof(input), stdin);
		if(ferror(stdin) || feof(stdin)) {
			exit(1);
		}
		struct leaf * leaf = leaf_ctor(strtok(input, "\n"));
		root = &leaf->node;
	}
	
	struct node * current = root;
	
	for(;;) {
		node_ask_question(current);
		fgets(input, sizeof(input), stdin);
		if(ferror(stdin) || feof(stdin)) {
			exit(1);
		}
		if(input[1] != '\n') {
			continue;
		}
		switch(input[0]) {
		case 'a':
			current = root;
			continue;
		case 'q':
			exit(0);
		case 's':
			{
				f = fopen(argv[1], "w");
				if(!f) {
					goto ioerror;
				}
				uint8_t header[] = { 'A', 'G', 'G', '0', 1, 2, 3, 4 };
				if(!fwrite(header, sizeof(header), 1, f)) {
					goto ioerror;
				}
				struct iovec v = node_serialize(root);
				if(!fwrite(v.iov_base, v.iov_len, 1, f)) {
					goto ioerror;
				}
				fclose(f);
			}
			
			break;
		default:
			current = node_process_answer(current, input[0], &root);
		}
	}
	
	return 0;
	ioerror:
	puts("IO Error while writing file");
	return 1;
}
