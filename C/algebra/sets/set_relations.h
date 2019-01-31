#ifndef algebra_sets_set_relations_h
#define algebra_sets_set_relations_h

#include <stdbool.h>

typedef unsigned int (*rules_fun)();
typedef struct relation Relation;
typedef struct relations Relations;
typedef enum relation_type {
    AND=1, OR=2
} RelationType;

#include "../../utils/util.h"
#include "set_interface.h"

struct relation
{
    const Set *A;
    const Set *B;
    const unsigned short int type;
};

struct relations
{
    const unsigned int rules_length;
    const unsigned int *rules_index;
    const unsigned int and_length;
    const unsigned int or_length;
    const Relation* and;
    const Relation* or;
};

static void print_relation(Relation relation, const unsigned int left) {
    unsigned int i, s;
    char *space = (char *) malloc(left*sizeof(char)+1);
    for (s=0; s<left; s++) {
        space[s] = ' ';
    }
    space[s] = '\0';
    printf("%s|-- A ", space);
    print_set(relation.A, left+6);
    printf("%s|-- B ", space);
    print_set(relation.B, left+6);
    free(space);
}

static void print_relations(Relations relations, const unsigned int left) {
    unsigned int i, s;
    char *space = (char *) malloc(left*sizeof(char)+1);
    for (s=0; s<left; s++) {
        space[s] = ' ';
    }
    space[s] = '\0';
    printf("%s|--Relations\n", space);
    printf("%s    |\n", space);
    printf("%s    |--rules_length: %u\n", space, relations.rules_length);
    if (relations.rules_length > 0) {
        printf("%s    |\n", space);
        printf("%s    |--rules_index\n", space);
        for (i=0; i<relations.rules_length; i++) {
            bool last = i == relations.rules_length-1;
            printf("%s    %c      |\n", space, last ? ' ' : '|');
            const unsigned int rule_index = relations.rules_index[i];
            char *rule_name =  rule_to_string(rule_index);
            printf("%s    %c      |-- %u. Rule: %s\n", space, last ? ' ' : '|', i+1, rule_name);
            free(rule_name);
        }
    }
    printf("%s    |\n", space);

    printf("%s    |--and_length: %u\n", space, relations.and_length);
    if (relations.and_length > 0) {
        printf("%s    |\n", space);
        printf("%s    |--and (list)\n", space);
        for (i=0; i<relations.and_length; i++) {
            bool last = i == relations.and_length-1;
            Relation and = relations.and[i];
            printf("%s    %c  |\n", space, last ? ' ' : '|');
            printf("%s    %c  |-- %u. Relation (type: %s)\n", space, last ? ' ' : '|', i+1, and.type == OR ? "OR" : (and.type == AND ? "AND" : "UNKNOWN"));
            printf("%s    %c            |\n", space, last ? ' ' : '|');
            print_relation(and, left+17);
        }
    }
    printf("%s    |\n", space);
    printf("%s    |--or_length: %u\n", space, relations.or_length);
    if (relations.or_length > 0) {
        printf("%s    |\n", space);
        printf("%s    |--or (list)\n", space);
        for (i=0; i<relations.or_length; i++) {
            bool last = i == relations.or_length-1;
            Relation or = relations.or[i];
            printf("%s    %c  |\n", space, last ? ' ' : '|');
            printf("%s    %c  |-- %u. Relation (type: %s)\n", space, last ? ' ' : '|', i+1, or.type == OR ? "OR" : (or.type == AND ? "AND" : "UNKNOWN"));
            printf("%s    %c            |\n", space, last ? ' ' : '|');
            print_relation(or, left+17);
        }
    }
    printf("\n");
    free(space);
}

#endif
