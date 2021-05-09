# ifndef __f__lib__hash__h
# define __f__lib__hash__h
#include "y_int.h"
struct f_lhash_entry {
    struct f_lhash_entry *fd, *next;
    _8_u const *key;
    _int_u len;
    void *p;
};

struct f_lhash {
    struct f_lhash_entry **table;
    struct f_lhash_entry *top;
};

void f_lhash_init(struct f_lhash*);
void f_lhash_destroy(struct f_lhash*);
void f_lhash_put(struct f_lhash*, _8_u const*, _int_u, void*);
void* f_lhash_get(struct f_lhash*, _8_u const*, _int_u);
# endif /*__f__lib__hash__h*/
