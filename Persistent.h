#pragma once
#include "Recipe.h"

int SaveRecipesToFile(RecipeDescriptor* descriptor, const char* filename);

int LoadRecipesFromFile(RecipeDescriptor* descriptor, const char* filename);
