#include "inner_node.h"

static const struct node_vtable inner_node_funcs = { /*TODO*/ NULL, NULL, NULL, NULL };

struct inner_node * inner_node_ctor(char * question) {
	struct node * super = node_ctor();
	super->vtable = &inner_node_funcs;
	
	struct inner_node * this = realloc(super, sizeof(*this));
	this->question = malloc(strlen(question) + 1);
	strcpy(this->question, question);
	
	return this;
}

void inner_node_dtor(struct inner_node * this) {
	free(this->question);
	node_dtor(&this->node);
}

void inner_node_ask_question(struct node * super) {
	struct inner_node * this = (struct inner_node*)super;
	printf("%s\n", this->question);
}


