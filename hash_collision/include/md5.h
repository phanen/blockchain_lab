#pragma once

#include <stdint.h>
#include <iostream>
#include <string.h>

// STATE always process in word
#define MD5_DIGST_SZ_IN_BT 16
#define MD5_STATE_SZ_IN_WD 4  //  4w 16B 128b
#define MD5_BLOCK_SZ_IN_BT 64 // 16w 64B 512b

typedef struct md5_ctx_t
{
    // counter of message bit length
    uint64_t cnt;
    // num of remain bytes in remain incomplete block
    size_t num;
    // middle state of iteration
    uint32_t state[MD5_STATE_SZ_IN_WD];
    // store remain incomplete block in a flow
    uint8_t remain[MD5_BLOCK_SZ_IN_BT];
} md5_ctx_t;

/**
 * @brief initialize the context
 * @param ctx
 */
void md5_init(md5_ctx_t *ctx);

/**
 * @brief update middle state
 *        compress a continuous dataflow
 * @param ctx
 * @param input cont inuous dataflow in address
 * @param byte_len byte length of input
 */
void md5_update(md5_ctx_t *ctx, const uint8_t *input, size_t byte_len);

/**
 * @brief finish the last block and write final output
 *       (pad, then compress)
 * @param ctx
 * @param dgst return final digest
 */
void md5_finish(md5_ctx_t *ctx, uint8_t *dgst);

/**
 * @brief simple hash (single short message)
 *        invoke other func
 * @param input
 * @param byte_len
 * @param dgst return
 */
void md5_digest(const uint8_t *input, size_t byte_len, uint8_t *dgst);

// 64-element table T[1 ... 64] constructed from the
// sine function. Let T[i] denote the i-th element of the table, which
// is equal to the integer part of 4294967296 times abs(sin(i)), where i
// is in radians.
