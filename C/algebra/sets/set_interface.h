#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

typedef struct set Set;
static void print_set(const Set *set, const unsigned int left);
static char *rule_to_string(unsigned int index);

#include <stdbool.h>
#include <stdarg.h>

#include "../../utils/number.h"
#include "set_relations.h"

/* Set of Objects */
struct set
{
    const char symbol;
    const bool (*belongs)(const Number n);
    const Relations *(*relations)();
};

#include "set_rules.h"

static void print_set(const Set *set, const unsigned int left) {
    unsigned int s;
    char *space;
    if (left > 0) {
        space = (char *) malloc(left*sizeof(char)+1);
        for (s=0; s<left; s++) {
            space[s] = ' ';
        }
        space[s] = '\0';
    } else {
        space = "";
    }
    if (set == NULL) {
        printf("Set NULL\n", space);
        return;
    }
    printf("Set (symbol: %c)\n", set->symbol);
    printf("    %s|\n", space);
    const Relations *relations = set->relations();
    print_relations(*relations, left+4);
    if (left > 0) {
        free(space);
    }
}

/*
 * @return `A ⊆ B`
*/
static bool is_subset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ⊇ B`
*/
static bool is_superset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ⊂ B`
*/
static bool is_proper_subset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ⊃ B`
*/
static bool is_proper_superset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ∩ B`
*/
static Set set_intersection(const Set A, const Set B) {
    /*unsigned int rules_tot = = A.rules_tot;
    unsigned int *p = malloc(sizeof(unsigned int) * rules_tot);
    unsigned int rules[] = (int *) memcpy(p, A.rules, sizeof(unsigned int) * rules_tot);

    for (unsigned short i=0; i<B.rules_tot; i++) {

        for (unsigned short j=0; j<rules_tot; j++) {
            if (B.rules[i] == rules[j]) {
                break;
            }
        }
    }*/
    const bool belongs_intersection(Number x) {
        return A.belongs(x) && B.belongs(x);
    }
    const Set C = {
        .symbol = 'C',
        .belongs = &belongs_intersection
    };
    return C;
}

/*
 * @return `A ∪ B`
*/
static Set set_union(const Set A, const Set B) {
    const bool belongs_union(Number x) {
        return A.belongs(x) || B.belongs(x);
    }
    const Set C = {
        .symbol = 'C',
        .belongs = &belongs_union
    };
    return C;
}

/*
 * @return `P(X)`: all subsets of X
*/
static Set set_power(const Set X) {
    printf("NOT IMPLEMENTED");
}

/*
 * @return `x ∊ A`
*/
static bool belongs_to_set(const Number x, const Set X) {
    /*if (X.parent != NULL && !X.parent->belongs(x)) {
        return false;
    }
    for (unsigned int i=0; i<X.rules_tot; i++) {
        if (!SET_RULES[X.rules[i]](X, x)) {
            return false;
        }
    }
    return true;*/
}

static Relations *get_relations(const Relation *or_r, const Relation *and_r,
    const unsigned int or_length, const unsigned int and_length,
    const unsigned int *rules_index, const unsigned int rules_length) {

    Relations r = {
        .rules_length = rules_length,
        .rules_index = rules_index,
        .and_length = and_length,
        .or_length = or_length,
        .and = and_r,
        .or = or_r
    };

    Relations *relations = (Relations *) malloc(sizeof(Relations));
    memcpy((void *) relations, &r, sizeof(Relations));

    return relations;
}


static Relation *get_relations_part(const unsigned int relations_length, ...) {

    va_list valist;
    unsigned int i;

    Relation *relations = (Relation *) malloc(sizeof(Relation)*relations_length);

    /* initialize valist for relations_length number of arguments */
    va_start(valist, relations_length);

    /* access all the arguments assigned to valist */
    for (i = 0; i < relations_length; i++) {
        Relation r = va_arg(valist, Relation);
        memcpy(relations+i, &r, sizeof(r));
    }

    /* clean memory reserved for valist */
    va_end(valist);
    return relations;
}

static unsigned int *get_rules(unsigned int rules_length, ...) {
    va_list valist;
    unsigned int i;

    unsigned int *rules = (unsigned int *) malloc(sizeof(unsigned int)*rules_length);

    /* initialize valist for rules_length number of arguments */
    va_start(valist, rules_length);

    /* access all the arguments assigned to valist */
    for (i = 0; i < rules_length; i++) {
        unsigned int r = va_arg(valist, unsigned int);
        memcpy(rules+i, &r, sizeof(r));
    }

    /* clean memory reserved for valist */
    va_end(valist);
    return rules;
}

#endif
