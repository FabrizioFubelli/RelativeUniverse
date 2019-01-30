// Set of Real numbers (R)

#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "universe.h"



//---- Static variables ----//
const static unsigned int N_RELATIONS_REAL = 1;
static Relation *and_relations_real = NULL;
static Relation *or_relations_real = NULL;
unsigned int *rules_real = NULL;



//---- Function declarations

const bool belongs_real(const Number x);
const unsigned int *get_rules_real();
const Relation *get_and_relations_real();
const Relation *get_or_relations_real();



//---- Main struct

static Set R = {
    .symbol = 'R',
    .relations_length = N_RELATIONS_REAL,
    .belongs = &belongs_real,
    .and_relations = &get_and_relations_real,
    .or_relations = &get_or_relations_real
};



//---- Function implementations

const bool belongs_real(const Number x) {
    return belongs_to_set(x, R);
}

const unsigned int *get_rules_real() {
    if (rules_real != NULL) {
        return rules_real;
    }
    const static unsigned int N_RULES = 0;
    rules_real = get_rules(N_RULES);
    return rules_real;
}

const Relation *get_and_relations_real() {
    if (and_relations_real != NULL) {
        return and_relations_real;
    }
    const Relation r1 = {
        .A = &U,
        .B = &E,
        .type = OR,
        .rules_length = 0,
        .get_rule_indexes = &get_rules_real
    };
    and_relations_real = get_relations(N_RELATIONS_REAL, &r1);
    return and_relations_real;
}

const Relation *get_or_relations_real() {
    if (or_relations_real != NULL) {
        return or_relations_real;
    }
    const Relation r1 = {
        .A = &U,
        .B = &E,
        .type = OR,
        .rules_length = 0,
        .get_rule_indexes = &get_rules_real
    };
    or_relations_real = get_relations(N_RELATIONS_REAL, &r1);
    return or_relations_real;
}

#endif
