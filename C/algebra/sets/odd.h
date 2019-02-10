// Set of Even numbers (P)
#ifndef algebra_sets_odd_h
#define algebra_sets_odd_h

#include "../../utils/number.h"
#include "natural.h"



//---- Static constants
#define N_RULES_ODD 1
#define N_RELATIONS_ODD_AND 1
#define N_RELATIONS_ODD_OR 0



//---- Function declarations
const bool belongs_odd(const Number x);
const Relations *get_relations_odd();



//---- Static variables
static Relations *relations_odd = NULL;



//---- Main struct
const static Set D = {
    .symbol = "D",
    .belongs = &belongs_odd,
    .relations = &get_relations_odd,
};



//---- Function implementations

const bool belongs_odd(const Number x) {
    return belongs_to_set(x, &D);
}

const Relations *get_relations_odd() {
    if (relations_odd != NULL) {
        return relations_odd;
    }

    //-- OR relations
    Relation *or_relations = get_relations_part(N_RELATIONS_ODD_OR);

    // AND relations
    const Relation and_1 = {
        .A = &N,
        .B = &E,
        .type = OR
    };
    Relation *and_relations = get_relations_part(N_RELATIONS_ODD_AND, and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_ODD, ONLY_ODD);

    // All Relations
    relations_odd = get_relations(or_relations, and_relations,
        N_RELATIONS_ODD_OR, N_RELATIONS_ODD_AND, rules, N_RULES_ODD);

    return relations_odd;
}

#endif
