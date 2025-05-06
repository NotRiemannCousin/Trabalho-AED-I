#pragma once
#include "Menu.h"
#include "Recipe.h"


void Clear();

// =============================    Menus    =============================
void ShowMainMenu();
void ShowRecipeMenu();

// =============================    Menus    =============================
void ManageRecipeOp(Recipe* recipe);
void AddIngredientOp(Recipe* recipe);
void RemoveIngredientOp(Recipe* recipe);
void ListIngredientsOp(const Recipe* recipe);
void OrderIngredientsOp(Recipe* recipe);
void ListEssentialsIngredientsOp(const Recipe* recipe);

// =============================    main    =============================
void AddRecipeOp(RecipeDescriptor* book);
void SelectRecipeOp(RecipeDescriptor* book);
void ListRecipesOp(const RecipeDescriptor* book);
void OrderRecipesOp(RecipeDescriptor* book);
