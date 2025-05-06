#pragma once

#define ING_NAME_LEN 50

typedef enum _Essentiality {
    ESSENTIALITY_LOW,
    ESSENTIALITY_NORMAL,
    ESSENTIALITY_HIGH,
} Essentiality;

typedef struct  _Ingredient { // NOLINT(*-reserved-identifier)
    struct _Ingredient* next;
    struct _Ingredient* last;
    char name[ING_NAME_LEN];
    Essentiality essentiality;
    int count;
} Ingredient;


Ingredient* MakeIngredient(char name[], Essentiality essentiality, int count);

