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
void test_sets_2();
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
     //test_sets();
     test_sets_2();
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

void check_numbers(const Set *set) {
    #define NUMBERS 6
    const Number numbers[NUMBERS] = {
        1234, 123.9087, -190, -43.322, 2148089043243, -191
    };
    for (unsigned short k=0; k<NUMBERS; k++) {
        Number n = numbers[k];
        printf("%s.belongs(%Lf) = %d\n\n", set->symbol, n, set->belongs(set, n));
    }
    printf("\n");
}

void test_sets_2() {
    printf("\n#---- test_sets_2\n\n");
    const Set *set_A = &P;
    const Set *set_B = &D;
    const Set *set_C = &Z_;
    const Set *set_D = &Z;
    const Set *set_E = &N;
    const Set *set_F = &E;
    const Set *A_union_B = set_union(set_A, set_B);
    const Set *A_intersection_B = set_intersection(set_A, set_B);
    const Set *A_difference_B = set_difference(set_A, set_B);
    const Set *A_difference_C = set_difference(set_A, set_C);
    const Set *A_difference_D = set_difference(set_A, set_C);
    const Set *A_union_D = set_union(set_A, set_D);
    const Set *E_union_C = set_union(set_A, set_C);
    const Set *E_union_C_intersection_B = set_intersection(E_union_C, set_B);
    const Set *D_difference_A = set_difference(set_D, set_A);
    const Set *D_difference_E = set_difference(set_D, set_E);
    const Set *A_difference_F = set_difference(set_A, set_F);
    const Set *A_union_F = set_union(set_A, set_F);
    const Set *A_intersection_F = set_intersection(set_A, set_F);


    check_numbers(A_union_B);
    check_numbers(A_intersection_B);
    check_numbers(A_difference_B);
    check_numbers(A_difference_C);

    /*printf("expand_set %s:\n", D_difference_E->symbol);
    printf("%s\n\n", expand_set(D_difference_E));

    printf("expand_set %s:\n", set_C->symbol);
    printf("%s\n\n", expand_set(set_C));

    printf("expand_set %s:\n", set_D->symbol);
    printf("%s\n\n", expand_set(set_D));

    printf("expand_set %s:\n", set_E->symbol);
    printf("%s\n\n", expand_set(set_E));

    printf("expand_set %s:\n", A_union_D->symbol);
    printf("%s\n\n", expand_set(A_union_D));

    printf("expand_set %s:\n", set_A->symbol);
    printf("%s\n\n", expand_set(set_A));*/

    printf("expand_set %s:\n", set_A->symbol);
    printf("%s\n\n", expand_set(set_A));

    printf("expand_set %s:\n", A_difference_B->symbol);
    printf("%s\n\n", expand_set(A_difference_B));

    printf("expand_set %s:\n", set_B->symbol);
    printf("%s\n\n", expand_set(set_B));

    printf("expand_set %s:\n", E_union_C_intersection_B->symbol);
    printf("%s\n\n", expand_set(E_union_C_intersection_B));


    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_difference_B->symbol, is_subset(set_A, A_difference_B));

    /*

    printf("%s ⊆ %s = %d\n\n", A_intersection_B->symbol, set_A->symbol, is_subset(A_intersection_B, set_A));
    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_union_B->symbol, is_subset(set_A, A_union_B));
    printf("%s ⊆ %s = %d\n\n", A_difference_B->symbol, A_union_B->symbol, is_subset(A_difference_B, A_union_B));
    printf("%s ⊆ %s = %d\n\n", A_difference_B->symbol, set_B->symbol, is_subset(A_difference_B, set_B));
    printf("%s ⊆ %s = %d\n\n", A_union_B->symbol, set_B->symbol, is_subset(A_union_B, set_B));
    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_difference_B->symbol, is_subset(set_A, A_difference_B));
    printf("%s ⊆ %s = %d\n\n", A_intersection_B->symbol, A_union_B->symbol, is_subset(A_intersection_B, A_union_B));
    printf("%s ⊆ %s = %d\n\n", A_intersection_B->symbol, set_B->symbol, is_subset(A_intersection_B, set_B));
    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_intersection_B->symbol, is_subset(set_A, A_intersection_B));
    printf("%s ⊆ %s = %d\n\n", set_C->symbol, A_union_D->symbol, is_subset(set_C, A_union_D));
    printf("%s ⊆ %s = %d\n\n", set_C->symbol, D_difference_A->symbol, is_subset(set_C, D_difference_A));
    printf("%s ⊆ %s = %d\n\n", set_C->symbol, D_difference_E->symbol, is_subset(set_C, D_difference_E));

    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_difference_F->symbol, is_subset(set_A, A_difference_F));
    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_difference_B->symbol, is_subset(set_A, A_difference_B));

    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_intersection_F->symbol, is_subset(set_A, A_intersection_F));
    printf("%s ⊆ %s = %d\n\n", set_A->symbol, A_union_F->symbol, is_subset(set_A, A_union_F));*/

    //print_set(D_difference_E, 0);
    //print_set(set_C, 0);
    printf("\n#---- end test_sets_2\n\n");
}

void test_sets() {
    #define SETS 8

    const Set *sets[SETS] = {&U, &R, &Z, &N, &P, &D, &Z_, &E};

    const Set *sets_union_check;
    const Set *sets_intersection_check;

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
            const Set *sets_intersection = set_intersection(set, set2);
            //print_set(sets_union, 0);
            if (i==5 && j == 6) {
                sets_union_check = sets_union;
                sets_intersection_check = sets_intersection;
            }
            check_numbers(sets_union);
            printf("\n");
            check_numbers(sets_intersection);
            printf("\n");
        }
        printf("\n\n");
    }
    printf("sets_union_check->symbol = %s\n", sets_union_check->symbol);
    print_set(sets_union_check, 0);
    check_numbers(sets_union_check);
    printf("\n");
    print_set(sets_intersection_check, 0);
    check_numbers(sets_intersection_check);
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
