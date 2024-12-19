#ifndef MEH_BITS_H_
#define MEH_BITS_H_

#include "meh_types.h"

/* -----------------------------------------------------------------------------
 * Defines
 * ----------------------------------------------------------------------------- */

#define meh_bit_size(X) (sizeof(X) * 8)
#define meh_byte_size sizeof

#define MEH_INT_BITS meh_bit_size(int)
#define MEH_CHAR_BITS meh_bit_size(char)
#define MEH_WORD_BITS meh_bit_size(meh_word_t)
#define MEH_SHORT_BITS meh_bit_size(short int)
#define MEH_LONGINT_BITS meh_bit_size(long int)

#define MEH_INT_BYTES meh_byte_size(int)
#define MEH_CHAR_BYTES meh_byte_size(char)
#define MEH_WORD_BYTES meh_byte_size(meh_word_t)
#define MEH_SHORT_BYTES meh_byte_size(short int)
#define MEH_LONGINT_BYTES meh_byte_size(long int)

#define MEH_WORD_INTS (MEH_WORD_BITS / MEH_INT_BITS)
#define MEH_WORD_CHARS (MEH_WORD_BITS / MEH_CHAR_BITS)
#define MEH_WORD_SHORTS (MEH_WORD_BITS / MEH_SHORT_BITS)
#define MEH_WORD_LONGS (MEH_WORD_BITS / MEH_LONGINT_BITS)

/* -----------------------------------------------------------------------------
 * Method Declarations
 * ----------------------------------------------------------------------------- */

extern union meh_bitvec
meh_bits_get(meh_word_t val, size_t high, size_t low);

extern union meh_bitvec
meh_bits_set(meh_word_t dst, size_t high, size_t low, meh_word_t src);

extern union meh_bitvec
meh_bits_toggle(meh_word_t val, size_t high, size_t low);

extern int
meh_bits_compare(
    meh_word_t a,
    meh_word_t ahigh,
    meh_word_t alow,
    meh_word_t b,
    meh_word_t bhigh,
    meh_word_t blow);

extern size_t
meh_bits_countones(meh_word_t value);

extern size_t
meh_bits_countzeros(meh_word_t value);

/* -----------------------------------------------------------------------------
 * Structs
 * ----------------------------------------------------------------------------- */

struct meh_bits8 {
    meh_u8_t bit0 : 1;
    meh_u8_t bit1 : 1;
    meh_u8_t bit2 : 1;
    meh_u8_t bit3 : 1;
    meh_u8_t bit4 : 1;
    meh_u8_t bit5 : 1;
    meh_u8_t bit6 : 1;
    meh_u8_t bit7 : 1;
};

struct meh_bits16 {
    meh_u16_t bit0 : 1;
    meh_u16_t bit1 : 1;
    meh_u16_t bit2 : 1;
    meh_u16_t bit3 : 1;
    meh_u16_t bit4 : 1;
    meh_u16_t bit5 : 1;
    meh_u16_t bit6 : 1;
    meh_u16_t bit7 : 1;
    meh_u16_t bit8 : 1;
    meh_u16_t bit9 : 1;
    meh_u16_t bit10 : 1;
    meh_u16_t bit11 : 1;
    meh_u16_t bit12 : 1;
    meh_u16_t bit13 : 1;
    meh_u16_t bit14 : 1;
    meh_u16_t bit15 : 1;
};

struct meh_bits32 {
    meh_u32_t b0 : 1;
    meh_u32_t b1 : 1;
    meh_u32_t b2 : 1;
    meh_u32_t b3 : 1;
    meh_u32_t b4 : 1;
    meh_u32_t b5 : 1;
    meh_u32_t b6 : 1;
    meh_u32_t b7 : 1;
    meh_u32_t b8 : 1;
    meh_u32_t b9 : 1;
    meh_u32_t b10 : 1;
    meh_u32_t b11 : 1;
    meh_u32_t b12 : 1;
    meh_u32_t b13 : 1;
    meh_u32_t b14 : 1;
    meh_u32_t b15 : 1;
    meh_u32_t b16 : 1;
    meh_u32_t b17 : 1;
    meh_u32_t b18 : 1;
    meh_u32_t b19 : 1;
    meh_u32_t b20 : 1;
    meh_u32_t b21 : 1;
    meh_u32_t b22 : 1;
    meh_u32_t b23 : 1;
    meh_u32_t b24 : 1;
    meh_u32_t b25 : 1;
    meh_u32_t b26 : 1;
    meh_u32_t b27 : 1;
    meh_u32_t b28 : 1;
    meh_u32_t b29 : 1;
    meh_u32_t b30 : 1;
    meh_u32_t b31 : 1;
};

