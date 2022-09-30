#pragma once

// STATE always process in word
#define SHA1_DIGST_SZ_IN_BT 20 //
#define SHA1_STATE_SZ_IN_WD 5  //  5w 20B 160b
#define SHA1_BLOCK_SZ_IN_BT 64 // 16w 64B 512b

// #define rot_left(X, n) (((X) << (n)) | ((X) >> (32 - (n))))
#define rot_left(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

inline static uint32_t rol(const uint32_t value, const size_t bits)
{
    return (value << bits) | (value >> (32 - bits));
}

inline static uint32_t blk(const uint32_t *block, const size_t i)
{
    return rol(block[(i + 13) & 15] ^ block[(i + 8) & 15] ^ block[(i + 2) & 15] ^ block[i], 1);
}

/*
 * (R0+R1), R2, R3, R4 are the different operations used in SHA1
 */

inline static void R0(const uint32_t *block, const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i)
{
    z += ((w & (x ^ y)) ^ y) + block[i] + 0x5a827999 + rol(v, 5);
    w = rol(w, 30);
}

inline static void R1(uint32_t *block, const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i)
{
    block[i] = blk(block, i);
    z += ((w & (x ^ y)) ^ y) + block[i] + 0x5a827999 + rol(v, 5);
    w = rol(w, 30);
}

inline static void R2(uint32_t *block, const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i)
{
    block[i] = blk(block, i);
    z += (w ^ x ^ y) + block[i] + 0x6ed9eba1 + rol(v, 5);
    w = rol(w, 30);
}

inline static void R3(uint32_t *block, const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i)
{
    block[i] = blk(block, i);
    z += (((w | x) & y) | (w & x)) + block[i] + 0x8f1bbcdc + rol(v, 5);
    w = rol(w, 30);
}

inline static void R4(uint32_t *block, const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i)
{
    block[i] = blk(block, i);
    z += (w ^ x ^ y) + block[i] + 0xca62c1d6 + rol(v, 5);
    w = rol(w, 30);
}

// big endian: to bytes / from bytes
#define PUTU16(p, V) ((p)[0] = (uint8_t)((V) >> 8), (p)[1] = (uint8_t)(V))
#define PUTU32(p, V)                                               \
    ((p)[0] = (uint8_t)((V) >> 24), (p)[1] = (uint8_t)((V) >> 16), \
     (p)[2] = (uint8_t)((V) >> 8), (p)[3] = (uint8_t)(V))
#define PUTU64(p, V)                                               \
    ((p)[0] = (uint8_t)((V) >> 56), (p)[1] = (uint8_t)((V) >> 48), \
     (p)[2] = (uint8_t)((V) >> 40), (p)[3] = (uint8_t)((V) >> 32), \
     (p)[4] = (uint8_t)((V) >> 24), (p)[5] = (uint8_t)((V) >> 16), \
     (p)[6] = (uint8_t)((V) >> 8), (p)[7] = (uint8_t)(V))

#define GETU16(p) ((uint16_t)(p)[0] << 8 | (uint16_t)(p)[1])
#define GETU32(p) \
    ((uint32_t)(p)[0] << 24 | (uint32_t)(p)[1] << 16 | (uint32_t)(p)[2] << 8 | (uint32_t)(p)[3])
#define GETU64(p) \
    ((uint64_t)(p)[0] << 56 | (uint64_t)(p)[1] << 48 | (uint64_t)(p)[2] << 40 | (uint64_t)(p)[3] << 32 | (uint64_t)(p)[4] << 24 | (uint64_t)(p)[5] << 16 | (uint64_t)(p)[6] << 8 | (uint64_t)(p)[7])
