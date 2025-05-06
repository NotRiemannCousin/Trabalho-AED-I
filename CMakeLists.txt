cmake_minimum_required(VERSION 3.29)
project(Maratonas)

set(CMAKE_C_STANDARD 17)

add_executable(Maratonas
        main.c
        Recipe.c
        Recipe.h
        Ingredient.c
        Ingredient.h
        Persistent.c
        Persistent.h
        Menu.c
        Menu.h
)
