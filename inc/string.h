#ifndef __string__h
#define __string__h
#include "y_int.h"
void bzero(void*, _64_u);
void bcopy(void*, void const*, _64_u);
void mem_cpy(void*, void const*, _64_u);
/*
  take caful condieration when using this
  when count is zero memory is still writen
  expects nonzero count
*/
void mem_cpyw(void*, void const*, _64_u);

_8_s mem_dup(void**, void const*, _64_u);
void* mem_set(void*, _8_u, _64_u);
_8_s mem_cmp(void const*, void const*, _64_u);
_64_u str_len(char const*);
char const* str_dup(char const*);
_8_s str_cmp(char const*, char const*);
_64_u str_len(char const*);
_64_u str_cpy(char*, char const*);
_8_s mem_cmpc(void const*, void const*, _64_u,_64_u);
_64_u str_cpyut(char const*,char const*,char);
#endif/*__string__h*/
