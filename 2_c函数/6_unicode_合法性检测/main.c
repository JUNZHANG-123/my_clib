#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

static void *
utf8_decode(void *buf, unsigned int *c, int *e)
{
    static const char lengths[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0
    };
    static const int masks[]  = {0x00, 0x7f, 0x1f, 0x0f, 0x07};
    static const unsigned int mins[] = {4194304, 0, 128, 2048, 65536};
    static const int shiftc[] = {0, 18, 12, 6, 0};
    static const int shifte[] = {0, 6, 4, 2, 0};

    unsigned char *s = buf;
    int len = lengths[s[0] >> 3];

    /* Compute the pointer to the next character early so that the next
     * iteration can start working on the next character. Neither Clang
     * nor GCC figure out this reordering on their own.
     */
    unsigned char *next = s + len + !len;

    /* Assume a four-byte character and load four bytes. Unused bits are
     * shifted out.
     */
    *c  = (unsigned int)(s[0] & masks[len]) << 18;
    *c |= (unsigned int)(s[1] & 0x3f) << 12;
    *c |= (unsigned int)(s[2] & 0x3f) <<  6;
    *c |= (unsigned int)(s[3] & 0x3f) <<  0;
    *c >>= shiftc[len];

    /* Accumulate the various error conditions. */
    *e  = (*c < mins[len]) << 6; // non-canonical encoding
    *e |= ((*c >> 11) == 0x1b) << 7;  // surrogate half?
    *e |= (*c > 0x10FFFF) << 8;  // out of range?
    *e |= (s[1] & 0xc0) >> 2;
    *e |= (s[2] & 0xc0) >> 4;
    *e |= (s[3]       ) >> 6;
    *e ^= 0x2a; // top two bits of each tail byte correct?
    *e >>= shifte[len];

    return next;
}

static bool utf8_decode_ok(unsigned char *buf) {
    unsigned char *next = buf;
    unsigned int c;
    int e;
    
    while(*next != 0) {
        next = utf8_decode(next, &c, &e);
        if(e != 0) {
			return false;
        }
    }
	
	return true;
}

int main(void)
{
	//unsigned char  buf[] = {0xe8,0xc9,0xb7,0xe3,0xd6,0xb1,0xb2,0xa5,0xd7,0xa8,0xd3,0xc3}; //无效数据
	unsigned char  buf[] = {0x34,0x32,0x2c,0x22,0x66,0x6c,0x61,0x67}; //有效数据
	
	printf("string is valid=%d\n", utf8_decode_ok(buf));
	
	return 0;
}
