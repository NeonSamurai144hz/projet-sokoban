#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <time.h>
#include <string.h>

char * get_file(FILE * fp)
{
    char * content;
    char buffer[10];

    content = malloc(1);
    content[0] = '\0';

    while(fgets(buffer, 10, fp) != NULL)
    {
        content = realloc(content, strlen(content) + strlen(buffer) + 1);
        strcat(content, buffer);
    }

    return content;
}

int count_lines(char *str)
{
    int i = 0;
    int lines = 0;

    while(str[i] != '\0')
    {
        if(str[i] == '\n')
        {
            lines++;
        }

        i++;
    }

    return lines;
}

void display_tab(char **tab, int lines)
{
    for (int i = 0; i < lines; i++) 
    {
        printf("%s\n", tab[i]);
    }
}

int check_win(char **tab, position2 pos2, position3 pos3) 
{
    return (pos2.Boite_x == pos3.obj_x && pos2.Boite_y == pos3.obj_y);
}

int check_lose(char **tab, position2 pos2) 
{
    int x = pos2.Boite_x;
    int y = pos2.Boite_y;
    
    if ((x > 0 && tab[x - 1][y] == '#') && 
        (x < 8 - 1 && tab[x + 1][y] == '#') &&
        (y > 0 && tab[x][y - 1] == '#') && (y < strlen(tab[0]) - 1 && tab[x][y + 1] == '#'))
        {

        return 1;

        }

    return 0;
}

void clean_up(char **tab, char *file_content, int lines)
{
    for (int i = 0; i < lines; i++) {
        free(tab[i]);
    }
    free(tab);
    free(file_content);
}

void clear_console()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main()
{
    system("clear");
    srand(time(NULL));

    char player = 'o';
    char Boite = '$';
    char objectif = '.';

    position pos1;  
    position2 pos2;
    position3 pos3;

    pos1.joueur_y = rand() % 8 + 1;  
    pos1.joueur_x = rand() % 8 + 1; 
    pos2.Boite_y = rand() % 6 + 2;  
    pos2.Boite_x = rand() % 6 + 2;
    pos3.obj_y = rand() % 8 + 1;  
    pos3.obj_x = rand() % 8 + 1;

    
    FILE *fp = fopen("sokoban.txt", "r");
    if(fp == NULL) 
    {
        printf("ERROR: could not open sokoban.txt\n");
        return EXIT_FAILURE;
    }

    char *file_content = get_file(fp);
    fclose(fp);
    int lines = count_lines(file_content);

    char **tab = malloc(lines * sizeof(*tab));
    char *line = strtok(file_content, "\n");

    for(int i = 0; i < lines && line != NULL; i++)
    {
        tab[i] = malloc(strlen(line) + 1);
        strcpy(tab[i], line);
        line = strtok(NULL, "\n");
    }

    tab[pos1.joueur_x][pos1.joueur_y] = player;
    tab[pos2.Boite_x][pos2.Boite_y] = Boite;
    tab[pos3.obj_x][pos3.obj_y] = objectif;

        printf("Joueur: %d % d\n", pos1.joueur_y, pos1.joueur_x);
        printf("Boite: %d %d\n", pos2.Boite_y, pos2.Boite_x);
        printf("Objectif: %d %d\n", pos3.obj_y, pos3.obj_x);
        
         while(1)
        {
            display_tab(tab, lines);
        
        if (check_win(tab, pos2, pos3)) {
            printf("Vous avez gagne! La boite est sur l'objectif.\n");
            break;
        }

        if (check_lose(tab, pos2)) {
            printf("Vous avez perdu! La boite est bloquee.\n");
            break;
        }

            printf("Choisissez un mouvment: haut(w) bas(s) gauche(a) droite(d)\n");
            char  move;
            scanf("%c", &move);

         int next_x = pos1.joueur_x;
        int next_y = pos1.joueur_y;

        if (move == 'w') {
            next_x--;
        } else if (move == 's') {
            next_x++;
        } else if (move == 'a') {
            next_y--;
        } else if (move == 'd') {
            next_y++;
        } else {
            printf("La touche n est pas un des mouvements\n");
            continue;
        }

        
        if (tab[next_x][next_y] != '#') 
        {
            
            if (next_x == pos2.Boite_x && next_y == pos2.Boite_y) 
            {
              
                int Boite_next_x = pos2.Boite_x;
                int Boite_next_y = pos2.Boite_y;

                if (move == 'w') {
                    Boite_next_x--;
                } else if (move == 's') {
                    Boite_next_x++;
                } else if (move == 'a') {
                    Boite_next_y--;
                } else if (move == 'd') {
                    Boite_next_y++;
                }

                
                if (tab[Boite_next_x][Boite_next_y] != '#' && 
                    (Boite_next_x != pos3.obj_x || Boite_next_y != pos3.obj_y)) 
                    {
                    
                    tab[pos2.Boite_x][pos2.Boite_y] = ' ';
                    pos2.Boite_x = Boite_next_x;
                    pos2.Boite_y = Boite_next_y;
                    tab[pos2.Boite_x][pos2.Boite_y] = Boite;
                } else 
                {
                    printf("Vous ne pouvez pas pousser la Boite dans cette direction.\n");
                }
            }

            
            tab[pos1.joueur_x][pos1.joueur_y] = ' ';
            pos1.joueur_x = next_x;
            pos1.joueur_y = next_y;
            tab[pos1.joueur_x][pos1.joueur_y] = player;
        } else {
            printf("Vous ne pouvez pas vous déplacer dans cette direction.\n");
        }
    }

    for (int i = 0; i < lines; i++)
    {
        free(tab[i]);
    }

    clean_up(tab, file_content, lines);

    return 0;
}
