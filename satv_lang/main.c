#include "satv_lang.h"
#include "../inc/lib.h"
#include "../inc/file.h"
#include "../inc/io.h"
#include "../inc/types.h"
#include "../inc/y_int.h"
struct svlang_comm svlcom;
_y_err main(int __argc, char const *__argv[]) {
	if(__argc<2){
		printf("please provide file.\n");
		return -1;
	}
	struct file test;
	bopen(&test,__argv[1],_O_RDONLY,_S_IRWXU);
	struct _stat st;
	bstat(&test,&st);
	svlcom.program = m_alloc(st.st_size);	
	bread(&test,svlcom.program,st.st_size);
	bclose(&test);
	svlcom.len = st.st_size;
	svlang_init();
	svlang_proceed();
	return 0;
}
