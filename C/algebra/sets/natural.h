// Set of Natural numbers (N)
#ifndef algebra_sets_natural_h
#define algebra_sets_natural_h

#include "../../utils/number.h"
#include "set_interface.h"
#include "integer.h"



//---- Static constants
#define N_RULES_NATURAL 1
#define N_RELATIONS_NATURAL_AND 1
#define N_RELATIONS_NATURAL_OR 0



//---- Function declarations
const bool belongs_natural(const Number x);
const Relations *get_relations_natural();



//---- Static variables
static Relations *relations_natural = NULL;



//---- Main struct
const static Set N = {
    .symbol = 'N',
    .belongs = &belongs_natural,
    .relations = &get_relations_natural,
};



//---- Function implementations

const bool belongs_natural(const Number x) {
    return belongs_to_set(x, N);
}

const Relations *get_relations_natural() {
    if (relations_natural != NULL) {
        return relations_natural;
    }

    //-- OR relations
    Relation *or_relations = get_relations_part(N_RELATIONS_NATURAL_OR);

    // AND relations
    const Relation and_1 = {
        .A = &Z,
        .B = &E,
        .type = OR
    };
    Relation *and_relations = get_relations_part(N_RELATIONS_NATURAL_AND, and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_NATURAL, ONLY_NATURAL);

    // All Relations
    relations_natural = get_relations(or_relations, and_relations,
        N_RELATIONS_NATURAL_OR, N_RELATIONS_NATURAL_AND, rules, N_RULES_NATURAL);

    return relations_natural;
}

#endif
