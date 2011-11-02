#include "node.h"
#include "leaf.h"
#include "inner_node.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/uio.h>

//virtual class constructor, only called by sub classes
struct node * node_ctor(struct inner_node * parent) {
	struct node * this = malloc(sizeof(*this));
	this->parent = parent;
	
	return this;
}

void _node_dtor(struct node * this) {
	free(this);
}

void node_dtor(struct node * this) {
	this->vtable->node_dtor(this);
}

void node_ask_question(struct node * this) {
	this->vtable->ask_question(this);
}

struct node * node_process_answer(struct node * this, char answer, struct node ** root) {
	return this->vtable->process_answer(this, answer, root);
}

struct iovec node_serialize(struct node * this) {
	return this->vtable->serialize(this);
}

static struct node * recursive_read(FILE * file) {
	uint8_t type;
	if(!fread(&type, sizeof(type), 1, file)) {
		goto error;
	}
	switch(type) {
	case 0:
		{
			uint32_t len;
			if(!fread(&len, sizeof(len), 1, file)) {
				goto error;
			}
			len = ntohl(len);
			char * question = malloc(len + 1);
			if(!question) {
				puts("malloc failed");
				exit(1);
			}
			if(!fread(question, len, 1, file)) {
				goto error;
			}
			question[len] = '\0';
			struct node * yes = recursive_read(file);
			struct node * no = recursive_read(file);
			
			struct inner_node * result = inner_node_ctor(question, yes, no);
			return &result->node;
		}
	case 1:
		{
			uint32_t len;
			if(!fread(&len, sizeof(len), 1, file)) {
				goto error;
			}
			len = ntohl(len);
			char * name = malloc(len + 1);
			if(!name) {
				puts("malloc failed");
				exit(1);
			}
			if(!fread(name, len, 1, file)) {
				goto error;
			}
			name[len] = '\0';
			
			struct leaf * result = leaf_ctor(name);
			return &result->node;
		}
	default:
		break;
	}
	error:
	puts("broken input file");
	exit(1);
	return NULL;
}

struct node * node_factory(FILE * file) {
	uint8_t header[] = { 'A', 'G', 'G', '0', 1, 2, 3, 4 };
	uint8_t input[8];
	if(!fread(&input, sizeof(input), 1, file)) {
		return NULL;
	}
	if(memcmp(header, input, sizeof(input))) {
		puts("broken input file");
		exit(1);
	}
	return recursive_read(file);
}

