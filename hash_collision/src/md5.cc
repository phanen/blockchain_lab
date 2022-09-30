#include "../include/md5.h"
#include "../include/md5_const.h"

static inline void md5_cf(uint32_t state[MD5_STATE_SZ_IN_WD], const uint8_t *input, size_t num_blks)
{
    uint32_t a, b, c, d;
    uint32_t x[MD5_BLOCK_SZ_IN_BT / 4];

    while (num_blks--)
    {
        for (size_t i = 0; i < MD5_BLOCK_SZ_IN_BT / 4; i++)
            x[i] = *(uint32_t *)(input + i * 4);
        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];

        /* Round 1 */
        FF(a, b, c, d, x[0], S11, 0xd76aa478);  /* 1 */
        FF(d, a, b, c, x[1], S12, 0xe8c7b756);  /* 2 */
        FF(c, d, a, b, x[2], S13, 0x242070db);  /* 3 */
        FF(b, c, d, a, x[3], S14, 0xc1bdceee);  /* 4 */
        FF(a, b, c, d, x[4], S11, 0xf57c0faf);  /* 5 */
        FF(d, a, b, c, x[5], S12, 0x4787c62a);  /* 6 */
        FF(c, d, a, b, x[6], S13, 0xa8304613);  /* 7 */
        FF(b, c, d, a, x[7], S14, 0xfd469501);  /* 8 */
        FF(a, b, c, d, x[8], S11, 0x698098d8);  /* 9 */
        FF(d, a, b, c, x[9], S12, 0x8b44f7af);  /* 10 */
        FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
        FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
        FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
        FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
        FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
        FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

        /* Round 2 */
        GG(a, b, c, d, x[1], S21, 0xf61e2562);  /* 17 */
        GG(d, a, b, c, x[6], S22, 0xc040b340);  /* 18 */
        GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
        GG(b, c, d, a, x[0], S24, 0xe9b6c7aa);  /* 20 */
        GG(a, b, c, d, x[5], S21, 0xd62f105d);  /* 21 */
        GG(d, a, b, c, x[10], S22, 0x2441453);  /* 22 */
        GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
        GG(b, c, d, a, x[4], S24, 0xe7d3fbc8);  /* 24 */
        GG(a, b, c, d, x[9], S21, 0x21e1cde6);  /* 25 */
        GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
        GG(c, d, a, b, x[3], S23, 0xf4d50d87);  /* 27 */
        GG(b, c, d, a, x[8], S24, 0x455a14ed);  /* 28 */
        GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
        GG(d, a, b, c, x[2], S22, 0xfcefa3f8);  /* 30 */
        GG(c, d, a, b, x[7], S23, 0x676f02d9);  /* 31 */
        GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

        /* Round 3 */
        HH(a, b, c, d, x[5], S31, 0xfffa3942);  /* 33 */
        HH(d, a, b, c, x[8], S32, 0x8771f681);  /* 34 */
        HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
        HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
        HH(a, b, c, d, x[1], S31, 0xa4beea44);  /* 37 */
        HH(d, a, b, c, x[4], S32, 0x4bdecfa9);  /* 38 */
        HH(c, d, a, b, x[7], S33, 0xf6bb4b60);  /* 39 */
        HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
        HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
        HH(d, a, b, c, x[0], S32, 0xeaa127fa);  /* 42 */
        HH(c, d, a, b, x[3], S33, 0xd4ef3085);  /* 43 */
        HH(b, c, d, a, x[6], S34, 0x4881d05);   /* 44 */
        HH(a, b, c, d, x[9], S31, 0xd9d4d039);  /* 45 */
        HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
        HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
        HH(b, c, d, a, x[2], S34, 0xc4ac5665);  /* 48 */

        /* Round 4 */
        II(a, b, c, d, x[0], S41, 0xf4292244);  /* 49 */
        II(d, a, b, c, x[7], S42, 0x432aff97);  /* 50 */
        II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
        II(b, c, d, a, x[5], S44, 0xfc93a039);  /* 52 */
        II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
        II(d, a, b, c, x[3], S42, 0x8f0ccc92);  /* 54 */
        II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
        II(b, c, d, a, x[1], S44, 0x85845dd1);  /* 56 */
        II(a, b, c, d, x[8], S41, 0x6fa87e4f);  /* 57 */
        II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
        II(c, d, a, b, x[6], S43, 0xa3014314);  /* 59 */
        II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
        II(a, b, c, d, x[4], S41, 0xf7537e82);  /* 61 */
        II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
        II(c, d, a, b, x[2], S43, 0x2ad7d2bb);  /* 63 */
        II(b, c, d, a, x[9], S44, 0xeb86d391);  /* 64 */

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;

        input += MD5_BLOCK_SZ_IN_BT;
    }
}

