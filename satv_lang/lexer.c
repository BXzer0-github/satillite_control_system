#include "../inc/lib.h"
#include "../inc/string.h"
#include "satv_lang.h"
#include "../inc/def.h"
#define CHRPTR	(svlcom.program+svlcom.off)
#define GETCHR	svlcom.program[svlcom.off]
#define INCR		svlcom.off++;

struct token*
svlang_lex(void){
_again:
	if(svlcom.off == svlcom.len)
		return NULL;
	
	char ch;
	ch = GETCHR;

	if(ch == ' ' || ch == '\n' || ch == '\t'){
		INCR
		goto _again;		
	}

	struct token *tok;
	tok = m_alloc(sizeof(struct token));

	char buf[128];
	_16_u c;
	c = svlcom.charmap[ch];
	
	if(c&_char_let){
		tok->val = harvest_s(buf,CHRPTR,svlcom.charmap,_char_let|_char_num|_char_underscore,&tok->len);
		tok->sort = _tok_ident;
		svlcom.off+=tok->len;
	}else if(c&_char_num){
		tok->val = harvest_s(buf,CHRPTR,svlcom.charmap,_char_num,&tok->len);
		tok->sort = _tok_num;
		svlcom.off+=tok->len;
	}else if(c&(_char_equal)){
		tok->sort = _tok_keychr;
		tok->id = c;
		INCR
	}	
	return tok;
}
