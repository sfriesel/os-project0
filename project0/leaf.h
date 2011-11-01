#pragma once

#include "leaf.c"

struct leaf {
	struct node node;
	char * name;
};

struct leaf * leaf_ctor(char * name);
void leaf_dtor(struct leaf * this);

