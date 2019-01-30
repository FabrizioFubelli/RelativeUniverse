#include <stdio.h>
#include <math.h>

#include "../../utils/util.h"
#include "sets.h"
#include "examples.h"

void test_numbers();
void test_sets();

int main() {
    printf("Hello Sets!\n\n");

    /*
     * N = Natural numbers
     * Z = Integers
     * R = Real numbers
     * E = Even numbers
     * O = Odd numbers
     */

     //test_numbers();
     test_sets();

}


void test_sets() {
    void test_set(Number n) {
        printf("N.belongs(%Lf) = %d\n\n", n, N.belongs(n));
    }

    test_set(get_number(1239489));
    test_set(get_number(242.1234));
    test_set(get_number(-1324412));
    test_set(get_number(-13244.213313589));
    test_set(get_number(1234567891234.01));
}


void test_numbers() {
    short int n = 12345;
    printf("short int n = %hd\n", n);
    printf("get_number = %Lf\n\n", get_number(n));

    int n1 = -1234567890;
    printf("int n = %d\n", n1);
    printf("get_number = %Lf\n\n", get_number(n1));

    long int n2 = 6234567890123456789;
    printf("long int n = %ld\n", n2);
    printf("get_number = %Lf\n\n", get_number(n2));

    long long int n3 = -8234567890123456789;
    printf("long long int n = %lld\n", n3);
    printf("get_number = %Lf\n\n", get_number(n3));

    unsigned short int n4 = 52345;
    printf("unsigned short int n = %u\n", n4);
    printf("get_number = %Lf\n\n", get_number(n4));

    unsigned int n5 = 4234567890;
    printf("unsigned int n = %u\n", n5);
    printf("get_number = %Lf\n\n", get_number(n5));

    unsigned long int n6 = 1234;
    printf("unsigned long int n = %lu\n", n6);
    printf("get_number = %Lf\n\n", get_number(n6));

    unsigned long long int n7 = 9000000000000000000;
    printf("unsigned long long int n = %llu\n", n7);
    printf("get_number = %Lf\n\n", get_number(n7));

    float n8 = 9000000000000000000.21124;
    printf("float n = %f\n", n8);
    printf("get_number = %Lf\n\n", get_number(n8));

    double n9 = 9000000000000000000;
    printf("double n = %f\n", n9);
    printf("get_number = %Lf\n\n", get_number(n9));

    long double n10 = 9000000000000000000;
    printf("long double n = %Lf\n", n10);
    printf("get_number = %Lf\n\n", get_number(n10));
}
