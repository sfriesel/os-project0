#include "node.h"
#include "stdlib.h"

struct node_vtable {
	bool (*ask_question)(struct node * this);
	char * (*serialize)(struct node * this);
};

static const struct node_vtable leaf_funcs = { /*TODO*/ NULL, NULL };

static const struct node_vtable inner_node_funcs = { /*TODO*/ NULL, NULL };

//virtual class constructor, only called by sub classes
struct node * node_ctor(void) {
	struct node * this = malloc(sizeof(*this));
	
	return this;
}

struct leaf * leaf_ctor(char * name) {
	struct node * super = node_ctor();
	super->vtable = &leaf_funcs;
	
	struct leaf * this = realloc(super, sizeof(*this));
	this->name = name;
	
	return this;
}

struct inner_node * inner_node_ctor(char * question) {
	struct node * super = node_ctor();
	super->vtable = &inner_node_funcs;
	
	struct inner_node * this = realloc(super, sizeof(*this));
	this->question = question;
	
	return this;
}
