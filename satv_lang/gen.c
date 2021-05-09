#include "satv_lang.h"
#include "../inc/io.h"
#include "../inc/def.h"
#include "../inc/lib.h"

void static
out_assign(struct node *__n){
	printf("assign: (%x)=%u.\n",__n->l->val,__n->r->val);
}

void(*out[])(struct node*) = {
	out_assign
};

void svlang_gen(void){
	struct node *n;
	n = svlcom.head;
	while(n != NULL){
		out[n->kind](n);
		n = n->next;
	}
}
