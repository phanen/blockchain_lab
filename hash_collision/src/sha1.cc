#include "../include/sha1.h"
#include "../include/sha1_const.h"

static inline void sha1_cf(uint32_t state[SHA1_STATE_SZ_IN_WD], const uint8_t *input, size_t num_blks)
{
    uint32_t a, b, c, d, e;
    uint32_t w[80];

    while (num_blks--)
    {
        size_t i = 0;
        for (; i < 16; i++)
            w[i] = GETU32((input + i * 4));
        // for (; i < 80; i++)
        //     w[i] = rot_left((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);
        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];
        e = state[4];

        R0(w, a, b, c, d, e, 0);
        R0(w, e, a, b, c, d, 1);
        R0(w, d, e, a, b, c, 2);
        R0(w, c, d, e, a, b, 3);
        R0(w, b, c, d, e, a, 4);
        R0(w, a, b, c, d, e, 5);
        R0(w, e, a, b, c, d, 6);
        R0(w, d, e, a, b, c, 7);
        R0(w, c, d, e, a, b, 8);
        R0(w, b, c, d, e, a, 9);
        R0(w, a, b, c, d, e, 10);
        R0(w, e, a, b, c, d, 11);
        R0(w, d, e, a, b, c, 12);
        R0(w, c, d, e, a, b, 13);
        R0(w, b, c, d, e, a, 14);
        R0(w, a, b, c, d, e, 15);
        R1(w, e, a, b, c, d, 0);
        R1(w, d, e, a, b, c, 1);
        R1(w, c, d, e, a, b, 2);
        R1(w, b, c, d, e, a, 3);
        R2(w, a, b, c, d, e, 4);
        R2(w, e, a, b, c, d, 5);
        R2(w, d, e, a, b, c, 6);
        R2(w, c, d, e, a, b, 7);
        R2(w, b, c, d, e, a, 8);
        R2(w, a, b, c, d, e, 9);
        R2(w, e, a, b, c, d, 10);
        R2(w, d, e, a, b, c, 11);
        R2(w, c, d, e, a, b, 12);
        R2(w, b, c, d, e, a, 13);
        R2(w, a, b, c, d, e, 14);
        R2(w, e, a, b, c, d, 15);
        R2(w, d, e, a, b, c, 0);
        R2(w, c, d, e, a, b, 1);
        R2(w, b, c, d, e, a, 2);
        R2(w, a, b, c, d, e, 3);
        R2(w, e, a, b, c, d, 4);
        R2(w, d, e, a, b, c, 5);
        R2(w, c, d, e, a, b, 6);
        R2(w, b, c, d, e, a, 7);
        R3(w, a, b, c, d, e, 8);
        R3(w, e, a, b, c, d, 9);
        R3(w, d, e, a, b, c, 10);
        R3(w, c, d, e, a, b, 11);
        R3(w, b, c, d, e, a, 12);
        R3(w, a, b, c, d, e, 13);
        R3(w, e, a, b, c, d, 14);
        R3(w, d, e, a, b, c, 15);
        R3(w, c, d, e, a, b, 0);
        R3(w, b, c, d, e, a, 1);
        R3(w, a, b, c, d, e, 2);
        R3(w, e, a, b, c, d, 3);
        R3(w, d, e, a, b, c, 4);
        R3(w, c, d, e, a, b, 5);
        R3(w, b, c, d, e, a, 6);
        R3(w, a, b, c, d, e, 7);
        R3(w, e, a, b, c, d, 8);
        R3(w, d, e, a, b, c, 9);
        R3(w, c, d, e, a, b, 10);
        R3(w, b, c, d, e, a, 11);
        R4(w, a, b, c, d, e, 12);
        R4(w, e, a, b, c, d, 13);
        R4(w, d, e, a, b, c, 14);
        R4(w, c, d, e, a, b, 15);
        R4(w, b, c, d, e, a, 0);
        R4(w, a, b, c, d, e, 1);
        R4(w, e, a, b, c, d, 2);
        R4(w, d, e, a, b, c, 3);
        R4(w, c, d, e, a, b, 4);
        R4(w, b, c, d, e, a, 5);
        R4(w, a, b, c, d, e, 6);
        R4(w, e, a, b, c, d, 7);
        R4(w, d, e, a, b, c, 8);
        R4(w, c, d, e, a, b, 9);
        R4(w, b, c, d, e, a, 10);
        R4(w, a, b, c, d, e, 11);
        R4(w, e, a, b, c, d, 12);
        R4(w, d, e, a, b, c, 13);
        R4(w, c, d, e, a, b, 14);
        R4(w, b, c, d, e, a, 15);

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;

        input += SHA1_BLOCK_SZ_IN_BT;
    }
}

