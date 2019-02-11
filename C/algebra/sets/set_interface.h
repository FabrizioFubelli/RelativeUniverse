#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

#include <stdbool.h>
#include <stdarg.h>

typedef struct set Set;
typedef struct map_set MapSet;
static void print_set(const Set *set, const unsigned int left);
static char *rule_to_string(unsigned int index);

#include "set_relations.h"
#include "../../utils/number.h"

static bool belongs_to_set(const Set *X, const Number x);
static unsigned int *get_rules(unsigned int rules_length, ...);
const static Relation **get_relations_part(const unsigned int relations_length, ...);
static void update_dynamic_relations(char *set_symbol, Relations *relations);
const static Relations *get_dynamic_relations(const Set *self);
static Relations *get_relations(const Relation **or_r, const Relation **and_r,    \
    const unsigned int or_length, const unsigned int and_length,                \
    const unsigned int *rules_index, const unsigned int rules_length);

#define MAX_DYNAMIC_SETS 100000

static unsigned int DYNAMIC_RELATIONS_LENGTH = 0;
static RelationMap *DYNAMIC_RELATIONS[MAX_DYNAMIC_SETS];

static unsigned int DYNAMIC_SETS_LENGTH = 0;
static MapSet *DYNAMIC_SETS[MAX_DYNAMIC_SETS];

/* Set of Objects */
struct set
{
    const char *symbol;
    const bool (*belongs)(const Set *self, const Number n);
    const Relations *(*relations)(const Set *self);
};

struct map_set {
    const char *key;
    const Set *value;
};

static void print_map_set() {
    printf("print_map_set\n");
    unsigned int i;
    for (i=0; i<DYNAMIC_SETS_LENGTH; i++) {
        const MapSet *map_set = DYNAMIC_SETS[i];
        const Set *set = map_set->value;
        //printf("fun_addr = %p\n", fun_addr);
        printf("DYNAMIC_SETS[%u] = %p\n", i, set);
        printf("set->symbol = %s\n", set->symbol);
        printf("set->belongs = %p\n", set->belongs);
        printf("set->relations = %p\n", set->relations);
        printf("set <= set->belongs && set <= set->relations = %d\n",
            (unsigned long) set <= (unsigned long) set->belongs &&
            (unsigned long) set <= (unsigned long) set->relations);
    }
}

static void put_set(const Set *set) {
    const MapSet map_set = {
        .key = set->symbol,
        .value = set
    };
    MapSet* map_set_ptr = (MapSet*) malloc(sizeof(MapSet));
    memcpy(map_set_ptr, (const void *) &map_set, sizeof(MapSet));
    DYNAMIC_SETS[DYNAMIC_SETS_LENGTH++] = map_set_ptr;
}

static const Set *get_set(const unsigned int index) {
    if (0 <= index && index < DYNAMIC_SETS_LENGTH) {
        return DYNAMIC_SETS[index]->value;
    }
    return NULL;
}

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

/*
 * @return `A ⊆ B`
*/
static bool is_subset(const Set *A, const Set *B) {
    if (strcmp(A->symbol, "E") == 0) { return true; }
    if (strcmp(B->symbol, "E") == 0) { return false; }
    if (strcmp(A->symbol, B->symbol) == 0) { return true; }
    unsigned int i;
    const Relations *relations = A->relations(A);
    for (i=0; i<relations->and_length; i++) {
        const Relation *and = relations->and[i];
        if (and->type == OR) {
            if ((strcmp(and->A->symbol, "E") != 0 && is_subset(and->A, B)) ||
                (strcmp(and->B->symbol, "E") != 0 && is_subset(and->B, B))) {
                return true;
            }
        } else {
            if (is_subset(and->A, B) && is_subset(and->B, B)) {
                return true;
            }
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


#define N_RELATIONS_UNION_OR 0
#define N_RELATIONS_UNION_AND 1
#define N_RULES_UNION 0

/*
 * @return `A ∪ B`
*/
const static Set *set_union(const Set *A, const Set *B) {
    const unsigned int index = DYNAMIC_SETS_LENGTH;
    char *symbol = malloc(sizeof(char)*50);
    sprintf(symbol, "(%s∪%s)", A->symbol, B->symbol);

    // OR relations
    const Relation **or_relations = get_relations_part(N_RELATIONS_UNION_OR);

    // AND relations
    const Relation and_1 = {
        .A = A,
        .B = B,
        .type = OR
    };
    const Relation **and_relations = get_relations_part(N_RELATIONS_UNION_AND, &and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_UNION);

    // All Relations
    Relations *relations_union = relations_union = get_relations(or_relations, and_relations,
        N_RELATIONS_UNION_OR, N_RELATIONS_UNION_AND, rules, N_RULES_UNION);

    update_dynamic_relations(symbol, relations_union);

    const Set C = {
        .symbol = symbol,
        .belongs = &belongs_to_set,
        .relations = &get_dynamic_relations
    };

    const Set *C_ptr = (Set *) malloc(sizeof(Set));
    memcpy((void *) C_ptr, (const void *) &C, sizeof(Set));
    put_set(C_ptr);
    return C_ptr;
}

/*
 * @return `A ∩ B`
*/
static Set set_intersection(const Set *A, const Set *B) {
    const bool belongs_intersection(const Set *self, Number x) {
        return A->belongs(A, x) && B->belongs(B, x);
    }
    char symbol[50];
    strcpy(symbol, "(");
    strcat(symbol, A->symbol);
    strcat(symbol, "∩");
    strcat(symbol, B->symbol);
    strcat(symbol, ")");
    const Set C = {
        .symbol = symbol,
        .belongs = &belongs_intersection,
        .relations = NULL
    };
    return C;
}

static void update_dynamic_relations(char *set_symbol, Relations *relations) {
    unsigned int i;
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

/*
 * @return `P(X)`: all subsets of X
*/
static Set set_power(const Set X) {
    printf("NOT IMPLEMENTED");
}

/*
 * @return `x ∊ X`
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
        } else {
            result = result && (and->A->belongs(and->A, x) || and->B->belongs(and->B, x));
        }
    }
    for (i=0; i<relations->or_length; i++) {
        const Relation *or = relations->or[i];
        if (or->type == AND) {
            result = result || (or->A->belongs(or->A, x) && or->B->belongs(or->B, x));
        } else {
            result = result || (or->A->belongs(or->A, x) || or->B->belongs(or->B, x));
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

#endif
