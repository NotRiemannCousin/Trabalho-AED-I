#include <stdlib.h>
#include <string.h>
#include "Recipe.h"

Recipe* MakeRecipe(char name[], char desc[], int rating) {
    Recipe* newRecipe = (Recipe*)malloc(sizeof(Recipe));
    if (newRecipe == NULL) return NULL;

    strncpy(newRecipe->name, name, REC_NOME_LEN - 1);
    newRecipe->name[REC_NOME_LEN - 1] = '\0';
    strncpy(newRecipe->desc, desc, REC_DESC_LEN - 1);
    newRecipe->desc[REC_DESC_LEN - 1] = '\0';
    newRecipe->rating = rating;

    newRecipe->dummyFront = MakeIngredient("___DummyFront___", ESSENTIALITY_NORMAL, -1);
    newRecipe->dummyBack  = MakeIngredient("___DummyBack___", ESSENTIALITY_NORMAL, -1);
    newRecipe->dummyFront->next = newRecipe->dummyBack;
    newRecipe->dummyBack->last  = newRecipe->dummyFront;

    newRecipe->ingredientCount = 0;

    newRecipe->next = NULL;

    return newRecipe;
}

int AddIngredientAtIndex(Recipe* recipe, Ingredient ingredient, int index) {
    if(!recipe) return -1;

    Ingredient *target = recipe->dummyFront;
    int i = 0;

    // Traverse the list to find the correct position
    while(i < index && target->next != recipe->dummyBack) {
        target = target->next;
        i++;
    }

    Ingredient* ing = MakeIngredient(ingredient.name, ingredient.essentiality, ingredient.count);
    ing->next = target->next;
    ing->last = target;

    if(target->next) {
        target->next->last = ing;
    }

    target->next = ing;
    recipe->ingredientCount++;

    return 0;
}

int AddIngredientAtFront(Recipe* recipe, Ingredient ingredient) {
    return AddIngredientAtIndex(recipe, ingredient, 0);
}

int AddIngredientAtBack(Recipe* recipe, Ingredient ingredient) {
    return AddIngredientAtIndex(recipe, ingredient, recipe->ingredientCount);
}



int RemoveIngredient(Recipe* recipe, Ingredient* ingredient) {
    if(!recipe) return -1;

    Ingredient *target = recipe->dummyFront->next;

    while(target != recipe->dummyBack && target != ingredient)
        target++;

    if(target == recipe->dummyBack)
        return -1;

    target->next->last = target->last;
    target->last->next = target->next;

    free(target->name);
    free(target);

    return 0;
}

int RemoveIngredientAtIndex(Recipe* recipe, int index) {
    if(!recipe) return -1;

    Ingredient *target = recipe->dummyFront->next;
    int i = 0;
    while(i < index && target != recipe->dummyBack)
        i++, target++;

    if(i != index || target == recipe->dummyBack)
        return -1;

    target->next->last = target->last;
    target->last->next = target->next;

    free(target->name);
    free(target);

    return 0;
}

int RemoveIngredientAtFront(Recipe* recipe) {
    return RemoveIngredientAtIndex(recipe, 0);
}

int RemoveIngredientAtBack(Recipe* recipe) {
    return RemoveIngredientAtIndex(recipe, recipe->ingredientCount - 1);
}

int ClearIngredients(Recipe* recipe) {
    Ingredient* target = recipe->dummyFront->next;
    Ingredient* next   = recipe->dummyFront->next->next;

    for(; target != recipe->dummyBack; target = next, next = next->next) {
        free(target->name);
        free(target);
    }

    return 0;
}



static int CompareByEssentiality(const Ingredient* a, const Ingredient* b) {
    return (int)b->essentiality - (int)a->essentiality;
}

static int CompareByName(const Ingredient* a, const Ingredient* b) {
    return strcmp(a->name, b->name) > 0;
}

static int CompareByCount(const Ingredient* a, const Ingredient* b) {
    return b->count - a->count > 0;
}

typedef int (*IngredientCompareFn)(const Ingredient*, const Ingredient*);


