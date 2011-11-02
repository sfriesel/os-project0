#include "node.h"

#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>

//virtual class constructor, only called by sub classes
struct node * node_ctor(void) {
	struct node * this = malloc(sizeof(*this));
	
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

struct node * node_process_answer(struct node * this, char answer, struct node * parent, struct node * root) {
	return this->vtable->process_answer(this, answer, parent, root);
}

struct iovec node_serialize(struct node * this) {
	return this->vtable->serialize(this);
}

