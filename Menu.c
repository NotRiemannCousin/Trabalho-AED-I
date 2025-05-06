#include "Menu.h"
#include "Recipe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Clear() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void ShowMainMenu() {
    printf(
        "\n=== LIVRO DE RECEITAS ===\n"
        "1. Criar nova receita\n"
        "2. Selecionar receita\n"
        "3. Listar receitas\n"
        "4. Ordenar receitas\n"
        "5. Sair\n"
        "Escolha: ");
}


void AddRecipeOp(RecipeDescriptor* book) {
    char name[REC_NOME_LEN];
    char desc[REC_DESC_LEN];
    int rating;

    printf("Nome da receita: ");
    fgets(name, REC_NOME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Descricao: ");
    fgets(desc, REC_DESC_LEN, stdin);
    desc[strcspn(desc, "\n")] = '\0';

    printf("Avaliacao (1-5): ");
    scanf("%d", &rating);
    getchar();

    Recipe* newRecipe = MakeRecipe(name, desc, rating);
    if (!newRecipe) {
        printf("Falha ao criar a receita.\n");
        return;
    }
    printf("Receita criada com sucesso!\n");

    AddRecipe(book, *newRecipe);
    free(newRecipe);
}

void SelectRecipeOp(RecipeDescriptor* book) {
    if (book->count == 0) {
        printf("Nenhuma receita disponivel.\n");
        return;
    }

    printf("Receitas disponiveis:\n");
    int i = 0;
    for (Recipe* r = book->dummy->next; r != NULL; r = r->next)
        printf("%d. %s\n", ++i, r->name);
    printf("\n");

    Recipe* recipe = NULL;

    while (!recipe) {
        printf(
            "Selecionar por:\n"
            "1. Indice\n"
            "2. Nome\n"
            "Escolha: ");
        int opt;
        scanf("%d", &opt);
        getchar();

        switch (opt) {
            case 1:
                int index;
                scanf("%d", &index);
                getchar();
                recipe = SelectRecipeAtIndex(book, index);
                if (!recipe)
                    printf("Indice invalido!\n");
                break;
            case 2:
                char name[REC_NOME_LEN];
                fgets(name, REC_NOME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';

                recipe = SelectRecipeByName(book, name);
                if (!recipe)
                    printf("Receita nao encontrada.\n");
                break;
            default:
                printf("Opçao invalida!\n");
        }
    }
    ManageRecipeOp(recipe);
}



void ListRecipesOp(const RecipeDescriptor* book) {
    printf("\n=== LISTA DE RECEITAS ===\n");
    for (Recipe *curr = book->dummy->next; curr != NULL; curr = curr->next)
        printf("%s (Avaliacao: %d)\n", curr->name, curr->rating);
}

void OrderRecipesOp(RecipeDescriptor* book) {
    printf(
        "Ordenar por:\n"
        "1. Rating\n"
        "2. Ordem Alfabetica\n"
        "Escolha: ");

    while (1) {
        int opt;
        scanf("%d", &opt);
        getchar();

        switch (opt) {
            case 1:  OrderByRating(book);            break;
            case 2:  OrderByLexicographicDesc(book); break;
            default: printf("Opcao invalida!\n");    continue;
        }
        break;
    }
}




void ShowRecipeMenu() {
    printf(
        "\n=== MENU DE INGREDIENTES ===\n"
        "1. Adicionar ingrediente\n"
        "2. Remover ingrediente\n"
        "3. Listar ingredientes\n"
        "4. Ordenar ingredientes\n"
        "5. Listar ingredientes essensiais\n"
        "6. Sair\n"
        "Escolha: ");
}



void ManageRecipeOp(Recipe* recipe) {
    printf("\n\n");
    int option;
    do {
        printf("\t%s\n%s", recipe->name, recipe->desc);
        ShowRecipeMenu();
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1: AddIngredientOp(recipe); getchar();             break;
            case 2: RemoveIngredientOp(recipe); getchar();          break;
            case 3: ListIngredientsOp(recipe); getchar();           break;
            case 4: OrderIngredientsOp(recipe); getchar();          break;
            case 5: ListEssentialsIngredientsOp(recipe); getchar(); break;
            case 6: break;
            default: printf("Opcao invalida!\n");
        }
        printf("\n\n");
    } while (option != 6);
}

void AddIngredientOp(Recipe* recipe) {
    char name[ING_NAME_LEN];
    int essentiality, count;

    printf("Nome do ingrediente: ");
    fgets(name, ING_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Essencialidade (0=Baixa, 1=Normal, 2=Alta): ");
    scanf("%d", &essentiality);

    printf("Quantidade: ");
    scanf("%d", &count);
    getchar();

    Ingredient* ing = MakeIngredient(name, essentiality, count);

    printf(
        "Adicionar:\n"
        "1. Inicio\n"
        "2. Fim\n"
        "3. Posicao especifica\n"
        "Escolha: ");
    while(1) {
        int addOption;
        scanf("%d", &addOption);
        getchar();

        switch(addOption) {
            case 1: AddIngredientAtFront(recipe, *ing); getchar(); break;
            case 2: AddIngredientAtBack(recipe, *ing);  getchar(); break;
            case 3:
                printf("Posicao: ");
                int index;
                scanf("%d", &index);
                getchar();
                AddIngredientAtIndex(recipe, *ing, index);
                getchar();
                break;
            default:
                printf("Opcao invalida!");
                continue;
        }
        break;
    }
}

void RemoveIngredientOp(Recipe* recipe) {
    if(!recipe || recipe->ingredientCount == 0) {
        printf("Sem ingredientes pra remover!\n");
        return;
    }
    printf(
        "Remover:\n"
        "1. Inicio\n"
        "2. Fim\n"
        "3. Posicao especifica\n"
        "Escolha: ");

    while(1) {
        int removeOption;
        scanf("%d", &removeOption);
        getchar();

        switch(removeOption){
            case 1: RemoveIngredientAtFront(recipe); break;
            case 2: RemoveIngredientAtBack(recipe); break;
            case 3:
                printf("Posicao: ");
                int index;
                scanf("%d", &index);
                getchar();
                RemoveIngredientAtIndex(recipe, index);
                break;
            default:
                printf("Opcao invalida!");
            continue;
        }
        break;
    }
}

void ListIngredientsOp(const Recipe* recipe){
    if(!recipe || recipe->ingredientCount == 0) {
        printf("Sem ingredientes pra listar!\n");
        return;
    }
    printf("Ingredientes:\n");
    for (Ingredient* curr = recipe->dummyFront->next; curr != recipe->dummyBack; curr = curr->next)
        printf("\t- %s (Essencialidade: %d, Quantidade: %d)\n", curr->name, curr->essentiality, curr->count);
}

void OrderIngredientsOp(Recipe* recipe){
    if(!recipe || recipe->ingredientCount == 0) {
        printf("Sem ingredientes pra ordenar!\n");
        return;
    }
    printf(
        "Ordenar por:\n"
        "1. Nivel de essencialidade\n"
        "2. Ordem alfabetica\n"
        "3. Quantidade\n"
        "Escolha: ");

    while(1) {
        int removeOption;
        scanf("%d", &removeOption);
        getchar();

        switch(removeOption){
            case 1:  OrderByEssentiality(recipe);  break;
            case 2:  OrderByLexicographic(recipe); break;
            case 3:  OrderByCount(recipe);         break;
            default: printf("Opcao invalida!");    continue;
        }
        break;
    }
}

void ListEssentialsIngredientsOp(const Recipe* recipe){
    if(!recipe || recipe->ingredientCount == 0) {
        printf("Sem ingredientes pra listar!\n");
        return;
    }
    printf("Ingredientes:\n");
    for (Ingredient* curr = recipe->dummyFront->next; curr != recipe->dummyBack; curr = curr->next)
        if(curr->essentiality == ESSENTIALITY_HIGH)
            printf("\t- %s (Essencialidade: %d, Quantidade: %d)\n", curr->name, curr->essentiality, curr->count);
}
