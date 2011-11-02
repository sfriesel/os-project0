#pragma once

#include <stdio.h>
#include <stdbool.h>

struct node;

struct node_vtable {
	void (*ask_question)(struct node * this);
	struct node * (*process_answer)(struct node * this, char answer, struct node * parent, struct node * root);
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
struct node * node_process_answer(struct node * this, char answer, struct node * parent, struct node * root);
struct iovec node_serialize(struct node * this);

