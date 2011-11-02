#include "leaf.h"
#include "inner_node.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/uio.h>

void leaf_ask_question(struct node * super);
struct node * leaf_process_answer(struct node * super, char answer, struct node ** root);
struct iovec leaf_serialize(struct node * super);
void leaf_dtor(struct node * this);

static const struct node_vtable leaf_funcs = {
	.ask_question = leaf_ask_question,
	.process_answer = leaf_process_answer,
	.serialize = leaf_serialize,
	.node_dtor = leaf_dtor
};

struct leaf * leaf_ctor(char * name) {
	struct node * super = node_ctor(NULL);
	super->vtable = &leaf_funcs;
	
	struct leaf * this = realloc(super, sizeof(*this));
	this->name = malloc(strlen(name) + 1);
	strcpy(this->name, name);
	
	return this;
}

void leaf_dtor(struct node * super) {
	struct leaf * this = (struct leaf*)super;
	free(this->name);
	node_dtor(&this->node);
}

void leaf_ask_question(struct node * super) {
	struct leaf * this = (struct leaf*)super;
	printf("Is it a %s?\n", this->name);
}

struct node * leaf_process_answer(struct node * super, char answer, struct node ** root) {
	struct leaf * this = (struct leaf*)super;
	switch(answer) {
	case 'j':
		return *root;
		break;
	case 'n':
		{
			puts("What animal where you thinking of?");
			char input[1024];
			fgets(input, sizeof(input), stdin);
			if(ferror(stdin) || feof(stdin)) {
				exit(1);
			}
			struct leaf * new_leaf = leaf_ctor(input);
			if(!*root) {
				*root = (struct node*)new_leaf;
				return *root;
			}
			
			puts("Enter a question so that the answer is 'yes' for your animal and 'no' for the other one.\n");
			fgets(input, sizeof(input), stdin);
			if(ferror(stdin) || feof(stdin)) {
				exit(1);
			}
			struct inner_node * new_node = inner_node_ctor(input, &new_leaf->node, &this->node);
			
			if(!this->node.parent) {
				*root = &new_node->node;
			} else if(this->node.parent->yes == &this->node) {
				this->node.parent->yes = &new_node->node;
			} else {
				this->node.parent->no = &new_node->node;
			}
			return *root;
		}
		break;
	default:
		return (struct node*)this;
	}
}

struct iovec leaf_serialize(struct node * super) {
	struct leaf * this = (struct leaf*)super;
	size_t name_len = strlen(this->name);
	uint32_t len_network_order = htonl(name_len);
	
	struct iovec result;
	result.iov_len = sizeof(uint8_t) + sizeof(uint32_t) + name_len;
	result.iov_base = malloc(result.iov_len);
	
	char * pos = result.iov_base;
	memset(pos, 1, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(pos, &len_network_order, sizeof(len_network_order));
	pos += sizeof(len_network_order);
	memcpy(pos, this->name, name_len);
	
	return result;
}
