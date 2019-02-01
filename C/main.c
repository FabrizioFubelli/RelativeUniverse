/*
 * TESTER
*/

#include <stdio.h>
#include <math.h>

#include "utils/log.h"
#include "utils/number.h"

#include "algebra/sets/sets.h"

//#include "examples.h"

void test_numbers();
void test_sets();
void test_files();

int main() {
    /*
     * N = Natural numbers
     * Z = Integers
     * R = Real numbers
     * E = Even numbers
     * O = Odd numbers
     */

     //test_numbers();
     //test_sets();
     test_files();
}

void test_files() {
    Log.info("Hello files!");
    Log.error("This is an error");
    Log.done("All done!");
}

void test_sets() {
    #define SETS 5
    #define NUMBERS 5

    printf("SETS = %hd\n", SETS);
    //const char sets[SETS] = {'N', 'Z', 'P', 'D', 'E', 'R'};
    const char sets[SETS] = {'U', 'R', 'Z', 'N', 'E'};

    printf("NUMBERS = %hd\n", NUMBERS);
    const Number numbers[NUMBERS] = {
        1234, 123.9087, -190, -43.322, 2148089043243
    };

    for (unsigned short i=0; i<SETS; i++) {
        printf("\n\nTESTING \"%c\" SET\n\n", sets[i]);
        const Set *set;
        if (sets[i] == 'U') {
            set = &U;
        } else if (sets[i] == 'R') {
            set = &R;
        } else if (sets[i] == 'Z') {
            set = &Z;
        } else if (sets[i] == 'N') {
            set = &N;
        } else if (sets[i] == 'E') {
            set = &E;
        } else {
            printf("SET %c NOT VALID!\n", sets[i]);
            continue;
        }
        print_set(set, 0);
        printf("\n\n");
        for (unsigned short k=0; k<NUMBERS; k++) {
            Number n = numbers[k];
            printf("%c.belongs(%Lf) = %d\n\n", sets[i], n, set->belongs(n));
        }
    }
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
