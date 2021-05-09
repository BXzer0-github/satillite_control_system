# ifndef __y__int__h
# define __y__int__h
//unt
typedef unsigned long long _ulonglong;

/*
	{DOM0}_{DOM1}
	DOM0 = CHARACTERISTICS{NAME,SIZE,BITORDER}
	DOM1 = ATTRIBUTES{SIGNED,UNSIGNED}
*/

typedef unsigned _128_u __attribute__((mode(TI)));
//new1
typedef unsigned char _8_u;
typedef signed char _8_i;
typedef signed char _8_s;

typedef unsigned short int _16_u;
typedef short int _16_i;
typedef short int _16_s;

typedef unsigned int _32_u;
typedef int _32_i;
typedef int _32_s;

typedef long long unsigned _64_u;
typedef long long int _64_i;
typedef long long int _64_s;

typedef unsigned char _char_u;
typedef char _char;
typedef signed char _char_s;

#define RETYPE(__typeid, __new)\
	typedef __typeid __new;
#define RETYPE3(__ts0, __tn0, __ts1, __tn1, __ts2, __tn2)\
RETYPE(__ts0, __tn0)\
RETYPE(__ts1, __tn1)\
RETYPE(__ts1, __tn2)

#ifdef __ff8
RETYPE3(
	_8_u, _int_u, 
	_8_s, _int_s, 
	_8_i, _int
);
#elif __ff16
RETYPE3(
	_16_u, _int_u,
	_16_s, _int_s,
	_16_i, _int
);
#elif __ff32
RETYPE3(
	_32_u, _int_u,
	_32_s, _int_s,
	_32_i, _int
);
#elif __ff64
RETYPE3(
	_64_u, _int_u,
	_64_s, _int_s,
	_64_i, _int
);
#else
RETYPE3(
	_32_u, _int_u,
	_32_s, _int_s,
	_32_i, _int
);
#endif
#endif /*__y__int__h*/
