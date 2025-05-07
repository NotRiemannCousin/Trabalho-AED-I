#pragma once
#include "Ingredient.h"

#define REC_NOME_LEN 50
#define REC_DESC_LEN 250

typedef struct _Recipe { // NOLINT(*-reserved-identifier)
    char name[REC_NOME_LEN];
    char desc[REC_DESC_LEN];
    int rating;

    Ingredient *dummyFront;
    Ingredient *dummyBack;
    int ingredientCount;

    struct _Recipe *next;
} Recipe;

typedef struct _RecipeDescriptor { // NOLINT(*-reserved-identifier)
    Recipe *dummy;
    int count;
} RecipeDescriptor;


Recipe* MakeRecipe(char name[], char desc[], int rating);

int AddIngredientAtIndex(Recipe* recipe, Ingredient ingredient, int index);
int AddIngredientAtFront(Recipe* recipe, Ingredient ingredient);
int AddIngredientAtBack(Recipe* recipe, Ingredient ingredient);

int RemoveIngredient(Ingredient *ingredient);
int RemoveIngredientAtIndex(Recipe* recipe, int index);
int RemoveIngredientAtFront(Recipe* recipe);
int RemoveIngredientAtBack(Recipe* recipe);
int ClearIngredients(Recipe* recipe);

int OrderByEssentiality(Recipe* recipe);
int OrderByLexicographic(Recipe* recipe);
int OrderByCount(Recipe* recipe);


RecipeDescriptor* MakeRecipeDescriptor();

Recipe* SelectRecipeAtIndex(RecipeDescriptor* recipeDescriptor, int index);
Recipe* SelectRecipeByName(RecipeDescriptor* RecipeDescriptor, char nome[]);

int AddRecipe(RecipeDescriptor* RecipeDescriptor, Recipe recipe);
int RemoveRecipe(RecipeDescriptor* descriptor, Recipe* recipe);
int RemoveRecipeAtIndex(RecipeDescriptor* descriptor, int index);

int OrderByRating(RecipeDescriptor* RecipeDescriptor);
int OrderByLexicographicDesc(RecipeDescriptor* RecipeDescriptor);
