#include <stdint.h>
#include <iostream>
#include <string.h>

#include <sys/time.h>

#include "sha1.h"
#include "md5.h"
#include "base64.h"
#include "util.h"

using namespace std;

const char *str1 = "0THdAsXm7sRpPZoGmK/5XC/KtYcSRn6rQARYPrj7f4lVrTQGCfSzAoPkiIMlcUFaCFEl6PfNyZ/ZHb3ygDc8W5YLHdHcQXuc5NiX9FplVdU1c5rH8Ov9DDAp8WbRCbGPdSd/eTDVXOsi6K26ecwVXO10y91fxdNtsZsK2DXMp+M=";
const char *str2 = "0THdAsXm7sRpPZoGmK/5XC/KtQcSRn6rQARYPrj7f4lVrTQGCfSzAoPkiIMl8UFaCFEl6PfNyZ/ZHb1ygDc8W5YLHdHcQXuc5NiX9FplVdU1c5pH8Ov9DDAp8WbRCbGPdSd/eTDVXOsi6K26eUwVXO10y91fxdNtsZsKWDXMp+M=";

int main()
{
    uint8_t buf1[1024], buf2[1024];
    size_t olen1, olen2;

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));

    base64_decode((uint8_t *)str1, strlen(str1), buf1, olen1);
    base64_decode((uint8_t *)str2, strlen(str2), buf2, olen2);

    cout << "hex of str1 (" << olen1 << ")" << endl;
    dump_buf(buf1, olen1);
    cout << "hex of str2 (" << olen2 << ")" << endl;
    dump_buf(buf2, olen2);

    // write decoded to file
    FILE *fp1 = fopen("./file1", "wb");
    fwrite(buf1, 1, olen1, fp1);
    FILE *fp2 = fopen("./file2", "wb");
    fwrite(buf2, 1, olen2, fp2);
    fclose(fp1);
    fclose(fp2);

    // hash of decoded string
    md5_digest((const uint8_t *)buf1, olen1, buf1);
    md5_digest((const uint8_t *)buf2, olen2, buf2);
    cout << "hash of str1: " << endl;
    dump_buf(buf1, MD5_DIGST_SZ_IN_BT);
    cout << "hash of str1: " << endl;
    dump_buf(buf2, MD5_DIGST_SZ_IN_BT);
    cout << (memcmp(buf1, buf2, MD5_DIGST_SZ_IN_BT) ? "different" : "same") << endl;

    // hash .pdf file
    test_large_file("/mnt/c/Users/lenovo/Desktop/shattered-1.pdf");
    test_large_file("/mnt/c/Users/lenovo/Desktop/shattered-2.pdf");

    test_large_file_sha("/mnt/c/Users/lenovo/Desktop/shattered-1.pdf");
    test_large_file_sha("/mnt/c/Users/lenovo/Desktop/shattered-2.pdf");
}

//////////////////////////////////// bug
// auto buf0 = "3451234512345123451234512345123451234512345123450123456789abcdef3451234512345123451234512345123451234512345123450123456789abcdef";
// auto bufx = "3451234512345123451234512345123451234512345123450123456789abcdefawuhawufehawefawef;;;;;iohgao;wrghawro;ghawrgohawrgrghiworghriog";
// auto buf0 = "12345678901234567890123456789012345678901234567890123456789012341234567890123456789012345678901234567890123456789012345678901234";
// auto bufx = "12345678901234567890123456789012345678901234567890123456789012341111111111111111111111111111111111111111111111111111111111111111";
// md5_digest((const uint8_t *)buf0, strlen(buf0), buf3);
// md5_digest((const uint8_t *)bufx, strlen(bufx), buf4);

// for (size_t i = 0; i < olen1; i++)
// {
//     printf("%.2x", buf1[i]);
// }
// cout << endl;
// for (size_t i = 0; i < olen2; i++)
// {
//     printf("%.2x", buf2[i]);
// }
// cout << endl;
