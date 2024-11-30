#ifndef _MEH_TYPES_H
#define _MEH_TYPES_H

#include <sys/types.h>

typedef signed char meh_i8_t;
typedef __S16_TYPE meh_i16_t;
typedef __S32_TYPE meh_i32_t;
typedef __S64_TYPE meh_i64_t;

typedef unsigned char meh_u8_t;
typedef __U16_TYPE meh_u16_t;
typedef __U32_TYPE meh_u32_t;
typedef __U64_TYPE meh_u64_t;

typedef __UWORD_TYPE meh_word_t;
typedef __UWORD_TYPE meh_uword_t;
typedef __SWORD_TYPE meh_sword_t;

typedef meh_u8_t meh_byte_t;
typedef meh_u8_t meh_bytes_t[];
typedef meh_u8_t meh_bytes8_t[1];
typedef meh_u8_t meh_bytes16_t[2];
typedef meh_u8_t meh_bytes32_t[4];
typedef meh_u8_t meh_bytes64_t[8];

typedef struct meh_bits8 meh_bits8_t;
typedef struct meh_bits16 meh_bits16_t;
typedef struct meh_bits32 meh_bits32_t;
typedef struct meh_bits64 meh_bits64_t;

typedef union meh_bitvec8 meh_bitvec8_t;
typedef union meh_bitvec16 meh_bitvec16_t;
typedef union meh_bitvec32 meh_bitvec32_t;
typedef union meh_bitvec64 meh_bitvec64_t;

typedef union meh_bitvec meh_bitvec_t;
typedef struct meh_darray meh_darray_t;
typedef struct meh_process meh_process_t;
typedef struct meh_process_list meh_process_list_t;

#endif
