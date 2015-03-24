/* $begin show-bytes */
#include <stdio.h>
/* $end show-bytes */
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <limits.h>
/* $begin show-bytes */

using namespace std;

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
    int i;
    //TODO Flip around to show endianness correctly
    for (i = len; i > 0; i--)
        printf(" %.2x", start[i - 1]);    //line:data:show_bytes_printf
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int)); //line:data:show_bytes_amp1
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float)); //line:data:show_bytes_amp2
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *)); //line:data:show_bytes_amp3
}
/* $end show-bytes */


/* $begin test-show-bytes */
void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}
/* $end test-show-bytes */

void simple_show_a() {
/* $begin simple-show-a */
    int val = 0x87654321;
    byte_pointer valp = (byte_pointer) &val;
    show_bytes(valp, 1); /* A. */
    show_bytes(valp, 2); /* B. */
    show_bytes(valp, 3); /* C. */
/* $end simple-show-a */
}

void simple_show_b() {
/* $begin simple-show-b */
    int val = 0x12345678;
    byte_pointer valp = (byte_pointer) &val;
    show_bytes(valp, 1); /* A. */
    show_bytes(valp, 2); /* B. */
    show_bytes(valp, 3); /* C. */
/* $end simple-show-b */
}

void float_eg() {
    int x = 3490593;
    float f = (float) x;
    printf("For x = %d\n", x);
    show_int(x);
    show_float(f);

    x = 3510593;
    f = (float) x;
    printf("For x = %d\n", x);
    show_int(x);
    show_float(f);

}

void string_ueg() {
/* $begin show-ustring */
    const char *s = "ABCDEF";
    show_bytes((byte_pointer) s, strlen(s));
/* $end show-ustring */
}

void string_leg() {
/* $begin show-lstring */
    const char *s = "abcdef";
    show_bytes((byte_pointer) s, strlen(s));
/* $end show-lstring */
}

void show_twocomp()
{
/* $begin show-twocomp */
    short x = 12345;
    short mx = -x;

    show_bytes((byte_pointer) &x, sizeof(short));
    show_bytes((byte_pointer) &mx, sizeof(short));
/* $end show-twocomp */
}

void show_short()
{
    short int x = 0x12345;

    show_bytes((byte_pointer)&x, sizeof(short int));
}

void show_long()
{
    long int x = 12345;

    show_bytes((byte_pointer)&x, sizeof(long int));
}

void show_double()
{
    double x = 0x123456789ABCDEFFF;

    show_bytes((byte_pointer)&x, sizeof(double));
}

int is_little_endian()
{
    int x = 0x1234;
    byte_pointer test = (byte_pointer)&x;
    if(test[0] == 0x34)
        return 1;

    return 0;
}

void yield_word()
{
    int x = 0x89ABCDEF;
    int y = 0x76543210;

    int test = (x & (0xff)) | (y & ~0xff);
    printf("\n Bytes of word are: ");
    show_bytes((byte_pointer)&test, sizeof(int));
}

unsigned replace_byte(unsigned x, int i, unsigned char h)
{
    unsigned char *p = (unsigned char *)&x;
    *(p+i) = h;
    return x;
}

int evaluate_intEqualsOne(int x)
{
    return !!x;
}

int evaluate_intEqualsZero(int x)
{
    return !!~x;
}

int evaluate_leastSignificantBitEqualsOne(int x)
{
    return !!(x & 0xFF);
}

int evaluate_MostSignificatnetBitEqualsZero(int x)
{
    return !!(~x &(0xFF >> ((sizeof(int) - 1) >> 3)));
}

int int_shifts_are_arithmetic()
{
    int n = -1;
    n >>= (sizeof(int) - 1);
    return (n < 0);
}

void printBits(int value)
{   unsigned int mask = 1 << 31;
    int i;
    printf("'n%12d = ", value);
    for (i = 31; i >= 0; --i) {
        printf("%c", value & mask ? '1': '0');
        mask >>= 1;
    }
}

unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int) x >> k;
    return xsra < INT_MIN ? xsra : xsra & ~(-1 << ((8 * sizeof(int)) - k));
}

int sra(int x, int k)
{
    int xsrl = (unsigned) x >> k;
    return x < 0 ? xsrl | (-1 << ((8 * sizeof(int)) - k)) : xsrl;
}

int any_odd_one(unsigned x)
{
    return (x && 0x55555555) && 1;
}

int odd_ones(unsigned x)
{
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x &= 1;
    return x;
}

int leftmost_one(unsigned x)
{
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return  (x >> 1) + 1;
}

int int_size_is_32()
{
    // A. Shift size must be smaller than int bit size
    // 32 bit machine
    // Incorrect returns true for 64 bit machine
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;
    // int is at least 16 bits
    /*int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;*/
    return set_msb && !beyond_msb;
}

