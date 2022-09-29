#include <stdint.h>
#include <iostream>
#include <string.h>

#include "base64.h"
#include "util.h"

using namespace std;

int init_inv_tab()
{
    memset(inv_tab, 0, sizeof(inv_tab));
    for (size_t i = 0; i < 64; i++)
        inv_tab[tab[i]] = i;
}

// 1 1 1 1 1 1 1 1 |  1 1 1 1 1 1 1 1 | 1 1 1 1 1 1 1 1
// s s s s s s d d |  d d d d s s s s | s s d d d d d d

// convert base64 to binary string
int base64_decode(const uint8_t *input, size_t len, uint8_t *output, size_t &olen)
{ // len: length of string

    uint8_t l, m1, m2, r;
    olen = 0;

    // absorb three bytes each time
    if (len == 0)
        return 1;

    size_t len1 = len - 4;
    size_t i = 0;
    for (; i < len1; i += 4)
    {
        l = inv_tab[input[i]];
        m1 = inv_tab[input[i + 1]];
        m2 = inv_tab[input[i + 2]];
        r = inv_tab[input[i + 3]];

        *(output++) = (l << 2) | ((m1 >> 4) & 0x03);
        *(output++) = (m1 << 4) | ((m2 >> 2) & 0x0f);
        *(output++) = (m2 << 6) | (r);
        olen += 3;
    }
    // cout << "hit" << endl;

    // Last four..
    if (input[len - 2] == '=')
    { // 8 <-> 12(2)
        l = inv_tab[input[i]];
        r = inv_tab[input[i + 1]];
        *(output++) = (l << 2) | ((r >> 4) & 0x03);
        ++olen;
        return 1;
    }

    if (input[len - 1] == '=')
    {
        // 16 <-> 18(3)
        l = inv_tab[input[i]];
        m1 = inv_tab[input[i + 1]];
        r = inv_tab[input[i + 2]];
        *(output++) = (l << 2) | ((m1 >> 4) & 0x03);
        *(output++) = ((m1 << 4) | (r >> 2) & 0x0f);
        olen += 2;
        return 1;
    }
    l = inv_tab[input[i]];
    m1 = inv_tab[input[i + 1]];
    m2 = inv_tab[input[i + 2]];
    r = inv_tab[input[i + 3]];
    *(output++) = (l << 2) | ((m1 >> 4) & 0x03);
    *(output++) = (m1 << 4) | ((m2 >> 2) & 0x0f);
    *(output++) = (m2 << 6) | (r);
    olen += 3;
    return 1;
}

int main()
{
    // init_inv_tab();
    // print_array(inv_tab, sizeof(inv_tab));
    uint8_t buf[1024];
    size_t olen = 0;
    memset(buf, 0, sizeof(buf));

    base64_decode((uint8_t *)str1, strlen(str1), buf, olen);
    dump_buf(buf, olen);

    base64_decode((uint8_t *)str2, strlen(str2), buf, olen);
    dump_buf(buf, olen);
}
