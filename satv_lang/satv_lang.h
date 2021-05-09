#ifndef __satv__lang__h
#define __satv__lang__h
#include "../inc/y_int.h"
#include "../inc/types.h"
#include "../inc/hash.h"
struct symb;
struct node;
#define VAL_IMM	0
#define VAL_SYM	1
struct val_strc{
	_64_u val;
	_8_u type;
};
struct svlang_comm{
	_16_u charmap[0x100];
	char *program;
	_int_u len;
	_int_u off;
	struct f_lhash hm;
	struct f_lhash env;

	struct token *tokbuf;
	struct token *tok;
	struct val_strc *val;
	struct node *head,*tail;
};

struct symb{
	char *name;
	struct val_strc val;
};

struct token{
	_8_u sort;
	_8_u id;
	char const *val;
	_int_u len;
};
struct keywd{
	char const *name;
	_int_u len;
	_8_u id;
};
#define NODE_ASSIGN 0

struct node{
	_int_u kind;
	struct val_strc *l,*r;

	struct node *next;
};

#define _char_let					1
#define _char_num					2
#define _char_underscore	4
#define _char_equal				8
enum{
	_tok_ident,
	_tok_num,
	_tok_keywd,
	_tok_keychr
};

enum{
	_tok_keywd_word_s,
	_tok_keywd_word_u
};
struct node* new_node(void);
_8_s nexttokis(_8_u,_8_u);
struct token* peektok(void);
_8_s istok(struct token*,_8_u,_8_u);
struct symb* symb_new(char const*,_int_u);
void print_token(struct token*);
void svlang_parser(void);
struct token* svlang_lex(void);
struct token* nexttok(void);
void svlang_proceed(void);
void svlang_init(void);
void svlang_gen(void);
extern struct svlang_comm svlcom;
#endif/*__satv__lang__h*/
