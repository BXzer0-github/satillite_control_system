#ifndef __base__file__h
#define __base__file__h
#include "y_int.h"
#include "types.h"
/*
	low level OS file access 
	no pointer function, tricks, buffers, etc 
	direct

	b = basal??? "forming or belonging to a bottom layer or base."
	sorry but im not spending any time naming this shit
*/
struct file {
	_8_u data[0x100];
};
struct _stat {
	_int_u st_size;
};
#define _O_RDONLY	(4|0)
#define _O_WRONLY	(4|1)
#define _O_RDWR		(4|2)
#define _O_TRUNC	8
#define _O_CREAT	16

#define _S_IRWXU 00700 // user: r/w/x
#define _S_IRUSR 00400 // user: r
#define _S_IWUSR 00200 // user: w
#define _S_IXUSR 00100 // user: x

#define _S_IRWXG 00070 // group: r/w/x
#define _S_IRGRP 00040 // group: r
#define _S_IWGRP 00020 // group: w
#define _S_IXGRP 00010 // group: x

#define _S_IRWXO 00007 // others: r/w/x
#define _S_IROTH 00004 // others: r
#define _S_IWOTH 00002 // others: w
#define _S_IXOTH 00001 // others: x
_8_s bopen(struct file*,char const*,_64_u,_64_u);
void bwrite(struct file*,void*,_int_u);
void bread(struct file*,void*,_int_u);
void bpwrite(struct file*,void*,_int_u,_64_u);
void bpread(struct file*,void*,_int_u,_64_u);
void bclose(struct file*);
void bstat(struct file*,struct _stat*);
#endif /*__base__file__h*/
