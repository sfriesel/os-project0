#include "leaf.h"

static const struct node_vtable leaf_funcs = { /*TODO*/ NULL, NULL, NULL, NULL };

struct leaf * leaf_ctor(char * name) {
	struct node * super = node_ctor();
	super->vtable = &leaf_funcs;
	
	struct leaf * this = realloc(super, sizeof(*this));
	this->name = malloc(strlen(name) + 1);
	strcpy(this->name, name);
	
	return this;
}

void leaf_dtor(struct leaf * this) {
	free(this->name);
	node_dtor(&this->node);
}

void leaf_ask_question(struct node * super) {
	struct leaf * this = (struct leaf*)super;
	printf("Is it a %s?\n", this->name);
}
