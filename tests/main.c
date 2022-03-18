#include <stdio.h>
#include <stdlib.h>
#include "food/food.h"

extern FILE *istream, *ostream, *ostream_result;

int main() {
    istream = stdin;
    ostream = stdout;
    ostream_result = stdout;
    main_logic();
    return 0;
}
