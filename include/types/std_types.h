#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef signed char s8;             /* 1 byte  = 8 bit  */
typedef unsigned char u8;           /* 1 byte  = 8 bit  */

typedef signed short int s16;       /* 2 bytes = 16 bit */
typedef unsigned short int u16;     /* 2 bytes = 16 bit */

typedef signed long int s32;        /* 4 bytes = 32 bit */
typedef unsigned long int u32;      /* 4 bytes = 32 bit */

typedef signed long long int s64;   /* 8 bytes = 64 bit */
typedef unsigned long long int u64; /* 8 bytes = 64 bit */

typedef float f32;                  /* 4 bytes  = 32 bit  */
typedef double f64;                 /* 8 bytes  = 64 bit  */
typedef long double f128;           /* 16 bytes = 128 bit */

typedef enum {
    VALID,
    INVALID,
} ErrorCode;

#endif /* STD_TYPES_H */
