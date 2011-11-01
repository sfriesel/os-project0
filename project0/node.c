#include "node.h"

#include <stdlib.h>
#include <string.h>


static const struct node_vtable leaf_funcs = { /*TODO*/ NULL, NULL, NULL, NULL };

static const struct node_vtable inner_node_funcs = { /*TODO*/ NULL, NULL, NULL, NULL };

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

struct leaf * leaf_ctor(char * name) {
	struct node * super = node_ctor();
	super->vtable = &leaf_funcs;
	
	struct leaf * this = realloc(super, sizeof(*this));
	this->name = malloc(strlen(name) + 1);
	strcpy(this->name, name);
	
	return this;
}

void node_ask_question(struct node * this) {
	this->vtable->ask_question(this);
}

struct iovec node_serialize(struct node * this) {
	return this->vtable->serialize(this);
}

void leaf_ask_question(struct node * super) {
	struct leaf * this = (struct leaf*)super;
	printf("Is it a %s?\n", this->name);
}

void inner_node_ask_question(struct node * super) {
	struct inner_node * this = (struct inner_node*)super;
	printf("%s\n", this->question);
}

struct inner_node * inner_node_ctor(char * question) {
	struct node * super = node_ctor();
	super->vtable = &inner_node_funcs;
	
	struct inner_node * this = realloc(super, sizeof(*this));
	this->question = malloc(strlen(question) + 1);
	strcpy(this->question, question);
	
	return this;
}

void leaf_dtor(struct leaf * this) {
	free(this->name);
	node_dtor(&this->node);
}

void inner_node_dtor(struct inner_node * this) {
	free(this->question);
	node_dtor(&this->node);
}
