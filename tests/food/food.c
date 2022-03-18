#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "food.h"

extern FILE *istream, *ostream, *ostream_result;

int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}


void Food_composition_add(Food_composition ** head) {
    if (*head == NULL) {
        *head = (Food_composition *) malloc(sizeof(Food_composition));
        (*head)->additives = NULL;
        (*head)->vitamins = NULL;
        (*head)->minerals = NULL;
        (*head)->next = NULL;
    }
    else {
        Food_composition *tmp;
        tmp = (Food_composition *) malloc(sizeof(Food_composition));
        tmp->additives = NULL;
        tmp->vitamins = NULL;
        tmp->minerals = NULL;
        tmp->next = *head;
        *head = tmp;
    }
}

void Add_add(Add ** head) {
    if (*head == NULL) {
        *head = (Add *) malloc(sizeof(Add));
        (*head)->next = NULL;
    }
    else {
        Add *tmp;
        tmp = (Add *) malloc(sizeof(Add));
        tmp->next = *head;
        *head = tmp;
    }
}
void Food_composition_all_memory_free(Food_composition **head) {
    if (*head == NULL)
        return;
    Food_composition * tmp;
    while ((*head)->next != NULL) {
        tmp = *head;
        *head = (*head)->next;
        Add_all_memory_free(&(tmp->additives));
        Add_all_memory_free(&(tmp->vitamins));
        Add_all_memory_free(&(tmp->minerals));
        tmp->next = NULL;
        free(tmp);
    }
    Add_all_memory_free(&((*head)->additives));
    Add_all_memory_free(&((*head)->vitamins));
    Add_all_memory_free(&((*head)->minerals));
    free(*head);
}

void Add_all_memory_free(Add **head) {
    if (*head == NULL)
        return;
    Add * tmp;
    while ((*head)->next != NULL) {
        tmp = *head;
        *head = (*head)->next;
        tmp->next = NULL;
        free(tmp);
    }
    free(*head);
}


void Food_composition_input(Food_composition * food) {
    fprintf(ostream, "Введите название рациона питания\n");
    input_string(food->name);
    fprintf(ostream, "Введите энергетическую ценность\n");
    food->energy_value = input_double();
    fprintf(ostream, "Введите содержание белков\n");
    food->protein = input_double();
    fprintf(ostream, "Введите содержание жиров\n");
    food->fats = input_double();
    fprintf(ostream, "Введите содержание углеводов\n");
    food->carbohydrates = input_double();
}

void Add_input_data(Add * add) {
    input_string(add->name);
    fprintf(ostream, "Введите кол-во\n");
    add->value = input_double();
}

int enter_diet(Food_composition ** food){
    Food_composition_add(food);
    Food_composition_input(*food);
    int done;
    int input_symbol;
    done = 0;
    while (done == 0) {
        fprintf(ostream, "Есть добавки?\n1 - Да\n2 - Нет\n");
        input_symbol = (int) input_double();
        switch (input_symbol) {
            case ADD:
                Add_input(food);
                break;
            case OUT:
                done = 1;
                break;
            default:
                break;
        }
    }
    return 0;
}

void Add_input(Food_composition ** food) {
    fprintf(ostream, "Тип добавки:\n1 - пищевые добавки\n2 - витамины\n3 - минералы\n");
    int type;
    type = (int) input_double();

    switch (type) {
        case 1:
            Add_add(&((*food)->additives));
            fprintf(ostream, "Введите название добавки\n");
            Add_input_data((*food)->additives);
            break;
        case 2:
            Add_add(&((*food)->vitamins));
            fprintf(ostream, "Введите название витамина\n");
            Add_input_data((*food)->vitamins);
            break;
        case 3:
            Add_add(&((*food)->minerals));
            fprintf(ostream, "Введите название минерала\n");
            Add_input_data((*food)->minerals);
            break;
        default:
            break;
    }
}


