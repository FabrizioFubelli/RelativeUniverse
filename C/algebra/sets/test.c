#include <stdio.h>
#include <math.h>

#include "../../utils/util.h"
#include "sets.h"
#include "examples.h"

int main() {
    printf("Hello Sets!\n\n");

    /*
     * N = Natural numbers
     * Z = Integers
     * R = Real numbers
     * E = Even numbers
     * O = Odd numbers
     */

     int x = 123456;
     printf("get_number1(%d) = %Lf\n\n", x, get_number1(x));

     //printf("N.belongs2(%Lf) = %d\n", n, N.belongs2(n));

     //n = get_number1(9203000000000000000.31443134);
     //printf("N.belongs2(%Lf) = %d\n", n, N.belongs2(n));
}


void test_numbers() {
    void cast(void *n, Type t) {
        Number new_n = get_number(n, t);
        printf("Converted Number: %Lf\n\n", new_n);
    }

    short int n = 12345;
    printf("short int n = %hd\n", n);
    cast(&n, t_short_int);

    int n1 = -1234567890;
    printf("int n = %d\n", n1);
    cast(&n1, t_int);

    long int n2 = 6234567890123456789;
    printf("long int n = %ld\n", n2);
    cast(&n2, t_long_int);

    long long int n3 = -8234567890123456789;
    printf("long long int n = %lld\n", n3);
    cast(&n3, t_long_long_int);

    unsigned short int n4 = 52345;
    printf("unsigned short int n = %u\n", n4);
    cast(&n4, t_unsigned_short_int);

    unsigned int n5 = 4234567890;
    printf("unsigned int n = %u\n", n5);
    cast(&n5, t_unsigned_int);

    unsigned long int n6 = 1234;
    printf("unsigned long int n = %lu\n", n6);
    cast(&n6, t_unsigned_long_int);

    unsigned long long int n7 = 9000000000000000000;
    printf("unsigned long long int n = %llu\n", n7);
    cast(&n7, t_unsigned_long_long_int);

    float n8 = 9000000000000000000.21124;
    printf("float n = %f\n", n8);
    cast(&n8, t_float);

    double n9 = 9000000000000000000;
    printf("double n = %f\n", n9);
    cast(&n9, t_double);

    long double n10 = 9000000000000000000;
    printf("long double n = %Lf\n", n10);
    cast(&n10, t_long_double);
}