struct meh_bits64 {
    meh_u64_t b0 : 1;
    meh_u64_t b1 : 1;
    meh_u64_t b2 : 1;
    meh_u64_t b3 : 1;
    meh_u64_t b4 : 1;
    meh_u64_t b5 : 1;
    meh_u64_t b6 : 1;
    meh_u64_t b7 : 1;
    meh_u64_t b8 : 1;
    meh_u64_t b9 : 1;
    meh_u64_t b10 : 1;
    meh_u64_t b11 : 1;
    meh_u64_t b12 : 1;
    meh_u64_t b13 : 1;
    meh_u64_t b14 : 1;
    meh_u64_t b15 : 1;
    meh_u64_t b16 : 1;
    meh_u64_t b17 : 1;
    meh_u64_t b18 : 1;
    meh_u64_t b19 : 1;
    meh_u64_t b20 : 1;
    meh_u64_t b21 : 1;
    meh_u64_t b22 : 1;
    meh_u64_t b23 : 1;
    meh_u64_t b24 : 1;
    meh_u64_t b25 : 1;
    meh_u64_t b26 : 1;
    meh_u64_t b27 : 1;
    meh_u64_t b28 : 1;
    meh_u64_t b29 : 1;
    meh_u64_t b30 : 1;
    meh_u64_t b31 : 1;
    meh_u64_t b32 : 1;
    meh_u64_t b33 : 1;
    meh_u64_t b34 : 1;
    meh_u64_t b35 : 1;
    meh_u64_t b36 : 1;
    meh_u64_t b37 : 1;
    meh_u64_t b38 : 1;
    meh_u64_t b39 : 1;
    meh_u64_t b40 : 1;
    meh_u64_t b41 : 1;
    meh_u64_t b42 : 1;
    meh_u64_t b43 : 1;
    meh_u64_t b44 : 1;
    meh_u64_t b45 : 1;
    meh_u64_t b46 : 1;
    meh_u64_t b47 : 1;
    meh_u64_t b48 : 1;
    meh_u64_t b49 : 1;
    meh_u64_t b50 : 1;
    meh_u64_t b51 : 1;
    meh_u64_t b52 : 1;
    meh_u64_t b53 : 1;
    meh_u64_t b54 : 1;
    meh_u64_t b55 : 1;
    meh_u64_t b56 : 1;
    meh_u64_t b57 : 1;
    meh_u64_t b58 : 1;
    meh_u64_t b59 : 1;
    meh_u64_t b60 : 1;
    meh_u64_t b61 : 1;
    meh_u64_t b62 : 1;
    meh_u64_t b63 : 1;
};

/* -----------------------------------------------------------------------------
 * Unions
 * ----------------------------------------------------------------------------- */

union meh_bitvec {
    meh_i8_t i8[MEH_WORD_BYTES];
    meh_u8_t u8[MEH_WORD_BYTES];
    meh_i16_t i16[MEH_WORD_BYTES / 2];
    meh_u16_t u16[MEH_WORD_BYTES / 2];
    meh_i32_t i32[MEH_WORD_BYTES / 4];
    meh_u32_t u32[MEH_WORD_BYTES / 4];
    meh_i64_t i64[MEH_WORD_BYTES / 8];
    meh_u64_t u64[MEH_WORD_BYTES / 8];
    meh_word_t word;
    meh_bits64_t bits;
    meh_bytes64_t bytes;
};

#endif
