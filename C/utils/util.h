#ifndef utils_util_h
#define utils_util_h

#include <stdlib.h>
#include <string.h>

typedef long double Number;

static Number get_number_string(const char *n_string) {
    const Number number = strtold(n_string, NULL);
    return number;
}

static Number get_short_int(const short int n) {
    char n_string[65];
    snprintf(n_string, 64, "%hd", n);
    return get_number_string(n_string);
}

static Number get_unsigned_short_int(const unsigned short int n) {
    char n_string[65];
    snprintf(n_string, 64, "%hu", n);
    return get_number_string(n_string);
}

static Number get_int(const int n) {
    char n_string[65];
    snprintf(n_string, 64, "%d", n);
    return get_number_string(n_string);
}

static Number get_unsigned_int(const unsigned int n) {
    char n_string[65];
    snprintf(n_string, 64, "%u", n);
    return get_number_string(n_string);
}

static Number get_long_int(const long int n) {
    char n_string[65];
    snprintf(n_string, 64, "%ld", n);
    return get_number_string(n_string);
}

static Number get_unsigned_long_int(const unsigned long int n) {
    char n_string[65];
    snprintf(n_string, 64, "%lu", n);
    return get_number_string(n_string);
}

static Number get_long_long_int(const long long int n) {
    char n_string[65];
    snprintf(n_string, 64, "%lld", n);
    return get_number_string(n_string);
}

static Number get_unsigned_long_long_int(const unsigned long long int n) {
    char n_string[65];
    snprintf(n_string, 64, "%llu", n);
    return get_number_string(n_string);
}

static Number get_float(const float n) {
    char n_string[65];
    snprintf(n_string, 64, "%f", n);
    return get_number_string(n_string);
}

static Number get_double(const double n) {
    char n_string[65];
    snprintf(n_string, 64, "%f", n);
    return get_number_string(n_string);
}

static Number get_long_double(const long double n) {
    return n;
}

#define get_number(x)                                                                            \
  _Generic((x),        /* Get the name of a type */                                             \
    short int: get_short_int(x),            unsigned short int: get_unsigned_short_int(x),      \
          int: get_int(x),                        unsigned int: get_unsigned_int(x),            \
     long int: get_long_int(x),              unsigned long int: get_unsigned_long_int(x),       \
long long int: get_long_long_int(x),    unsigned long long int: get_unsigned_long_long_int(x),  \
         float: get_float(x),                             double: get_double(x),                  \
  long double: get_long_double(x),                     default: 0)


#endif
