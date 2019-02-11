/*
 * TESTER
*/

#include <stdio.h>
#include <math.h>

#include "utils/util.h"
#include "utils/log.h"
#include "utils/number.h"

#include "algebra/sets/sets.h"

void test_numbers();
void test_sets();
void test_files();
void test_utils();

int main() {
    /*
     * N = Natural numbers
     * Z = Integers
     * R = Real numbers
     * P = Even numbers
     * D = Odd numbers
     */

     //test_numbers();
     test_sets();
     //test_files();
     //test_utils();
     return 0;
}

void test_utils() {
    char *curr_dir = pwd();
    printf("pwd() = %s\n", pwd());
    free(curr_dir);
}

void test_files() {
    printf("Log file: %s\n", LOG_FILE);
    Log.info("Hello files!");
    Log.error("This is an error");
    Log.done("All done!");
}

void test_sets() {
    #define SETS 8
    #define NUMBERS 5

    printf("SETS = %hu\n", SETS);
    const Set *sets[SETS] = {&U, &R, &Z, &N, &P, &D, &Z_, &E};

    printf("NUMBERS = %hu\n", NUMBERS);
    const Number numbers[NUMBERS] = {
        1234, 123.9087, -190, -43.322, 2148089043243
    };

    void check_numbers(const Set *set) {
        for (unsigned short k=0; k<NUMBERS; k++) {
            Number n = numbers[k];
            printf("%s.belongs(%Lf) = %d\n\n", set->symbol, n, set->belongs(set, n));
        }
    }

    const Set *sets_union_check;

    for (unsigned short i=0; i<SETS; i++) {
        const Set *set = sets[i];
        printf("\n\nTESTING \"%s\" SET\n\n", set->symbol);
        print_set(set, 0);
        printf("\n\n");
        check_numbers(set);
        printf("\n");
        for (unsigned short j=0; j<SETS; j++) {
            const Set *set2 = sets[j];
            printf("%s ⊆ %s = %d\n\n", set->symbol, set2->symbol, is_subset(set, set2));
            printf("%s ⊂ %s = %d\n", set->symbol, set2->symbol, is_proper_subset(set, set2));
            printf("\n");
            const Set *sets_union = set_union(set, set2);
            //print_set(sets_union, 0);
            if (i==4 && j == 2) {
                sets_union_check = sets_union;
            }
            check_numbers(sets_union);
            printf("\n");
        }

        printf("\n\n");
    }
    printf("sets_union_check->symbol = %s\n", sets_union_check->symbol);
    print_set(sets_union_check, 0);
    check_numbers(sets_union_check);
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
