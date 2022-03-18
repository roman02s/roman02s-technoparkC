#ifndef COMPILER_MD_ADD_H
#define COMPILER_MD_ADD_H

#include "food.h"
#include "input.h"



struct Add {
    char name[MAX_LEN_NAME];
    double value;
    struct Add *next;
};

typedef struct Add Add;

// Методы для стека Add
void Add_add(Add **);
void Add_all_memory_free(Add **);
void Add_input_data(Add *);


#endif //COMPILER_MD_ADD_H
