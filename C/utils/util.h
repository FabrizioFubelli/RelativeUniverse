#ifndef utils_util_h
#define utils_util_h

/* 'pwd' to get path to the current file in C Program */

#include <stdlib.h>
#include <stdio.h>  /* defines FILENAME_MAX */
//#define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define get_current_dir _getcwd
#else
#include <unistd.h>
#define get_current_dir getcwd
#endif

static char *pwd() {
    char *current_dir = (char *) malloc(FILENAME_MAX);
    get_current_dir(current_dir, FILENAME_MAX);
    return current_dir;
}

#endif