void sha1_init(sha1_ctx_t *ctx)
{
    memset(ctx, 0, sizeof(sha1_ctx_t));
    // Initialized Buffer
    ctx->state[0] = 0x67452301; // A
    ctx->state[1] = 0xEFCDAB89; // B
    ctx->state[2] = 0x98BADCFE; // C
    ctx->state[3] = 0x10325476; // D
    ctx->state[4] = 0xC3D2E1F0; // E
    ctx->num = 0;
    ctx->cnt = 0;
}

void sha1_update(sha1_ctx_t *ctx, const uint8_t *input, size_t byte_len)
{
    if (ctx->num) // if prev dataflow remain, handle remain bytes in last block
    {
        size_t left_len = SHA1_BLOCK_SZ_IN_BT - ctx->num;
        if (byte_len < left_len) // not long enough to gen a full block
        {                        // append updated bytes
            memcpy(ctx->remain + ctx->num, input, byte_len);
            ctx->num += byte_len;
            return;
        }
        // gen a full block
        memcpy(ctx->remain + ctx->num, input, left_len);
        sha1_cf(ctx->state, ctx->remain, 1);
        ++ctx->cnt; // num of full blks
        input += left_len;
        byte_len -= left_len;
        // ctx->num = 0; will be reset later
    }

    // num of full block
    size_t blocks = byte_len / SHA1_BLOCK_SZ_IN_BT;
    sha1_cf(ctx->state, input, blocks);
    ctx->cnt += blocks;
    input += SHA1_BLOCK_SZ_IN_BT * blocks;
    byte_len -= SHA1_BLOCK_SZ_IN_BT * blocks;

    ctx->num = byte_len;
    // store left_len bytes in current dataflow
    if (byte_len)
        memcpy(ctx->remain, input, byte_len);
}

void sha1_finish(sha1_ctx_t *ctx, uint8_t *dgst)
{
    // append '10'
    ctx->remain[ctx->num] = 0x80;
    // append '0's
    int zero_bytes = SHA1_BLOCK_SZ_IN_BT - ctx->num - 9;
    if (zero_bytes >= 0) // (ctx->num + 1) + 8 <= 64, no new block
    {
        memset(ctx->remain + ctx->num + 1, 0, zero_bytes);
    }
    else // ctx->num + 9 > 64, fill the current block
    {
        memset(ctx->remain + ctx->num + 1, 0, SHA1_BLOCK_SZ_IN_BT - ctx->num - 1);
        sha1_cf(ctx->state, ctx->remain, 1);
        memset(ctx->remain, 0, SHA1_BLOCK_SZ_IN_BT - 8); // new block
    }
    // append '(len)'
    ctx->cnt = (ctx->cnt << 9) + (ctx->num << 3);

    PUTU64((ctx->remain + 56), ctx->cnt);
    // *(uint64_t *)(ctx->remain + 56) = ctx->cnt;
    sha1_cf(ctx->state, ctx->remain, 1);

    for (int i = 0; i < 5; i++)
        PUTU32((dgst + i * 4), ctx->state[i]);

    // free
    memset(ctx, 0, sizeof(sha1_ctx_t));
}

void sha1_digest(const uint8_t *input, size_t byte_len, uint8_t *dgst)
{
    sha1_ctx_t ctx;
    sha1_init(&ctx);
    sha1_update(&ctx, input, byte_len);
    sha1_finish(&ctx, dgst);
}
