#include "input.h"
#include <stdio.h>
//#include <string.h>

FILE *istream, *ostream, *ostream_result;


double input_double() {
    double digital;
    fscanf(istream, "%lf", &digital);
    return digital;
}

void input_string(char *buf) {
    fscanf(istream, "%" STRLEN(MAX_LEN_NAME_STR) "s", buf);
}