int lower_one_mask(int n)
{
    int n0 = n - 1;
    int mask = ((~(-1 << n0) << 1)) + 0x1;
//rotate mask n times. this fills in the lower bits with 0's
//    std::cout << "Lower One Mask value: " << n << ", bit mask: ";
//    show_bytes((byte_pointer) &n, sizeof(int));
    show_bytes((byte_pointer) &mask, sizeof(int));
    return mask;
}

unsigned rotate_left(unsigned x, int n)
{
    //TODO Ask about
    int w = sizeof(int) << 3;

    std::cout << "before left rotate: ";
    show_bytes((byte_pointer)&x, sizeof(int));
    return ((x >> (w - n - 1) >> 1)) | (x << n);
}

int fit_bits(int x, int n)
{
    int sign = x >> ((sizeof(int) << 3) - 1);
    int mask = (sign >> (n - 1)) << (n - 1);
    int maskNum = ~(-1 << (n - 1));
    int newNum = mask  + (x & maskNum);
    return newNum == x;
}

typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum)
{
    // TODO Ask why fails with negative number
    //return (word >> (bytenum << 3)) & 0xFF;
    return (word << (24 - (bytenum << 3))) >> (bytenum << 3);
}

void copy_int(int val, void *buf, int maxbytes)
{
    // How it was written in the box size_t is unsigned
    if(~(sizeof(val)) >= ~maxbytes)
        memcpy(buf, (void *) &val, sizeof(val));
}

int saturating_add(int x, int y)
{
    int w = sizeof(int) << 3;
    int l_mask = 0x0000FFFF;
    int m_mask = ~(l_mask << (w - 16));

    int lx = l_mask & x;
    int ly = l_mask & y;
    int lz = (lx + ly) >> 16;

    int sign_equal = ((x >> (w - 1)) == (y >> (w - 1))) << (w - 1) >> (w - 1);

    int mx = (x >> 16) & m_mask;
    int my = (y >> 16) & m_mask;
    int mz = mx + my + lz;
    int two_sign = mz >> (w - 16 - 1);
    int first_sign = two_sign & 0x1;
    int second_sign = two_sign >> 1;
    int overflow = ~((first_sign ^ second_sign) - 1);
    int min = 0x1 << (w - 1);
    int max = ~min;

    return (sign_equal & overflow & (-first_sign) & max) + (sign_equal & overflow & (~(-first_sign)) & min) +
            (sign_equal & (~overflow) & (x + y)) + (~sign_equal & (x + y));
}

// TODO Ask about
int tsub_ok(int x, int y)
{
    int w = sizeof(int) << 3;

    int l_mask = 0x0000FFFF;
    int m_mask = ~(l_mask << (w - 16));
    y = -y;
    int lx = l_mask & x;
    int ly = l_mask & y;
    int lz = (lx + ly) >> 16;

    int mx = (x >> 16) & m_mask;
    int my = (y >> 16) & m_mask;
    int mz = mx + my + lz;
    int two_sign = mz >> (w - 16 - 1);
    int first_sign = two_sign & 0x1;
    int second_sign = two_sign >> 1;
    return (first_sign ^ second_sign);
}

//TODO ask about
unsigned int unsigned_high_prod(unsigned x, unsigned y)
{
    unsigned w = sizeof(int) << 3;
    unsigned wd2 = w >> 1;
    unsigned minus1 = -1;
    unsigned mask0 = minus1 >> wd2;
    unsigned mask1 = ~(mask0);

    unsigned x0 = mask0 & x;
    unsigned x1 = mask1 & x;
    unsigned y0 = mask0 & y;
    unsigned y1 = mask1 & y;

    unsigned result = ((x0 * (y1 >> wd2)) >> wd2) + ((y0 * (x1 >> wd2)) >> wd2) +
            ((x1 >> wd2) * (y1 >> wd2));

    unsigned l0 = ((x & mask0) * (y & mask0));
    unsigned l1 = (x & mask0) * (y & mask1);
    unsigned l2 = ((x & mask1) * (y & mask0));
    //printf("%x %x %x\n", l0, l1, l2);
    unsigned p = ((((l0 & mask0) + (l1 & mask0) + (l2 & mask0)) >> wd2) + (l0 >> wd2) + (l1 >> wd2) + (l2 >> wd2)) >> wd2;
    return result + p;
}

void multiply_by_const(int x)
{
    int k17 = (x << 4) + x;
    std::cout << k17 << endl;

    int k7 = -(x << 3) + x;
    std::cout << k7 << endl;

    int k60 = (x << 6) - (x << 2);
    std::cout << k60 << endl;

    int k112 = -(x << 7) + (x << 4);
    std::cout << k112 << endl;
}

int divide_power2(int x, int k)
{
    return x >> k;
}

int mul3div4(int x)
{
    int x0 = x >> 2;
    int x1 = x - (x0 << 2);
    return x0 + (x0 << 1) + ((x1 +(x1 << 1)) >> 2);
}

int threefourths(int x)
{
    int x0 = x >> 2;
    int x1 = x - (x0 << 2);

    int mod4 =  (0x00000003 & x) == 0;
    int negative = (0x80000000 & x) != 0;
    return x0 + (x0 << 1) + ((x1 + (x1 << 1)) >> 2) + negative * (!mod4);
}

