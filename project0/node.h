#pragma once

#include <stdio.h>
#include <stdbool.h>

struct node;

struct node_vtable {
	bool (*ask_question)(struct node * this);
	char * (*serialize)(struct node * this);
	void (*node_dtor)(struct node * this);
};

struct node {
	const struct node_vtable * vtable;
};

struct node factory(FILE * file);

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

struct node * node_ctor(void);

struct leaf * leaf_ctor(char * name);
void leaf_dtor(struct leaf * this);

struct inner_node * inner_node_ctor(char * question);
void inner_node_dtor(struct inner_node * this);
