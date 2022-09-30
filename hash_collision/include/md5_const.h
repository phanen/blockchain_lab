#pragma once

// STATE always process in word
#define MD5_STATE_SZ_IN_WD 4  //  4w 16B 128b
#define MD5_BLOCK_SZ_IN_BT 64 // 16w 64B 512b

#define F(x, y, z) (((x) & (y)) | ((~(x)) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~(z))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~(z))))

// #define rot_left(X, n) (((X) << (n)) | ((X) >> (32 - (n))))
#define rot_left(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define FF(a, b, c, d, x, s, ac)                        \
    {                                                   \
        (a) += F((b), (c), (d)) + (x) + (uint32_t)(ac); \
        (a) = rot_left((a), (uint32_t)(s));             \
        (a) += (b);                                     \
    }
#define GG(a, b, c, d, x, s, ac)                        \
    {                                                   \
        (a) += G((b), (c), (d)) + (x) + (uint32_t)(ac); \
        (a) = rot_left((a), (uint32_t)(s));             \
        (a) += (b);                                     \
    }
#define HH(a, b, c, d, x, s, ac)                        \
    {                                                   \
        (a) += H((b), (c), (d)) + (x) + (uint32_t)(ac); \
        (a) = rot_left((a), (uint32_t)(s));             \
        (a) += (b);                                     \
    }
#define II(a, b, c, d, x, s, ac)                        \
    {                                                   \
        (a) += I((b), (c), (d)) + (x) + (uint32_t)(ac); \
        (a) = rot_left((a), (uint32_t)(s));             \
        (a) += (b);                                     \
    }

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// legacy
// #define F(X, Y, Z) (((X) & (Y)) | ((~(X)) & (Z)))
// #define G(X, Y, Z) (((X) & (Z)) | ((Y) & (~(Z))))
// #define H(X, Y, Z) ((X) ^ (Y) ^ (Z))
// #define I(X, Y, Z) (X) ^ ((Y) & (~(Z)))
// #define F0 F
// #define F1 G
// #define F2 H
// #define F3 I

// #define ABCD(id, T, k, s) A = B + rot_left((A + F##id(B, C, D) + X[k] + T), s)
// #define DABC(id, T, k, s) D = A + rot_left((D + F##id(A, B, C) + X[k] + T), s)
// #define CDAB(id, T, k, s) C = D + rot_left((C + F##id(D, A, B) + X[k] + T), s)
// #define BCDA(id, T, k, s) B = C + rot_left((B + F##id(C, D, A) + X[k] + T), s)

// const uint32_t T[64] = {
//     0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
//     0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
//     0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
//     0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
//     0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
//     0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
//     0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
//     0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 //
// };
