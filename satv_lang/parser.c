#include "satv_lang.h"
#include "../inc/io.h"
#include "../inc/def.h"
#include "../inc/lib.h"
#define new_val ((struct val_strc*)m_alloc(sizeof(struct val_strc)))
void static expr(void);
void exprn(void){
	svlcom.tok = nexttok();
	if(!svlcom.tok){
		while(1);
	}
	expr();
}
void static
primary_expr(void){
	if(svlcom.tok->sort == _tok_ident){
		struct symb *sy;
		sy = f_lhash_get(&svlcom.env,svlcom.tok->val,svlcom.tok->len);
		svlcom.val = &sy->val;
	}else if(svlcom.tok->sort == _tok_num){
		svlcom.val = new_val;
		_64_u val;
		val = _ffly_dsn(svlcom.tok->val,svlcom.tok->len);
		svlcom.val->type = VAL_IMM;
		svlcom.val->val = val;
	}
}

void static
assign_expr(void){
	if(nexttokis(_tok_keychr,_char_equal)){
		struct node *n;
		n = new_node();
		n->kind = NODE_ASSIGN;
		struct val_strc *sy;
		sy = svlcom.val;
		struct val_strc *val;
		svlcom.val = NULL;
		exprn();
		val = svlcom.val;
		n->l = sy;
		n->r = val;
	}
}

void
expr(void){
	primary_expr();
	assign_expr();
}

void static
decl(void){
	printf("decl.\n");
	struct token *name;
	name = nexttok();
	struct symb *sy;
	sy = symb_new(name->val,name->len);
	sy->val.type = VAL_SYM;
	sy->val.val = 0x40;
}

#define is_type(tok) (tok->sort == _tok_keywd && (tok->id == _tok_keywd_word_s || tok->id == _tok_keywd_word_u))
void svlang_parser(void){
	while((svlcom.tok = nexttok()) != NULL) {
		print_token(svlcom.tok);
		if(is_type(svlcom.tok)){
			decl();
		}else{
			expr();
		}
	}
}
