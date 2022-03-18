#include <stdio.h>
#ifndef COMPILER_MD_FOOD_H
#define COMPILER_MD_FOOD_H

#define BLOCK_FOOD 10
#define ADD 1
#define OUT 2

#define STRLEN_(x) #x
#define STRLEN(x) STRLEN_(x)
#define MAX_LEN_NAME 32
#define MAX_LEN_NAME_STR 31

FILE *ostream, *istream, *ostream_result;

int fib(int n);

struct Food_composition {
    char name[MAX_LEN_NAME];
    double energy_value;
    double protein;
    double fats;
    double carbohydrates;
    struct Add {
        char name[MAX_LEN_NAME];
        double value;
        struct Add *next;
    } *minerals, *vitamins, *additives;
    struct Food_composition *next;
};

typedef struct Food_composition Food_composition;
typedef struct Add Add;

// Методы для стека Food_composition
void Food_composition_add(Food_composition **);
void Food_composition_all_memory_free(Food_composition **);
void Food_composition_input(Food_composition *);

// Методы для стека Add
void Add_add(Add **);
void Add_all_memory_free(Add **);
void Add_input_data(Add *);

// Функции ввода/вывода
double input_double();
void input_string(char *);
//void clear_input();

// Функции заполения структуры о составе питания
int enter_diet(Food_composition **);
void Add_input(Food_composition **);

// Функции подбора завтрака по пользовательским критериям
int choose_diet(const Food_composition *);

int main_logic();

#endif //COMPILER_MD_FOOD_H
