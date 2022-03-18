#include "add.h"
#include <stdio.h>
#include <stdlib.h>

//extern FILE *istream, *ostream, *ostream_result;

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

void Add_input_data(Add * add) {
    input_string(add->name);
    fprintf(ostream, "Введите кол-во\n");
    add->value = input_double();
}

