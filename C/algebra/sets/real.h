// Set of Real numbers (R)

#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/number.h"
#include "set_interface.h"
#include "universe.h"



//---- Static constants
#define N_RULES_REAL 0
#define N_RELATIONS_REAL_AND 1
#define N_RELATIONS_REAL_OR 0



//---- Function declarations
const bool belongs_real(const Number x);
const Relations *get_relations_real();



//---- Static variables
static Relations *relations_real = NULL;



//---- Main struct
const static Set R = {
    .symbol = "R",
    .belongs = &belongs_real,
    .relations = &get_relations_real,
};



//---- Function implementations

const bool belongs_real(const Number x) {
    return belongs_to_set(x, &R);
}

const Relations *get_relations_real() {
    if (relations_real != NULL) {
        return relations_real;
    }

    //-- OR relations
    Relation *or_relations = get_relations_part(N_RELATIONS_REAL_OR);

    // AND relations
    const Relation and_1 = {
        .A = &U,
        .B = &E,
        .type = OR
    };
    Relation *and_relations = get_relations_part(N_RELATIONS_REAL_AND, and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_REAL);

    // All Relations
    relations_real = get_relations(or_relations, and_relations,
        N_RELATIONS_REAL_OR, N_RELATIONS_REAL_AND, rules, N_RULES_REAL);

    return relations_real;
}

#endif