static int OrderIngredientsBy(Recipe* recipe, IngredientCompareFn cmp) {
    if (!recipe || recipe->ingredientCount <= 1) return -1;

    for (int i = 0; i < recipe->ingredientCount - 1; i++) {
        Ingredient* prev = recipe->dummyFront;
        Ingredient* a = prev->next;
        Ingredient* b = a->next;

        for (int j = 0; j < recipe->ingredientCount - 1 - i; j++) {
            if (cmp(a, b)) {
                a->next = b->next;
                b->next = a;
                prev->next = b;
                a = b;
            }
            prev = prev->next;
            a = prev->next;
            if (!a || !a->next) break;
            b = a->next;
        }
    }
    return 0;
}

int OrderByEssentiality(Recipe* recipe) {
    return OrderIngredientsBy(recipe, CompareByEssentiality);
}

int OrderByLexicographic(Recipe* recipe) {
    return OrderIngredientsBy(recipe, CompareByName);
}

int OrderByCount(Recipe* recipe) {
    return OrderIngredientsBy(recipe, CompareByCount);
}







RecipeDescriptor* MakeRecipeDescriptor() {
    RecipeDescriptor* descriptor =(RecipeDescriptor*)malloc(sizeof(RecipeDescriptor));
    if(!descriptor) return NULL;
    descriptor->count = 0;
    descriptor->dummy = MakeRecipe("__Dummy__", "aroace", -1);

    return descriptor;
}


Recipe* SelectRecipeAtIndex(RecipeDescriptor* recipeDescriptor, int index) {
    if(!recipeDescriptor || index < 0 || index >= recipeDescriptor->count)
        return NULL;

    Recipe* curr = recipeDescriptor->dummy->next;

    for(int i = 0; i < index; i++)
        curr = curr->next;

    return curr;
}

Recipe* SelectRecipeByName(RecipeDescriptor* RecipeDescriptor, char name[]) {
    if(!RecipeDescriptor) return NULL;

    for(Recipe* curr = RecipeDescriptor->dummy->next; curr; curr = curr->next)
        if(strcmp(name, curr->name) == 0)
            return curr;

    return NULL;
}



int AddRecipe(RecipeDescriptor* descriptor, Recipe recipe) {
    if (!descriptor) return -1;

    Recipe* newRecipe = MakeRecipe(recipe.name, recipe.desc, recipe.rating);
    if (!newRecipe) return -1;

    for (Ingredient* curr = recipe.dummyFront->next; curr != recipe.dummyBack; curr = curr->next) {
        Ingredient* ing = MakeIngredient(curr->name, curr->essentiality, curr->count);
        AddIngredientAtBack(newRecipe, *ing);
        free(ing);
    }

    Recipe* current = descriptor->dummy;
    while (current->next)
        current = current->next;

    current->next = newRecipe;
    descriptor->count++;

    return 0;
}


int RemoveRecipeAtIndex(RecipeDescriptor* descriptor, int index) {
    if (!descriptor || index < 0 || index >= descriptor->count) return -1;

    Recipe* prev = descriptor->dummy;
    int i = 0;
    while (i < index && prev->next) {
        prev = prev->next;
        i++;
    }

    Recipe* toRemove = prev->next;
    if (!toRemove) return -1;

    prev->next = toRemove->next;
    ClearIngredients(toRemove);
    free(toRemove);

    descriptor->count--;

    return 0;
}



static int CompareByRating(const Recipe* a, const Recipe* b) {
    return a->rating - b->rating < 0;
}

static int CompareByNameDesc(const Recipe* a, const Recipe* b) {
    return strcmp(b->name, a->name) < 0;
}

typedef int (*RecipeComparatorFn)(const Recipe*, const Recipe*);


static int OrderByDesc(RecipeDescriptor* descriptor, RecipeComparatorFn cmp) {
    if (!descriptor || descriptor->count <= 1) return - 1;

    for (int i = 0; i < descriptor->count - 1; i++) {
        Recipe* prev = descriptor->dummy;
        Recipe* a = prev->next;
        Recipe* b = a->next;

        for (int j = 0; j < descriptor->count - 1 - i; j++) {
            if (cmp(a, b)) {
                a->next = b->next;
                b->next = a;
                prev->next = b;
                a = b;
            }
            prev = prev->next;
            a = prev->next;
            if (!a || !a->next) break;
            b = a->next;
        }
    }
    return 0;
}

int OrderByRating(RecipeDescriptor* descriptor){
    return OrderByDesc(descriptor, CompareByRating);
}

int OrderByLexicographicDesc(RecipeDescriptor* descriptor) {
    return OrderByDesc(descriptor, CompareByNameDesc);
}
