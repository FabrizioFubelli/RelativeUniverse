#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

#include <stdbool.h>
#include <stdarg.h>

typedef struct set Set;
static void print_set(const Set *set, const unsigned int left);
static char *rule_to_string(unsigned int index);

#include "set_relations.h"
#include "../../utils/number.h"

static bool belongs_to_set(const Set *X, const Number x);
static bool is_superset(const Set *A, const Set *B) ;
static unsigned int *get_rules(unsigned int rules_length, ...);
const static Relation **get_relations_part(const unsigned int relations_length, ...);
static void update_dynamic_relations(char *set_symbol, Relations *relations);
const static Relations *get_dynamic_relations(const Set *self);
static Relations *get_relations(const Relation **or_r, const Relation **and_r,  \
    const unsigned int or_length, const unsigned int and_length,                \
    const unsigned int *rules_index, const unsigned int rules_length);

#define MAX_DYNAMIC_RELATIONS 100000

static unsigned int DYNAMIC_RELATIONS_LENGTH = 0;
static RelationMap *DYNAMIC_RELATIONS[MAX_DYNAMIC_RELATIONS];

/* Set of Objects */
struct set
{
    const char *symbol;
    const bool (*belongs)(const Set *self, const Number n);
    const Relations *(*relations)(const Set *self);
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
    printf("Set (symbol: %s)\n", set->symbol);
    if (set->relations != NULL) {
        const Relations *relations = set->relations(set);
        printf("    %s|\n", space);
        print_relations(relations, left+4);
    }
    if (left > 0) {
        free(space);
    }
}

static bool is_union(const Set *X) {
    return strstr(X->symbol, "∪") != NULL;
}
static bool is_intersaction(const Set *X) {
    return strstr(X->symbol, "∩") != NULL;
}
static bool is_difference(const Set *X) {
    return strstr(X->symbol, "-") != NULL;
}

static bool is_dynamic(const Set *X) {
    return is_union(X) || is_intersaction(X) || is_difference(X);
}

static void print_sets(const Set **sets) {
    printf("print_sets\n");
    unsigned int i=0;
    while (sets[i]) {
        const Set *set = sets[i];
        printf("Set: %s\n", set->symbol);
        i++;
    }
}

const static char *expand_set(const Set *X) {
    unsigned int i;
    char *expanded = malloc(sizeof(char)*1000);
    const Relations *relations = X->relations(X);

    for (i=0; i<relations->and_length; i++) {
        const Relation *and = relations->and[i];
        const Set *A;
        const Set *B;
        if (and->type == OR) {
            if (strcmp(and->A->symbol, "Ø") == 0) {
                A = and->B;
                B = NULL;
            } else if (strcmp(and->B->symbol, "Ø") == 0) {
                A = and->A;
                B = NULL;
            } else {
                A = and->A;
                B = and->B;
            }
        } else {
            A = and->A;
            B = and->B;
        }

        char *expanded_and_A = malloc(sizeof(char)*200);
        char *expanded_and_B = malloc(sizeof(char)*200);

        if (is_dynamic(A)) {
            sprintf(expanded_and_A, "(%s)", expand_set(A));
        } else {
            sprintf(expanded_and_A, "x ∈ %s", A->symbol);
        }

        if (B != NULL) {
            if (is_dynamic(B)) {
                sprintf(expanded_and_B, " (%s x %s %s)",
                        and->type == OR ? "∨" : "∧",
                        and->type == DIFF ? "∉" : "∈",
                        expand_set(B));
            } else {
                sprintf(expanded_and_B, " %s x %s %s",
                        and->type == OR ? "∨" : "∧",
                        and->type == DIFF ? "∉" : "∈",
                        B->symbol);
            }
        } else {
            sprintf(expanded_and_B, "");
        }

        sprintf(expanded, "%s%s%s", expanded, expanded_and_A, expanded_and_B);
    }

    // Or
    /*if ((relations->rules_length > 0 || relations->and_length > 0) && relations->or_length > 0) {
        sprintf(expanded, "%s ∨ ", expanded);
    }*/


    // Rules
    if (relations->rules_length > 0 && relations->and_length > 0) {
        sprintf(expanded, "%s | ", expanded);
    }
    for (i=0; i<relations->rules_length; i++) {
        sprintf(expanded, "%s%s%s", i > 0 ? " " : "", expanded, rule_to_string(relations->rules_index[i]));
    }

    return expanded;
    /*for (i=0; i<relations->and_length; i++) {
        const Relation *and = relations->and[i];
        if (!is_dynamic(and->A)) {
            insert_superset(and->A);
        } else {
            const Set **A_supersets = is_subset_of(and->A);
            unsigned int j = 0;
            while (A_supersets[j]) {
                insert_superset(A_supersets[j]);
                j++;
            }
        }
        if (!is_dynamic(and->B)) {
            insert_superset(and->B);
        } else {
            const Set **B_supersets = is_subset_of(and->B);
            unsigned int j = 0;
            while (B_supersets[j]) {
                insert_superset(B_supersets[j]);
                j++;
            }
        }
    }
    print_sets(supersets);
    return supersets;*/
}

