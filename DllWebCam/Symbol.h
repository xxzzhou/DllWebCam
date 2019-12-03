#ifndef _SYMBOL_H_
#define _SYMBOL_H_

typedef unsigned char  uchar;
typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

#ifndef MIN
#define MIN(a, b) ((a)<=(b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a)<=(b) ? (b) : (a))
#endif

#ifndef PI
#define PI 3.141592653589793
#endif

#ifndef __cplusplus
#define bool   int
#define false  0
#define true   1
#endif

#endif