int generateBitPattern_a(int k)
{
    return -1 << k;
}

int generateBitPattern_b(int j, int k)
{
    return 0x7FFFFFFF >> ((sizeof(int) << 3) - 1 - k) << j;
}

int main(int argc, char *argv[])
{

    int val = 12345;

    if (argc > 1) {
        if (argc > 1) {
            val = strtol(argv[1], NULL, 0);
        }
        printf("calling test_show_bytes\n");
        test_show_bytes(val);
    } else {
        printf("calling show_twocomp\n");
        show_twocomp();
        printf("Calling simple_show_a\n");
        simple_show_a();
        printf("Calling simple_show_b\n");
        simple_show_b();
        printf("Calling float_eg\n");
        float_eg();
        printf("Calling string_ueg\n");
        string_ueg();
        printf("Calling string_leg\n");
        string_leg();
        printf("Calling show_short\n");
        show_short();
        printf("calling show_long\n");
        show_long();
        printf("Calling show_double\n");
        show_double();
        if(is_little_endian())
            printf("A Little Endian Machine");
        else
            printf("Big Endian Machine");
        yield_word();
        unsigned test = replace_byte(0x12345678, 2, 0xAB); // 0x12AB5678
        test = replace_byte(0x12345678, 3, 0xCF);
        show_bytes((byte_pointer)&test, sizeof(unsigned));
        std::cout << evaluate_intEqualsOne(14) << std::endl;
        std::cout << evaluate_intEqualsZero(254) << std::endl;
        std::cout << evaluate_leastSignificantBitEqualsOne(1) << std::endl;
        std::cout << evaluate_MostSignificatnetBitEqualsZero(255) << std::endl;
        std::cout << int_shifts_are_arithmetic();

        std::cout << srl(125, 6) << std::endl;
        std::cout << sra(-125, 6) << std::endl;

        std::cout << any_odd_one(42) << std::endl;
        std::cout << any_odd_one(21) << std::endl;
        std::cout << any_odd_one(0) << std::endl;

        std::cout << odd_ones(1) << std::endl;
        std::cout << odd_ones(2) << std::endl;
        std::cout << odd_ones(15) << std::endl;

        std::cout << leftmost_one(1) << std::endl;
        std::cout << leftmost_one(0) << std::endl;
        std::cout << leftmost_one(125) << std::endl;
        std::cout << leftmost_one(8) << std::endl;

        std::cout << int_size_is_32() << std::endl;

        std::cout << lower_one_mask(6) << std::endl;
        std::cout << lower_one_mask(17) << std::endl;

        unsigned testByte = rotate_left(0x123456781, 4);
        show_bytes((byte_pointer)&testByte, sizeof(unsigned));
        testByte = rotate_left(0x123456781, 20);
        show_bytes((byte_pointer)&testByte, sizeof(unsigned));

        printf("%d\n", fit_bits(0x000000FF, 9));
        printf("%d\n", fit_bits(0x7FFFFFFF, 63));
        printf("%d\n",fit_bits(0x80000000,64));
        printf("%d\n",fit_bits(0xFFFFFF00,9));
        std::cout << 0x12345678u << endl;
        int xbyteValue = xbyte(0x12345678u, 2);
        std::cout << xbyteValue << endl;
        show_bytes((byte_pointer) &xbyteValue, sizeof(int));
        xbyteValue = xbyte(0x89ABCDEFu,2);
        show_bytes((byte_pointer) &xbyteValue, sizeof(int));

        int buf = 0;
        copy_int(0xFFFFFFFF, (void*) &buf, 3);

        std::cout << saturating_add(0x7FFFFFF0,0x000000FF) << endl;
        std::cout << saturating_add(0x80000000,0xFFFFFFF0) << endl;
        std::cout << saturating_add(20000000, 1) << endl;
        std::cout << saturating_add(-1, 1) << endl;

        std::cout << tsub_ok(0x7FFFFFFF, -1) << endl;
        std::cout << tsub_ok(1, 0x80000000) << endl;
        std::cout << tsub_ok(-100,  2 * 2147483647) << endl;

        std::cout << unsigned_high_prod(0xFFFFFFFFu,0xFFFFFFFFu) << endl;
        std::cout << unsigned_high_prod(0x00000021u,0x00000002u) << endl;

        multiply_by_const(5);

        std::cout << divide_power2(-31, 4) << endl;
        std::cout << divide_power2(64, 5) << endl;

        std::cout << mul3div4(8) << endl;

        std::cout << threefourths(100) << endl;

        std::cout << generateBitPattern_a(20) << endl;
        std::cout << generateBitPattern_b(1, 20) << endl;


        // 81. A. x = 0 y = -2147483648 causes A to equal 0
        // 81. B. always 1;
        // 81. C. Always 1
        // 81. D. x = 2147483647; y = -2147483648; causes C to equal 0
        // 81. E. Always 1

    }

    return 0;
}

//2.55 Home computer is little endian