/*
const static Set **is_subset_of(const Set *X) {
    unsigned int i;
    char expanded_supersets[1000];
    const Set **supersets = (const Set**) malloc(sizeof(Set*));
    unsigned int supersets_length = 0;
    void insert_superset(const Set *set) {
        for (unsigned int j=0; j<supersets_length; j++) {
            if (strcmp(supersets[j]->symbol, set->symbol) == 0) {
                return;
            }
        }
        supersets = realloc(supersets, sizeof(Set*)*supersets_length+1);
        supersets[supersets_length] = set;
        supersets_length++;
    }
    const Relations *relations = X->relations(X);
    for (i=0; i<relations->and_length; i++) {
        const Relation *and = relations->and[i];
        if (!is_dynamic(and->A)) {
            insert_superset(and->A);
        } else {
            const Set **A_supersets = is_subset_of(and->A);
            unsigned int j = 0;
            while (A_supersets[j]) {
                insert_superset(A_supersets[j]);
                j++;
            }
        }
        if (!is_dynamic(and->B)) {
            insert_superset(and->B);
        } else {
            const Set **B_supersets = is_subset_of(and->B);
            unsigned int j = 0;
            while (B_supersets[j]) {
                insert_superset(B_supersets[j]);
                j++;
            }
        }
    }
    print_sets(supersets);
    return supersets;
}*/

/*
 * @return `A ⊆ B`
*/
static bool is_subset(const Set *A, const Set *B) {
    if (strcmp(A->symbol, "Ø") == 0) { return true; }
    if (strcmp(B->symbol, "Ø") == 0) { return false; }
    if (strcmp(A->symbol, B->symbol) == 0) { return true; }
    unsigned int i;
    if (is_union(B) || is_difference(B)) {
        const Relations *B_relations = B->relations(B);
        for (i=0; i<B_relations->and_length; i++) {
            const Relation *and = B_relations->and[i];
            //printf("[1] %s must be subset of %s%s%s\n", A->symbol, and->A->symbol, type_to_symbol(and->type), and->B->symbol);
            if (and->type == OR) {
                if ((strcmp(and->A->symbol, "Ø") != 0 && is_subset(A, and->A)) ||
                    (strcmp(and->B->symbol, "Ø") != 0 && is_subset(A, and->B))) {
                    return true;
                }
            } else if (and->type == DIFF) {
                //printf("is_subset(%s, and->%s) = %d\n", A->symbol, and->A->symbol, is_subset(A, and->A));
                if (is_subset(A, and->A) && (strcmp(and->B->symbol, "Ø") == 0)) {
                    return true;
                }
            }
        }
    }
    const Relations *A_relations = A->relations(A);
    for (i=0; i<A_relations->and_length; i++) {
        const Relation *and = A_relations->and[i];
        char symbol[50];
        sprintf(symbol, "(%s%s%s)", and->A->symbol, type_to_symbol(and->type), and->B->symbol);
        if (strcmp(symbol, B->symbol) == 0) {
            return true;
        }
        if (and->type == OR) {
            if (is_subset(and->A, B) && is_subset(and->B, B)) {
                return true;
            }
        } else if (and->type == AND) {
            //printf("FLAG 1b\n");
            if (is_subset(and->A, B) || is_subset(and->B, B)) {
                return true;
            }
        } else if (and->type == DIFF) {
            if (is_subset(and->A, B)) {
                return true;
            }
            //printf("FLAG 1c\n");
        }
    }
    return false;
}

/*
 * @return `A ⊇ B`
*/
static bool is_superset(const Set *A, const Set *B) {
    return is_subset(B, A);
}

/*
 * @return `A ⊂ B`
*/
static bool is_proper_subset(const Set *A, const Set *B) {
    return strcmp(A->symbol, B->symbol) != 0 && is_subset(A, B);
}

/*
 * @return `A ⊃ B`
*/
static bool is_proper_superset(const Set *A, const Set *B) {
    return strcmp(A->symbol, B->symbol) != 0 && is_superset(A, B);
}


#define N_RELATIONS_MERGE_OR 0
#define N_RELATIONS_MERGE_AND 1
#define N_RULES_MERGE 0

