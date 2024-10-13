#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void DrawBoard()
{
    for(int y=0; y<18; y++)
        for(int x=0; x<26; x++)
            if(y==0)
                if(x==25)       printf(" \n");
                else if(x%3==2) putchar(65+(x/3));   
                else            putchar(' ');
            else if (y==1)
                if(x==0)        putchar(' ');
                else if(x==1)   putchar(218);
                else if(x==25)  printf("%c\n", 191);
                else if(x%3==1) putchar(194); 
                else            putchar(196);
            else if(y==17)
                if(x==0)        putchar(' ');
                else if(x==1)   putchar(192);
                else if(x==25)  printf("%c\n", 217);
                else if(x%3==1) putchar(193); 
                else            putchar(196);
            else if(y%2==1)
                if(x==0)        putchar(' ');
                else if(x==1)   putchar(195);
                else if(x==25)  printf("%c\n", 180);
                else if(x%3==1) putchar(197); 
                else            putchar(196);
            else
                if (x==0)       putchar(48+(y/2));
                else if(x==25)  printf("%c\n", 179);
                else if(x%3==1) putchar(179); 
                else if(x%3==2) printf("X");;// <- Cell content goes here
}

int main() {
    DrawBoard;

    exit(0);
}