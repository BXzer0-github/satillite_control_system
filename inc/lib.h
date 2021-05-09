#ifndef __lib__h
#define __lib__h
#include "y_int.h"
void*m_alloc(_int_u);
void m_free(void*);
void* m_realloc(void*,_int_u);
_int_u harvest(char*,char*,_16_u*,_16_u);
char* harvest_s(char*,char*,_16_u*,_16_u,_int_u*);
_64_u _ffly_dsn(char*, _int_u);
#endif/*__lib__h*/
