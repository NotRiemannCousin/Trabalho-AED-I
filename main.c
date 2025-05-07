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
            case 1: AddRecipeOp(book); getchar();    break;
            case 2: RemoveRecipeOp(book);            break;
            case 3: SelectRecipeOp(book);            break;
            case 4: ListRecipesOp(book); getchar();  break;
            case 5: OrderRecipesOp(book);            break;
            case 6: printf("Saindo...\n"); break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (option != 6);


    SaveRecipesToFile(book, filename);
    return 0;
}