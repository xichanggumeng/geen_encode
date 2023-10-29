#ifndef C_GENECODE_H
#define C_GENECODE_H

#include <stdlib.h>
#include <stdio.h>

char const GENE_CH[4] = {'A', 'T', 'C', 'G'};
int const GENE_A = 0;
int const GENE_T = 1;
int const GENE_C = 2;
int const GENE_G = 3;

char *gene_encode(char *str) {
    char *ptr = str, *result;
    int result_length = 0;
    while (*ptr != '\0') {
        char n = *ptr;
        int i = 0, ss[4] = {0, 0, 0, 0};
        while (n > 0) {
            ss[i++] = n % 4;
            n /= 4;
        }
        char *temp = (char *) realloc(result, result_length + 4);
        result = temp;
        for (i = 0; i < 4; ++i) {
            result[result_length++] = GENE_CH[ss[i]];
        }
        ptr++;
    }
    // µ¹Ðò ±ä ÕýÐò
    for (int i = 0, mid = result_length / 2; i < mid; ++i) {
        char temp = result[i];
        result[i] = result[result_length - i - 1];
        result[result_length - i - 1] = temp;
    }
    // ²¹³ä \0
    char *temp = (char *) realloc(result, result_length + 1);
    result = temp;
    result[result_length] = '\0';

    return result;
}

char *gene_decode(char *str) {
    char *ptr = str, *result;
    int result_length = 0;
    int t = 0, n = 0;
    while (*ptr != '\0') {
        n *= 10;
        switch (*ptr) {
            case 'A':
                n += GENE_A;
                break;
            case 'T':
                n += GENE_T;
                break;
            case 'C':
                n += GENE_C;
                break;
            case 'G':
                n += GENE_G;
                break;
        }
        ptr++;

        if (++t == 4) {
            t = 0;

            char ch = 0;
            int i = 0;
            while (n > 0) {
                ch += n % 10 * 1 << 2 * i;
                n /= 10;
                i++;
            }

            char *temp = (char *) realloc(result, result_length + 1);
            result = temp;
            result[result_length++] = ch;
        }
    }
    // µ¹Ðò ±ä ÕýÐò
    for (int i = 0, mid = result_length / 2; i < mid; ++i) {
        char temp = result[i];
        result[i] = result[result_length - i - 1];
        result[result_length - i - 1] = temp;
    }

    char *temp = (char *) realloc(result, result_length + 1);
    result = temp;
    result[result_length] = '\0';

    return result;
}

// TODO Ó³Éä£º0~9 a~z A~Z /= -> 0~64

#endif //C_GENECODE_H
