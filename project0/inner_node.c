#include "inner_node.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/uio.h>

static const struct node_vtable inner_node_funcs = { /*TODO*/ NULL, NULL, NULL, NULL };

struct inner_node * inner_node_ctor(char * question, struct node * yes, struct node * no) {
	struct node * super = node_ctor();
	super->vtable = &inner_node_funcs;
	
	struct inner_node * this = realloc(super, sizeof(*this));
	this->question = malloc(strlen(question) + 1);
	strcpy(this->question, question);
	this->yes = yes;
	this->no = no;
	
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

struct node * inner_node_process_answer(struct node * super, char answer, struct inner_node * parent, struct node * root) {
	struct inner_node * this = (struct inner_node*)super;
	switch(answer) {
	case 'j':
		return this->yes;
		break;
	case 'n':
		return this->no;
		break;
	default:
		return (struct node*)this;
	}
}

struct iovec inner_node_serialize(struct node * super) {
	struct inner_node * this = (struct inner_node*)super;
	size_t question_len = strlen(this->question);
	uint32_t len_network_order = htonl(question_len);
	
	struct iovec yes_tree = node_serialize(this->yes);
	struct iovec no_tree = node_serialize(this->yes);
	
	struct iovec result;
	result.iov_len = sizeof(uint8_t) + sizeof(uint32_t) + question_len + yes_tree.iov_len + no_tree.iov_len;
	result.iov_base = malloc(result.iov_len);
	
	char * pos = result.iov_base;
	memset(pos, 0, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(pos, &len_network_order, sizeof(len_network_order));
	pos += sizeof(len_network_order);
	memcpy(pos, this->question, question_len);
	pos += question_len;
	memcpy(pos, yes_tree.iov_base, yes_tree.iov_len);
	pos += yes_tree.iov_len;
	memcpy(pos, no_tree.iov_base, no_tree.iov_len);
	
	free(yes_tree.iov_base);
	free(no_tree.iov_base);
	
	return result;
}


