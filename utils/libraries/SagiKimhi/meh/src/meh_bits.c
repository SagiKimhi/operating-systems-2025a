#include "meh_bits.h"

/* -----------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------- */

#ifndef meh_as_bitvec
# define meh_as_bitvec(w) ((meh_bitvec_t){.word = (w)})
#endif

#ifndef meh_bit_cast
# define meh_bit_cast(V) ((meh_word_t)(V))
#endif

#ifndef meh_bit_size
# define meh_bit_size(T) (sizeof(T) * MEH_BYTE_BITS)
#endif

#ifndef meh_bit_mask
# define meh_bit_mask(H, L) ((~(meh_bit_cast(~0) << ((H) - (L)))) << ((H) - (L)))
#endif

#ifndef meh_get_bits
# define meh_get_bits(V, H, L) (meh_bit_mask(H, L) & meh_bit_cast(V))
#endif

#ifndef meh_set_bits
# define meh_set_bits(DEST, H, L, V)               \
     (((~meh_bit_mask(H, L)) & meh_bit_cast(DEST)) \
      | (meh_bit_mask(H, L) & meh_bit_cast(V)))
#endif

#ifndef meh_toggle_bits
# define meh_toggle_bits(V, H, L) meh_set_bits(V, H, L, (~meh_get_bits(V, H, L)))
#endif

#ifndef meh_compare_bits
# define meh_compare_bits(A, AH, AL, B, BH, BL) \
     (meh_get_bits(A, AH, AL) == meh_get_bits(B, BH, BL))
#endif

/* -----------------------------------------------------------------------------
 * Method Definitions
 * ----------------------------------------------------------------------------- */

meh_bitvec_t
meh_bits_get(size_t val, size_t high, size_t low)
{
    return meh_as_bitvec(meh_get_bits(val, high, low));
}

meh_bitvec_t
meh_bits_set(size_t dst, size_t high, size_t low, size_t src)
{
    return meh_as_bitvec(meh_set_bits(dst, high, low, src));
}

meh_bitvec_t
meh_bits_toggle(size_t val, size_t high, size_t low)
{
    return meh_as_bitvec(meh_toggle_bits(val, high, low));
}

int
meh_bits_compare(
    meh_word_t a,
    meh_word_t ahigh,
    meh_word_t alow,
    meh_word_t b,
    meh_word_t bhigh,
    meh_word_t blow)
{
    return meh_compare_bits(a, ahigh, alow, b, bhigh, blow);
}

size_t
meh_bits_countones(size_t value)
{
    return (meh_bit_size(value) - meh_bits_countzeros(value));
}

size_t
meh_bits_countzeros(size_t value)
{
    int count;

    for (count = 0; value; count++)
        value &= value - 1;

    return count;
}
