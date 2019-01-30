// Set of Real numbers (R)

#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "universe.h"


// Static functions
static const bool belongs_real(const Number x);
static const unsigned int *get_rules_real();
static const Relation *get_relations_real();

// Static variables
static Relation *relations_real = NULL;
unsigned int *rules_real = NULL;



// Main struct
static const Set R = {
    .symbol = 'R',
    .belongs = &belongs_real,
    .relations_length = 1,
    .relations = &get_relations_real
};



//---- Function implementations ----//

static const bool belongs_real(const Number x) {
    return belongs_to_set(x, R);
}

static const Relation *get_relations_real() {
    if (relations_real != NULL) {
        return relations_real;
    }
    const static unsigned int N_RELATIONS = 1;
    const Relation r1 = {
        .A = &U,
        .B = &E,
        .type = OR,
        .rules_length = 0,
        .get_rule_indexes = &get_rules_real
    };
    relations_real = get_relations(N_RELATIONS, &r1);
    return relations_real;
}

const unsigned int *get_rules_real() {
    if (rules_real != NULL) {
        return rules_real;
    }
    const static unsigned int N_RULES = 0;
    rules_real = get_rules(N_RULES);
    return rules_real;
}

#endif
