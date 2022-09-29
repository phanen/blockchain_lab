#include <stdint.h>
#include <iostream>

template <class T>
int print_array(T *arr, std::size_t sz)
{
    for (std::size_t i = 0; i < sz; i++)
    {
        if (i % 8 == 0)
            std::cout << std::endl;
        std::cout << int(arr[i]) << ", ";
    }
    std::cout << std::endl;
    return 1;
}

inline void dump_buf(uint8_t *buf, std::size_t len, uint8_t sep = ' ')
{
    for (std::size_t i = 0; i < len; i++)
    {
        printf("0x%.2x%c", buf[i], sep);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");
}

const char *str1 = "0THdAsXm7sRpPZoGmK/5XC/KtYcSRn6rQARYPrj7f4lVrTQGCfSzAoPkiIMlcUFaCFEl6PfNyZ/ZHb3ygDc8W5YLHdHcQXuc5NiX9FplVdU1c5rH8Ov9DDAp8WbRCbGPdSd/eTDVXOsi6K26ecwVXO10y91fxdNtsZsK2DXMp+M=";
const char *str2 = "0THdAsXm7sRpPZoGmK/5XC/KtQcSRn6rQARYPrj7f4lVrTQGCfSzAoPkiIMl8UFaCFEl6PfNyZ/ZHb1ygDc8W5YLHdHcQXuc5NiX9FplVdU1c5pH8Ov9DDAp8WbRCbGPdSd/eTDVXOsi6K26eUwVXO10y91fxdNtsZsKWDXMp+M=";

uint8_t tab[64]{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/' //
};

uint8_t inv_tab[128]{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 62, 0, 0, 0, 63,
    52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 0, 0, 0, 0, 0,
    0, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 0, 0, 0, 0, 0, //
};