const static Set *set_merge(const Set *A, const Set *B, RelationType type) {
    char *symbol = malloc(sizeof(char)*50);
    sprintf(symbol, "(%s%s%s)", A->symbol, type_to_symbol(type), B->symbol);

    // OR relations
    const Relation **or_relations = get_relations_part(N_RELATIONS_MERGE_OR);

    // AND relations
    const Relation and_1 = {
        .A = A,
        .B = B,
        .type = type
    };
    const Relation **and_relations = get_relations_part(N_RELATIONS_MERGE_AND, &and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_MERGE);

    // All Relations
    Relations *relations_union = relations_union = get_relations(or_relations, and_relations,
        N_RELATIONS_MERGE_OR, N_RELATIONS_MERGE_AND, rules, N_RULES_MERGE);

    update_dynamic_relations(symbol, relations_union);

    const Set C = {
        .symbol = symbol,
        .belongs = &belongs_to_set,
        .relations = &get_dynamic_relations
    };

    const Set *C_ptr = (Set *) malloc(sizeof(Set));
    memcpy((void *) C_ptr, (const void *) &C, sizeof(Set));
    return C_ptr;
}

/*
 * @return `A ∪ B`
*/
const static Set *set_union(const Set *A, const Set *B) {
    return set_merge(A, B, OR);
}

/*
 * @return `A ∩ B`
*/
const static Set *set_intersection(const Set *A, const Set *B) {
    return set_merge(A, B, AND);
}

/*
 * @return `A - B`
*/
const static Set *set_difference(const Set *A, const Set *B) {
    return set_merge(A, B, DIFF);
}

/*
 * @return `P(X)`: all subsets of X
*/
static Set set_power(const Set X) {
    printf("NOT IMPLEMENTED");
}

/*
 * @return `x ∈ X`
*/
static bool belongs_to_set(const Set *X, const Number x) {
    unsigned int i;
    const Relations *relations = X->relations(X);
    bool result = true;
    for (i=0; i<relations->rules_length; i++) {
        if (!SET_RULES[relations->rules_index[i]](x)) {
            result = false;
            break;
        }
    }
    for (i=0; i<relations->and_length; i++) {
        const Relation *and = relations->and[i];
        if (and->type == AND) {
            result = result && (and->A->belongs(and->A, x) && and->B->belongs(and->B, x));
        } else if (and->type == OR) {
            result = result && (and->A->belongs(and->A, x) || and->B->belongs(and->B, x));
        } else if (and->type == DIFF) {
            result = result && (and->A->belongs(and->A, x) && !and->B->belongs(and->B, x));
        }
    }
    for (i=0; i<relations->or_length; i++) {
        const Relation *or = relations->or[i];
        if (or->type == AND) {
            result = result || (or->A->belongs(or->A, x) && or->B->belongs(or->B, x));
        } else if (or->type == OR) {
            result = result || (or->A->belongs(or->A, x) || or->B->belongs(or->B, x));
        } else if (or->type == DIFF) {
            result = result || (or->A->belongs(or->A, x) && !or->B->belongs(or->B, x));
        }
    }
    return result;
}

static Relations *get_relations(const Relation **or_r, const Relation **and_r,
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
    memcpy((void *) relations, (const void *) &r, sizeof(Relations));

    return relations;
}


const static Relation **get_relations_part(const unsigned int relations_length, ...) {
    va_list valist;
    unsigned int i;

    const Relation **relations = (const Relation **) malloc(sizeof(Relation*)*relations_length);

    /* initialize valist for relations_length number of arguments */
    va_start(valist, relations_length);

    /* access all the arguments assigned to valist */
    for (i = 0; i < relations_length; i++) {
        const Relation *r = va_arg(valist, Relation*);
        const Relation *relation = malloc(sizeof(Relation));
        memcpy((void *) relation, (const void *) r, sizeof(Relation));
        memcpy((void *) relations+i, (const void *) &relation, sizeof(Relation));
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
        memcpy(rules+i, &r, sizeof(unsigned int));
    }

    /* clean memory reserved for valist */
    va_end(valist);
    return rules;
}

static void update_dynamic_relations(char *set_symbol, Relations *relations) {
    unsigned int i;
    if (MAX_DYNAMIC_RELATIONS <= DYNAMIC_RELATIONS_LENGTH) {
        Log.error("Too many dynamic relations!");
        exit(0);
    }
    for (i=0; i<DYNAMIC_RELATIONS_LENGTH; i++) {
        if (strcmp(DYNAMIC_RELATIONS[i]->key, set_symbol) == 0) {
            return;
        }
    }
    RelationMap *map_ptr = malloc(sizeof(RelationMap));
    const RelationMap map = {
        .key = set_symbol,
        .value = relations
    };
    memcpy((void *) map_ptr, &map, sizeof(RelationMap));
    DYNAMIC_RELATIONS[DYNAMIC_RELATIONS_LENGTH] = map_ptr;
    DYNAMIC_RELATIONS_LENGTH++;
}

const static Relations *get_dynamic_relations(const Set *set) {
    unsigned int i;
    for (i=0; i<DYNAMIC_RELATIONS_LENGTH; i++) {
        if (strcmp(DYNAMIC_RELATIONS[i]->key, set->symbol) == 0) {
            const Relations *relations = DYNAMIC_RELATIONS[i]->value;
            return relations;
        }
    }
    return NULL;
}

#endif
