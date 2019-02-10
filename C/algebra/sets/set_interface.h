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

static bool belongs_to_set(const Number x, const Set *X);
static unsigned int *get_rules(unsigned int rules_length, ...);
static Relation *get_relations_part(const unsigned int relations_length, ...);
static Relations *get_relations(const Relation *or_r, const Relation *and_r,    \
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
    const bool (*belongs)(const Number n);
    const Relations *(*relations)();
};

struct map_set {
    const char *key;
    const Set *set;
};

static void put_set(const Set *set) {
    const MapSet map_set = {
        .key = set->symbol,
        .set = set
    };
    MapSet* map_set_ptr = (MapSet*) malloc(sizeof(MapSet));
    memcpy(map_set_ptr, (const void *) &map_set, sizeof(MapSet));
    DYNAMIC_SETS[DYNAMIC_SETS_LENGTH++] = map_set_ptr;
}

static const Set *get_set(void *fun_addr) {
    //printf("get_set(%d)\n", fun_addr);
    unsigned int i;
    for (i=0; i<DYNAMIC_SETS_LENGTH; i++) {
        const MapSet *map_set = DYNAMIC_SETS[i];
        const Set *set = map_set->set;
        printf("fun_addr = %p\n", fun_addr);
        printf("set->belongs = %p\n", set->belongs);
        printf("set->relations = %p\n", set->relations);
        if (set <= fun_addr  && (fun_addr <= set->belongs || fun_addr <= set->relations)) {
            return set;
        }
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
    if (set->relations != NULL) {
        const Relations *relations = set->relations();
        printf("Set (symbol: %s)\n", set->symbol);
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
static bool is_subset(const Set A, const Set B) {
    if (strcmp(A.symbol, "E") == 0) { return true; }
    if (strcmp(B.symbol, "E") == 0) { return false; }
    if (strcmp(A.symbol, B.symbol) == 0) { return true; }
    unsigned int i;
    const Relations *relations = A.relations();
    for (i=0; i<relations->and_length; i++) {
        const Relation and = relations->and[i];
        if (and.type == OR) {
            if ((strcmp(and.A->symbol, "E") != 0 && is_subset(*and.A, B)) ||
                (strcmp(and.B->symbol, "E") != 0 && is_subset(*and.B, B))) {
                return true;
            }
        } else {
            if (is_subset(*and.A, B) && is_subset(*and.B, B)) {
                return true;
            }
        }
    }
    return false;
}

/*
 * @return `A ⊇ B`
*/
static bool is_superset(const Set A, const Set B) {
    return is_subset(B, A);
}

/*
 * @return `A ⊂ B`
*/
static bool is_proper_subset(const Set A, const Set B) {
    return strcmp(A.symbol, B.symbol) != 0 && is_subset(A, B);
}

/*
 * @return `A ⊃ B`
*/
static bool is_proper_superset(const Set A, const Set B) {
    return strcmp(A.symbol, B.symbol) != 0 && is_superset(A, B);
}

/*
 * @return `A ∩ B`
*/
static Set set_intersection(const Set A, const Set B) {
    const bool belongs_intersection(Number x) {
        return A.belongs(x) && B.belongs(x);
    }
    char symbol[50];
    strcpy(symbol, "(");
    strcat(symbol, A.symbol);
    strcat(symbol, "∩");
    strcat(symbol, B.symbol);
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

const static Relations *get_dynamic_relations(const char *set_symbol) {
    unsigned int i;
    for (i=0; i<DYNAMIC_RELATIONS_LENGTH; i++) {
        if (strcmp(DYNAMIC_RELATIONS[i]->key, set_symbol) == 0) {
            const Relations *relations = DYNAMIC_RELATIONS[i]->value;
            return relations;
        }
    }
    return NULL;
}

#define N_RELATIONS_UNION_OR 0
#define N_RELATIONS_UNION_AND 1
#define N_RULES_UNION 0

#define CALLFOO label ## __LINE__: get_fun_addr(&&label ## __LINE__);

void *get_fun_addr(void *addr)
{
    printf("Caller address = %p\n", addr);
    return addr;
}

/*
 * @return `A ∪ B`
*/
const static Set *set_union(const Set *A, const Set *B) {
    char *symbol = malloc(sizeof(char)*50);
    sprintf(symbol, "(%s∪%s)", A->symbol, B->symbol);
    const Set *C_ptr = (Set *) malloc(sizeof(Set));
    const bool belongs_union(Number x) {
        get_set(0);
        return belongs_to_set(x, C_ptr);
    }
    void dummy1() {}
    const Relations *get_relations_union() {
        CALLFOO;
        get_set(0);
        /*printf("get_relations_union 0\n");
        printf("C_ptr = %d\n", C_ptr);*/

        printf("C_ptr->symbol = %s\n", C_ptr->symbol);
        //printf("get_relations_union 1\n");
        const Relations *relations = get_dynamic_relations(C_ptr->symbol);
        //printf("get_relations_union 2\n");
        for (unsigned int i=0; i<relations->and_length; i++) {
            const Relation *and = relations->and;
        }
        return relations;
    }
    void dummy2() {}

    const bool (*belongs_union_ptr)(Number) = malloc(4096);
    memcpy(belongs_union_ptr, (const void*) &belongs_union, (unsigned long) &dummy1 - (unsigned long) &belongs_union);

    const Relations *(*get_relations_union_ptr)() = malloc(4096);
    memcpy(get_relations_union_ptr, (const void*) &get_relations_union, (unsigned long) &dummy2 - (unsigned long) &get_relations_union);

    printf("get_relations_union_ptr = %p\n", get_relations_union_ptr);

    // OR relations
    Relation *or_relations = get_relations_part(N_RELATIONS_UNION_OR);

    // AND relations
    const Relation and_1 = {
        .A = A,
        .B = B,
        .type = OR
    };
    Relation *and_relations = get_relations_part(N_RELATIONS_UNION_AND, and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_UNION);

    // All Relations
    Relations *relations_union = relations_union = get_relations(or_relations, and_relations,
        N_RELATIONS_UNION_OR, N_RELATIONS_UNION_AND, rules, N_RULES_UNION);

    update_dynamic_relations(symbol, relations_union);

    const Set C = {
        .symbol = symbol,
        .belongs = belongs_union_ptr,
        .relations = get_relations_union_ptr
    };

    memcpy((void *) C_ptr, (const void *) &C, sizeof(C));
    put_set(C_ptr);
    printf("C_ptr = %p\n", C_ptr);
    return C_ptr;
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
static bool belongs_to_set(const Number x, const Set *X) {
    printf("belongs_to_set\n");
    printf("X = %d\n", X);
    unsigned int i;
    printf("belongs_to_set 1\n");
    printf("X->symbol = %s\n", X->symbol);
    const Relations *relations = X->relations();
    printf("belongs_to_set 2\n");
    bool result = true;
    for (i=0; i<relations->rules_length; i++) {
        if (!SET_RULES[relations->rules_index[i]](x)) {
            result = false;
            break;
        }
    }
    for (i=0; i<relations->and_length; i++) {
        const Relation and = relations->and[i];
        if (and.type == AND) {
            result = result && (and.A->belongs(x) && and.B->belongs(x));
        } else {
            result = result && (and.A->belongs(x) || and.B->belongs(x));
        }
    }
    for (i=0; i<relations->or_length; i++) {
        const Relation or = relations->or[i];
        if (or.type == AND) {
            result = result || (or.A->belongs(x) && or.B->belongs(x));
        } else {
            result = result || (or.A->belongs(x) || or.B->belongs(x));
        }
    }
    return result;
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
