#ifndef utils_util_h
#define utils_util_h

#include <stdlib.h>
#include <string.h>

typedef enum {
    t_other=0,
    t_bool=1,
    t_unsigned_char=2, t_char=3, t_signed_char=4,
    t_short_int=5, t_unsigned_short_int=6, t_int=7, t_unsigned_int=8,
    t_long_int=9, t_unsigned_long_int=10, t_long_long_int=11, t_unsigned_long_long_int=12,
    t_float=13,
    t_double=14, t_long_double=15,
    t_pointer_to_char=16, t_pointer_to_void=17, t_pointer_to_int=18,
    t_set=19, t_number=20
} Type;

typedef long double Number;

static Number get_number(void *n, Type t);
static char *str_typename(Type t);

#include "../algebra/sets/set_interface.h"

#define typename(x) _Generic((x),        /* Get the name of a type */              \
        _Bool: t_bool,                   unsigned char: t_unsigned_char,          \
         char: t_char,                     signed char: t_signed_char,            \
    short int: t_short_int,         unsigned short int: t_unsigned_short_int,     \
          int: t_int,                     unsigned int: t_unsigned_int,           \
     long int: t_long_int,           unsigned long int: t_unsigned_long_int,      \
long long int: t_long_long_int, unsigned long long int: t_unsigned_long_long_int, \
         float: t_float,                          double: t_double,                 \
  long double: t_long_double,                   char *: t_pointer_to_char,        \
       void *: t_pointer_to_void,                int *: t_pointer_to_int,         \
          Set: t_set,                          default: t_other)

static char *str_typename(Type t) {
    switch (t) {
        case t_bool:
            return "bool";
        case t_unsigned_char:
            return "unsigned char";
        case t_char:
            return "char";
        case t_signed_char:
            return "signed char";

        case t_short_int:
            return "short int";
        case t_unsigned_short_int:
            return "unsigned short int";
        case t_int:
            return "int";
        case t_unsigned_int:
            return "unsigned int";

        case t_long_int:
            return "long int";
        case t_unsigned_long_int:
            return "unsigned long int";
        case t_long_long_int:
            return "long long int";
        case t_unsigned_long_long_int:
            return "unsigned long long int";

        case t_float:
            return "float";
        case t_double:
            return "double";
        case t_long_double:
            return "long double";
        case t_pointer_to_char:
            return "char *";

        case t_pointer_to_void:
            return "void *";
        case t_pointer_to_int:
            return "int *";

        case t_set:
            return "Set";

        default:
            return "other";
    }
}

static Number get_number(void *n, Type t) {
    printf("get_number(void *, %s)\n", str_typename(t));
    char n_string[65];
    switch (t) {
        case t_unsigned_short_int:
        snprintf(n_string, 64, "%hu", *(unsigned short int *) n);
        break;

        case t_unsigned_int:
        snprintf(n_string, 64, "%u", *(unsigned int *) n);
        break;

        case t_unsigned_long_int:
        snprintf(n_string, 64, "%lu", *(unsigned long int *) n);
        break;

        case t_unsigned_long_long_int:
        snprintf(n_string, 64, "%llu", *(unsigned long long int *) n);
        break;

        case t_short_int:
        snprintf(n_string, 64, "%hd", *(short int *) n);
        break;

        case t_int:
        snprintf(n_string, 64, "%d", *(int *) n);
        break;

        case t_long_int:
        snprintf(n_string, 64, "%ld", *(long int *) n);
        break;

        case t_long_long_int:
        snprintf(n_string, 64, "%lld", *(long long int *) n);
        break;

        case t_float:
        snprintf(n_string, 64, "%f", *(float *) n);
        break;

        case t_double:
        snprintf(n_string, 64, "%f", *(double *) n);
        break;

        case t_long_double:
        free(n);
        return *(Number *) n;

        case t_number:
        free(n);
        return *(Number *) n;

        default:
        printf("type %s is not a number!\n", str_typename(t));
        free(n);
        return 0;
    }
    printf("String (Lf): %s\n", n_string);
    Number n_new = strtold(n_string, NULL);
    printf("Number (Lf): %Lf\n", n_new);
    free(n);
    return n_new;
}


#define CACHE_ALIGNMENT 16

#define get_number2(x_pointer, x)  \
    _Generic((x),        /* Get the name of a type */                                                                               \
    short int: get_number(x_pointer, t_short_int),      unsigned short int: get_number(x_pointer, t_unsigned_short_int),            \
          int: get_number(x_pointer, t_int),            unsigned int: get_number(x_pointer, t_unsigned_int),                        \
     long int: get_number(x_pointer, t_long_int),       unsigned long int: get_number(x_pointer, t_unsigned_long_int),              \
long long int: get_number(x_pointer, t_long_long_int),  unsigned long long int: get_number(x_pointer, t_unsigned_long_long_int),    \
         float: get_number(x_pointer, t_float),           double: get_number(x_pointer, t_double),                                    \
  long double: get_number(x_pointer, t_long_double),    default: get_number(x_pointer, t_other))



#define get_number1(x) get_number2(memcpy(aligned_alloc(sizeof(x), CACHE_ALIGNMENT), &x, CACHE_ALIGNMENT), x)

#endif