void md5_init(md5_ctx_t *ctx)
{
    memset(ctx, 0, sizeof(md5_ctx_t));
    // Initialized Buffer
    ctx->state[0] = 0x67452301; // A
    ctx->state[1] = 0xEFCDAB89; // B
    ctx->state[2] = 0x98BADCFE; // C
    ctx->state[3] = 0x10325476; // D
    ctx->num = 0;
    ctx->cnt = 0;
}

void md5_update(md5_ctx_t *ctx, const uint8_t *input, size_t byte_len)
{
    if (ctx->num) // if prev dataflow remain, handle remain bytes in last block
    {
        size_t left_len = MD5_BLOCK_SZ_IN_BT - ctx->num;
        if (byte_len < left_len) // not long enough to gen a full block
        {                        // append updated bytes
            memcpy(ctx->remain + ctx->num, input, byte_len);
            ctx->num += byte_len;
            return;
        }
        // gen a full block
        memcpy(ctx->remain + ctx->num, input, left_len);
        md5_cf(ctx->state, ctx->remain, 1);
        ++ctx->cnt; // num of full blks
        input += left_len;
        byte_len -= left_len;
        // ctx->num = 0; will be reset later
    }

    // num of full block
    size_t blocks = byte_len / MD5_BLOCK_SZ_IN_BT;
    md5_cf(ctx->state, input, blocks);
    ctx->cnt += blocks;
    input += MD5_BLOCK_SZ_IN_BT * blocks;
    byte_len -= MD5_BLOCK_SZ_IN_BT * blocks;

    ctx->num = byte_len;
    // store left_len bytes in current dataflow
    if (byte_len)
        memcpy(ctx->remain, input, byte_len);
}

void md5_finish(md5_ctx_t *ctx, uint8_t *dgst)
{
    // append '10'
    ctx->remain[ctx->num] = 0x80;
    // append '0's
    int zero_bytes = MD5_BLOCK_SZ_IN_BT - ctx->num - 9;
    if (zero_bytes >= 0) // (ctx->num + 1) + 8 <= 64, no new block
    {
        memset(ctx->remain + ctx->num + 1, 0, zero_bytes);
    }
    else // ctx->num + 9 > 64, fill the current block
    {
        memset(ctx->remain + ctx->num + 1, 0, MD5_BLOCK_SZ_IN_BT - ctx->num - 1);
        md5_cf(ctx->state, ctx->remain, 1);
        memset(ctx->remain, 0, MD5_BLOCK_SZ_IN_BT - 8); // new block
    }
    // append '(len)'
    ctx->cnt = (ctx->cnt << 9) + (ctx->num << 3);
    *(uint64_t *)(ctx->remain + 56) = ctx->cnt;
    md5_cf(ctx->state, ctx->remain, 1);

    for (int i = 0; i < 4; i++)
        *(uint32_t *)(dgst + i * 4) = ctx->state[i];
    // free
    memset(ctx, 0, sizeof(md5_ctx_t));
}

void md5_digest(const uint8_t *input, size_t byte_len, uint8_t *dgst)
{
    md5_ctx_t ctx;
    md5_init(&ctx);
    md5_update(&ctx, input, byte_len);
    md5_finish(&ctx, dgst);
}
