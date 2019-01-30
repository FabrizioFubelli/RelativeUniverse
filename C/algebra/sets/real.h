// Set of Real numbers (R)
#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "universe.h"

const bool belongs_real(const Number x);
const unsigned int *rules_real();

static const Set R = {
    .symbol = 'R',
    .belongs = &belongs_real,
    .relations_length = 1,
    .relations = {
        {
            .A = &U,
            .B = &E,
            .type = OR,
            .rules_tot = 0,
            .get_rule_numbers = rules_real
        }
    }
};

const bool belongs_real(const Number x) {
    return belongs_to_set(x, R);
}

const unsigned int *rules_real() {
    return NULL;
}

#endif
