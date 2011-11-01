#pragma once

#include <stdio.h>
#include <stdbool.h>
struct node_vtable;

struct node {
	struct node_vtable * vtable;
	struct node * (*factory)(FILE * file);
};

struct leaf {
	struct node node;
	char * name;
};

struct inner_node {
	struct node node;
	char * question;
	struct node * yes;
	struct node * no;
};
