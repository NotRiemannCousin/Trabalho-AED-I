#include <stdio.h>
#include "Recipe.h"
#include "Persistent.h"
#include "Menu.h"

int main() {
    RecipeDescriptor* book = MakeRecipeDescriptor();
    setvbuf(stdout, NULL, _IONBF, 0);

    char filename[] = "C:/Users/MARCE/CLionProjects/Maratonas/receitas.txt";
    LoadRecipesFromFile(book, filename);

    if (!book) {
        printf("Falha ao criar o Livro de Receitas.\n");
        return 1;
    }

    int option;
    do {
        Clear();
        ShowMainMenu();
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1: AddRecipeOp(book); getchar();     break;
            case 2: SelectRecipeOp(book); getchar();  break;
            case 3: ListRecipesOp(book); getchar();   break;
            case 4: OrderRecipesOp(book); getchar();  break;
            case 5: printf("Saindo...\n"); break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (option != 5);


    SaveRecipesToFile(book, filename);
    return 0;
}