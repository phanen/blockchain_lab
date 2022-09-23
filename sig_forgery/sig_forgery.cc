// #include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sig_forgery.h"
#include <gmp.h>

// encode string to mpz  (ascii)
void encode(mpz_t rop, const char *msg)
{
    char buf[1024];
    char hex_tab[17] = "0123456789abcdef";
    uint8_t cur;
    char *p = buf;

    while (cur = *msg)
    {
        *p = hex_tab[(cur >> 4) & 0x0f];
        ++p;
        *p = hex_tab[cur & 0x0f];
        ++p;
        ++msg;
    }
    *p = '\0';
    mpz_set_str(rop, buf, 16);
}

// success return 1
int rsa_verify(const mpz_t e, const mpz_t n, const mpz_t m, const mpz_t sig)
{
    mpz_t res;
    mpz_init(res);
    mpz_powm(res, sig, e, n);
    return !mpz_cmp(res, m);
}

int main()
{
    const char *msg = "Alice owes Bob $500.";
    mpz_t m, sig, m1, tmp, n1, e1;
    mpz_inits(m, sig, m1, tmp, n1, e1, NULL);
    mpz_set_str(n1, N, 10);
    mpz_set_str(e1, e, 10);

    encode(m, msg);
    mpz_set(m1, m); // copy
    gmp_printf("Alice's message(encoded): 0x%Zx\n\n", m);

    // factorization of m with a factor base, collecting index
    unsigned index_lst[10];
    memset(index_lst, 0, 10 * sizeof(unsigned));

    for (size_t i = 0; i < 10; ++i)
    {
        mpz_set_str(tmp, msg_lst[i], 10);
        while (mpz_divisible_p(m, tmp))
        {
            mpz_divexact(m, m, tmp);
            ++index_lst[i];
        }
    }
    if (!mpz_cmp_ui(m, 1))
    {
        gmp_printf("Factorization finish!\n");
        gmp_printf("List of factor's index: ");
        for (size_t i = 0; i < 10; ++i)
            gmp_printf("%d ", index_lst[i]);
        gmp_printf("\n\n");
    }

    // Forgery of signature
    mpz_set_ui(sig, 1);
    for (size_t i = 0; i < 10; ++i)
    {
        while (index_lst[i]--)
        {
            mpz_set_str(tmp, sig_lst[i], 10);
            mpz_mul(sig, sig, tmp);
            mpz_mod(sig, sig, n1);
        }
    }
    // Verify
    if (rsa_verify(e1, n1, m1, sig))
    {
        gmp_printf("Success!\n");
        gmp_printf("The forgery signature is %Zx\n", sig);
    }
}