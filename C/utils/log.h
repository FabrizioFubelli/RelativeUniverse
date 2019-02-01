#ifndef utils_log_h
#define utils_log_h

#include <stdlib.h>
#include <time.h>
#include <string.h>

//#define PATH_MAX 200
#define LOG_FILE "/tmp/RelativeUniverse.log"
#define LOG_MAX_SIZE_MB 2

typedef enum log_type {
    INFO,
    OK,
    ERROR
} LogType;

// Colors
#define C_NRM  "\x1B[0m"
#define C_RED  "\x1B[31m"
#define C_GRN  "\x1B[32m"
#define C_YEL  "\x1B[33m"
#define C_BLU  "\x1B[34m"
#define C_MAG  "\x1B[35m"
#define C_CYN  "\x1B[36m"
#define C_WHT  "\x1B[37m"

static void __write_log__(char *msg, LogType type);

static void log_info(char *msg);
static void log_err(char *msg);
static void log_done(char *msg);

struct log {
    void (*info)(char *msg);
    void (*error)(char *msg);
    void (*done)(char *msg);
} Log = { log_info, log_err, log_done };

#include "util.h"
#include "file.h"

static void log_info(char *msg) {
    __write_log__(msg, INFO);
}

static void log_done(char *msg) {
    __write_log__(msg, OK);
}

static void log_err(char *msg) {
    __write_log__(msg, ERROR);
}

static void __write_log__(char *msg, LogType type) {
    int malloc_size = sizeof(char)*(32+strlen(msg));
    char text[malloc_size];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *color = type == INFO ? C_CYN : (type == OK ? C_GRN : C_RED);
    sprintf(text, "%s[%d-%d-%d %d:%d:%d]%s %s", color, tm.tm_year + 1900,
            tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, C_NRM, msg);
    printf("%s\n", text);
    int log_file_byte = f_size(LOG_FILE);
    if (log_file_byte >= LOG_MAX_SIZE_MB*1024) {
        f_write(LOG_FILE, text);
    } else {
        f_append(LOG_FILE, text);
    }
}

#endif
