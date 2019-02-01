#ifndef utils_file_h
#define utils_file_h

static int f_size(char *file_path);
static void f_write(char *file_path, char *text);
static void f_append(char *file_path, char *text);

static void f_write(char *file_path, char *text) {
    FILE *fptr;
    fptr = fopen(file_path, "w");
    if (fptr == NULL) {
        printf("Error! Unable to write on file %s", file_path);
        return;
    }
    fprintf(fptr, "%s\n", text);
    fclose(fptr);
}

static void f_append(char *file_path, char *text) {
    FILE *fptr;
    fptr = fopen(file_path, "a");
    if (fptr == NULL) {
        printf("Error! Unable to write on file %s", file_path);
        return;
    }
    fprintf(fptr, "%s\n", text);
    fclose(fptr);
}

static int f_size(char *file_path) {
    FILE *fptr = fopen(file_path, "r");
    int prev=ftell(fptr);
    fseek(fptr, 0L, SEEK_END);
    int sz = ftell(fptr);
    fseek(fptr,prev,SEEK_SET); //go back to where we were
    fclose(fptr);
    return sz;
}

#endif