int choose_diet(const Food_composition * food) {
    if (food == NULL) {
        fprintf(ostream, "Нет структур с информацией о составе рациона питания\n");
        return 1;
    }
    fprintf(ostream, "Выберите критерии для поиска рациона:\n");
    fprintf(ostream, "1 - энергетическая ценность\n2 - кол-во белков\n3 - кол-во жиров\n4 - кол-во углеводов\n5 - наличие пищевых добавок\n6 - наличие витаминов\n7 - наличие минералов\n");
    int type;
    type = (int) input_double();
    switch (type) {
        case 1:
        {
            fprintf(ostream, "Введите значение:\n");
            double value;
            value = input_double();
            fprintf(ostream, "Подходящие варианты:\n");
            do {
                if (food->energy_value == value) {
                    fprintf(ostream_result, "%s\n", food->name);
                }
                food = food->next;
            } while (food != NULL);
        };
            break;
        case 2:
        {
            fprintf(ostream, "Введите значение:\n");
            double value;
            value = input_double();
            fprintf(ostream, "Подходящие варианты:\n");
            do {
                if (food->protein == value) {
                    fprintf(ostream_result, "%s\n", food->name);
                }
                food = food->next;
            } while (food != NULL);
        };
            break;
        case 3:
        {
            fprintf(ostream, "Введите значение:\n");
            double value;
            value = input_double();
            fprintf(ostream, "Подходящие варианты:\n");
            do {
                if (food->fats == value) {
                    fprintf(ostream_result, "%s\n", food->name);
                }
                food = food->next;
            } while (food != NULL);
        };
            break;
        case 4:
        {
            fprintf(ostream, "Введите значение:\n");
            double value;
            value = input_double();
            fprintf(ostream, "Подходящие варианты:\n");
            do {
                if (food->carbohydrates == value) {
                    fprintf(ostream_result, "%s\n", food->name);
                }
                food = food->next;
            } while (food != NULL);
        };
            break;
        case 5:
        {
            char _name[MAX_LEN_NAME];
            fprintf(ostream, "Введите название пищевой добавки\n");
            input_string(_name);
            fprintf(ostream, "Введите кол-во\n");
            double value;
            value = input_double();
            Add *head;
            fprintf(ostream, "Подходящие варианты:\n");
            do {
                if(food->additives == NULL)
                    continue;
                do {
                    head = food->additives;
                    if(strcmp(_name, head->name) == 0)
                        if(head->value == value) {
                            fprintf(ostream_result, "%s\n", food->name);
                        }
                    head = head->next;
                } while (head != NULL);
                food = food->next;
            } while (food != NULL);
        };
            break;
        case 6:
        {
            char _name[MAX_LEN_NAME];
            fprintf(ostream, "Введите название пищевой добавки\n");
            input_string(_name);
            fprintf(ostream, "Введите кол-во\n");
            double value;
            value = input_double();
            Add *head;
            fprintf(ostream, "Подходящие варианты:\n");
            do {
                if(food->vitamins == NULL)
                    continue;
                do {
                    head = food->vitamins;
                    if(strcmp(_name, head->name) == 0)
                        if(head->value == value) {
                            fprintf(ostream_result, "%s\n", food->name);
                        }
                    head = head->next;
                } while (head != NULL);
                food = food->next;
            } while (food != NULL);
        };
            break;
        case 7:
        {
            char _name[MAX_LEN_NAME];
            fprintf(ostream, "Введите название пищевой добавки\n");
            input_string(_name);
            fprintf(ostream, "Введите кол-во\n");
            double value;
            value = input_double();
            Add *head;
            fprintf(ostream, "Подходящие варианты:\n");
            do {
                if(food->vitamins == NULL)
                    continue;
                do {
                    head = food->minerals;
                    if(strcmp(_name, head->name) == 0)
                        if(head->value == value) {
                            fprintf(ostream_result, "%s\n", food->name);
                        }
                    head = head->next;
                } while (head != NULL);
                food = food->next;
            } while (food != NULL);
        };
            break;
        default:
            return 0;
    }
    return 1;
}

double input_double() {
    double digital;
    fscanf(istream, "%lf", &digital);
    return digital;
}

void input_string(char *buf) {
    fscanf(istream, "%" STRLEN(MAX_LEN_NAME_STR) "s", buf);
}

int main_logic() {
    Food_composition *food;
    food = NULL;
    int done;
    int input_symbol;
    done = 0;
    while(done == 0) {
        fprintf(ostream, "Введите действие:\n 1 - ввести рацион\n 2 - подобрать рацион\n");
        input_symbol = (int) input_double();
        switch (input_symbol) {
            case ADD:
                done = enter_diet(&food);
                break;
            case OUT:
                done = choose_diet(food);
                break;
            default:
                continue;
        }
    }
    Food_composition_all_memory_free(&food);
    return 0;
}