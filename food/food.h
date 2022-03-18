#ifndef COMPILER_MD_FOOD_H
#define COMPILER_MD_FOOD_H

#include "add.h"
#include "input.h"

struct Food_composition {
    char name[MAX_LEN_NAME];
    double energy_value;
    double protein;
    double fats;
    double carbohydrates;
    struct Add *minerals;
    struct Add *vitamins;
    struct Add *additives;
    struct Food_composition *next;
};
//extern FILE *istream, *ostream, *ostream_result;

typedef struct Food_composition Food_composition;

// Методы для стека Food_composition
void Food_composition_add(Food_composition **);
void Food_composition_all_memory_free(Food_composition **);
void Food_composition_input(Food_composition *);

// Функции заполения структуры о составе питания
void Add_input(Food_composition **);

// Функции заполения структуры о составе питания
int enter_diet(Food_composition **);


// Функции подбора завтрака по пользовательским критериям
int choose_diet(const Food_composition *);

int main_logic();

#endif //COMPILER_MD_FOOD_H
