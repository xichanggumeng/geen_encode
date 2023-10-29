#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genecode.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 1;
    }
    char ch, *str = NULL, *result;
    int str_length = 0;
    while ((ch = (char) getchar()) != EOF) {
        char *temp = (char *) realloc(str, str_length + 1);
        str = temp;
        str[str_length++] = ch;
    }
    str[str_length - 1] = '\0';
    if (strcmp(argv[1], "encode") == 0) {
        result = gene_encode(str);
    } else if (strcmp(argv[1], "decode") == 0) {
        result = gene_decode(str);
    } else{
        return 2;
    }
    printf("%s", result);
    return 0;
}