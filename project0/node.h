#pragma once

#include <stdio.h>
#include <stdbool.h>

struct node;

struct node_vtable {
	void (*ask_question)(struct node * this);
	struct node * (*process_answer)(char answer);
	struct iovec (*serialize)(struct node * this);
	void (*node_dtor)(struct node * this);
};

struct node {
	const struct node_vtable * vtable;
};

struct node * factory(FILE * file);

struct node * node_ctor(void);
void node_dtor(struct node * this);
void node_ask_question(struct node * this);
struct iovec node_serialize(struct node * this);

