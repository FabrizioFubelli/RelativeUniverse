// Set of Integers (Z)

#ifndef algebra_sets_integer_h
#define algebra_sets_integer_h

#include "../../utils/number.h"
#include "set_interface.h"
#include "real.h"



//---- Static constants
#define N_RULES_INTEGER 1
#define N_RELATIONS_INTEGER_AND 1
#define N_RELATIONS_INTEGER_OR 0



//---- Function declarations
const bool belongs_integer(const Number x);
const Relations *get_relations_integer();



//---- Static variables
static Relations *relations_integer = NULL;



//---- Main struct
const static Set Z = {
    .symbol = "Z",
    .belongs = &belongs_integer,
    .relations = &get_relations_integer,
};



//---- Function implementations

const bool belongs_integer(const Number x) {
    return belongs_to_set(x, &Z);
}

const Relations *get_relations_integer() {
    if (relations_integer != NULL) {
        return relations_integer;
    }

    //-- OR relations
    Relation *or_relations = get_relations_part(N_RELATIONS_INTEGER_OR);

    // AND relations
    const Relation and_1 = {
        .A = &R,
        .B = &E,
        .type = OR
    };
    Relation *and_relations = get_relations_part(N_RELATIONS_INTEGER_AND, and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_INTEGER, ONLY_INTEGERS);

    // All Relations
    relations_integer = get_relations(or_relations, and_relations,
        N_RELATIONS_INTEGER_OR, N_RELATIONS_INTEGER_AND, rules, N_RULES_INTEGER);

    return relations_integer;
}

#endif
