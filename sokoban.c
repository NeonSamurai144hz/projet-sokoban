#include <stdio.h>
#include <stdlib.h>

int main(){
    char tab[10][10] = {};

        FILE *fp = fopen("sokoban.txt", "r+");

    if (fp == NULL)
    {
        printf("Le fichier sokoban.txt n a pas pu etre ouvert\n");
        return EXIT_FAILURE;
    }

    
    return 0;
    

    return 0;
}