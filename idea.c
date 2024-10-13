#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * get_file(FILE * fp)
{
    char * content;
    char buffer[10];

    content = malloc(sizeof(char));
    content[0] = '\0';

    while(fgets(buffer, 10, fp) != NULL)
    {
        content = realloc(content, (strlen(buffer) * sizeof(char)) + strlen(content) * sizeof(char));
        content = strcat(content, buffer);
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
    int i = 0;

    while(i < lines)
    {
        printf("%s\n", tab[i]);
        i++;
    }
}

int main()
{
    FILE *fp = fopen("sokoban.txt", "r");
    char * file_content;
    char **tab;
    int lines;
    char * line;
    int i = 0;

    if (fp == NULL)
    {
        printf("ERROR\n");
        return EXIT_FAILURE;
    }

    file_content = get_file(fp);
    
    lines = count_lines(file_content);

    tab = malloc(lines * sizeof(*tab));

    line = strtok(file_content, "\n");
    while((line != NULL) && (i < lines))
    {
        tab[i] = malloc(strlen(line) * sizeof(char));
        tab[i] = strcpy(tab[i], line);
        i++;

        line = strtok(NULL, "\n");
    }

    display_tab(tab, lines);

    i = 0;

      while(i < lines)
    {
        free(tab[i]);
        i++;
    }

    free(tab);
    
    fclose(fp);
    return 0;
}