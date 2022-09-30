#pragma once

#include <stdint.h>
#include <iostream>
#include <string.h>

// STATE always process in word
#define SHA1_DIGST_SZ_IN_BT 20 //
#define SHA1_STATE_SZ_IN_WD 5  //  5w 20B 160b
#define SHA1_BLOCK_SZ_IN_BT 64 // 16w 64B 512b

typedef struct sha1_ctx_t
{
    // counter of message bit length
    uint64_t cnt;
    // num of remain bytes in remain incomplete block
    size_t num;
    // middle state of iteration
    uint32_t state[SHA1_STATE_SZ_IN_WD];
    // store remain incomplete block in a flow
    uint8_t remain[SHA1_BLOCK_SZ_IN_BT];
} sha1_ctx_t;

/**
 * @brief initialize the context
 * @param ctx
 */
void sha1_init(sha1_ctx_t *ctx);

/**
 * @brief update middle state
 *        compress a continuous dataflow
 * @param ctx
 * @param input cont inuous dataflow in address
 * @param byte_len byte length of input
 */
void sha1_update(sha1_ctx_t *ctx, const uint8_t *input, size_t byte_len);

/**
 * @brief finish the last block and write final output
 *       (pad, then compress)
 * @param ctx
 * @param dgst return final digest
 */
void sha1_finish(sha1_ctx_t *ctx, uint8_t *dgst);

/**
 * @brief simple hash (single short message)
 *        invoke other func
 * @param input
 * @param byte_len
 * @param dgst return
 */
void sha1_digest(const uint8_t *input, size_t byte_len, uint8_t *dgst);

// 64-element table T[1 ... 64] constructed from the
// sine function. Let T[i] denote the i-th element of the table, which
// is equal to the integer part of 4294967296 times abs(sin(i)), where i
// is in radians.
