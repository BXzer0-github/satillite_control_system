cc_flags="-nostdlib -O0 -g -fno-builtin -mincoming-stack-boundary=4 -std=c99"
cc_objs="lexer.o satv_lang.o gen.o parser.o ../lib/yage.o"
gcc $cc_flags -c gen.c
gcc $cc_flags -c parser.c
gcc $cc_flags -c satv_lang.c
gcc $cc_flags -c lexer.c
gcc $cc_flags main.c $cc_objs
