#include "satv_lang.h"
#include "../inc/io.h"
#include "../inc/def.h"
#include "../inc/lib.h"
#define _ 0
struct svlang_comm svlcom = {
	.charmap = {
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_
	}
};

void static lazymap_chars(void){
	char c;
	c = 'a';
	for(;c != 'z'+1;c++){
		svlcom.charmap[c] = _char_let;
	}
	c = '0';
	for(;c != '9'+1;c++){
		svlcom.charmap[c] = _char_num;
	}

	svlcom.charmap['_'] = _char_underscore;
	svlcom.charmap['='] = _char_equal;
}
char const *toksort[] = {
	[_tok_ident]	= "ident",
	[_tok_num]		= "number",
	[_tok_keywd]		= "keyword",
	[_tok_keychr]		= "keychar"
};

void print_token(struct token *tok){
	printf("token-%s: value: %s.\n",toksort[tok->sort],tok->sort == _tok_keychr?"NONE":tok->val);
}

struct token* peektok(void){
	struct token *tok;
	tok = nexttok();
	svlcom.tokbuf = tok;
	return tok;
}
struct token* nexttok(void){
	if(svlcom.tokbuf != NULL){
		struct token *tok;
		tok = svlcom.tokbuf;
		svlcom.tokbuf = NULL;
		return tok;
	}
	struct token *tok;
	tok = svlang_lex();
	if(!tok)return NULL;
	if(tok->sort == _tok_ident){
		struct keywd *w;
		w = f_lhash_get(&svlcom.hm,tok->val,tok->len);
		if(w != NULL){
			tok->sort = _tok_keywd;
			tok->id = w->id;
		}
	}
	return tok;
}

void svlang_proceed(void){
	svlang_parser();
	svlang_gen();
}

#define N_KEYWORDS 2
static struct keywd keywords[] = {
	{
		.name = "word_s",
		.len = 6,
		.id = _tok_keywd_word_s
	},
	{
		.name = "word_u",
		.len = 6,
		.id = _tok_keywd_word_u
	}
};

_8_s istok(struct token *tok,_8_u __sort,_8_u __id){
	if(!tok)
		return 0;
	return (tok->sort == __sort && tok->id == __id);
}

struct symb* symb_new(char const *__name,_int_u __len){
	struct symb *sy;
	sy = m_alloc(sizeof(struct symb));
	sy->name = __name;
	f_lhash_put(&svlcom.env,__name,__len,sy);
	return sy;
}

_8_s nexttokis(_8_u __sort,_8_u __id){
	struct token *tok;
	tok = nexttok();
	if(!tok)return 0;
	if(istok(tok,_tok_keychr,_char_equal)){
		return 1;
	}
	svlcom.tokbuf = tok;
	return 0;
}
struct node* new_node(void) {
	struct node *n;
	n = m_alloc(sizeof(struct node));
	if(!svlcom.head)
		svlcom.head = n;
	
	if(svlcom.tail != NULL){
		svlcom.tail->next = n;
	}
	n->next = NULL;
	svlcom.tail = n;
	return n;
}

void svlang_init(void){
	svlcom.head = NULL;
	svlcom.tail = NULL;
	svlcom.off = 0;
	svlcom.tokbuf = NULL;
	lazymap_chars();
	f_lhash_init(&svlcom.hm);
	f_lhash_init(&svlcom.env);
	_int_u i;
	i = 0;
	for(;i != N_KEYWORDS;i++){
		struct keywd *w;
		w = keywords+i;
		f_lhash_put(&svlcom.hm,w->name,w->len,w);
	}
}
