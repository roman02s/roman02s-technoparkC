#ifndef COMPILER_MD_INPUT_H
#define COMPILER_MD_INPUT_H
#include <stdio.h>

#define ADD 1
#define OUT 2

#define STRLEN_(x) #x
#define STRLEN(x) STRLEN_(x)
#define MAX_LEN_NAME 32
#define MAX_LEN_NAME_STR 31

extern FILE *istream, *ostream, *ostream_result;

// Функции ввода/вывода
double input_double();
void input_string(char *);



#endif //COMPILER_MD_INPUT_H
