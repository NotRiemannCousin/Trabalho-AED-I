#include "Persistent.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int SaveRecipesToFile(RecipeDescriptor* descriptor, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return -1;

    for (Recipe* r = descriptor->dummy->next; r; r = r->next) {
        fprintf(f, "RECIPE;%s;%s;%d\n", r->name, r->desc, r->rating);
        for (Ingredient* i = r->dummyFront->next; i != r->dummyBack; i = i->next)
            fprintf(f, "INGREDIENT;%s;%d;%d\n", i->name, i->essentiality, i->count);
    }

    fclose(f);
    return 0;
}

int LoadRecipesFromFile(RecipeDescriptor* descriptor, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        char name[128], desc[256];
        int rating;
        sscanf(line, "RECIPE;%127[^;];%255[^;];%d", name, desc, &rating);
        Recipe* recipe = MakeRecipe(name, desc, rating);

        while (fgets(line, sizeof(line), f) && strncmp(line, "INGREDIENT;", 10) == 0) {
            int ess, count;
            sscanf(line, "INGREDIENT;%127[^;];%d;%d", name, &ess, &count);
            Ingredient* ing = MakeIngredient(name, (Essentiality)ess, count);
            AddIngredientAtBack(recipe, *ing);
            free(ing);
        }

        AddRecipe(descriptor, *recipe);

        if (!feof(f)) fseek(f, -strlen(line), SEEK_CUR);
    }

    fclose(f);
    return 0;
}

