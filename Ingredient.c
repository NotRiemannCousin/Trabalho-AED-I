#include <string.h>
#include <stdlib.h>
#include "Ingredient.h"

Ingredient* MakeIngredient(char name[], Essentiality essentiality, int count) {
    Ingredient* newIngredient = (Ingredient*)malloc(sizeof(Ingredient));
    if (newIngredient == NULL) return NULL;

    strncpy(newIngredient->name, name, ING_NAME_LEN - 1);
    newIngredient->name[ING_NAME_LEN - 1] = '\0';
    newIngredient->essentiality = essentiality;
    newIngredient->count = count;
    newIngredient->last = newIngredient->next = NULL;

    return newIngredient;
}

