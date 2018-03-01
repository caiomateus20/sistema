#include <stdio.h>
#include <string.h>
#include "StrCol.h"

void inicia_col(StrCol *col)
{
    col->cont = 0;
    col->blocos = 1;
    col->lista = (char**) malloc(10*sizeof(char*));
}

void insere_string(StrCol *col, char *s)
{
    int numStr = strlen(s)+1;

    if(col->cont/col->blocos < 9)
    {
        col->lista[col->cont] = (char*) malloc(numStr*sizeof(char));
        if (col->lista == NULL)
        {
            printf ("Não há memoria suficiente!\n");
            system ("pause");
            exit(0);
        }
        strcpy(col->lista[col->cont],s);
        col->cont++;
    }
    else
    {

        col->blocos++;
        col->lista = (char**) realloc(col->lista, (col->blocos*10) *sizeof(char*));

        if (col->lista == NULL)
        {
            printf ("Não há memoria suficiente!\n");
            system ("pause");
            exit(0);
        }
        col->lista[col->cont] = (char*) malloc(numStr*sizeof(char));

        strcpy(col->lista[col->cont],s);
        col->cont++;
    }
}

void lista_String (StrCol *col)
{

    int i, j;

    for (i=0; i < col->cont; i++)
    {

        for (j=0; col->lista[i][j] != '\0'; j++)
        {
            printf ("%c", col->lista[i][j]);
        }

        printf ("\n");

    }

}

void remove_string(StrCol *col, int indice)
{

    free(col->lista[indice]);

    for(; indice < col->cont; indice++)
        col->lista[indice] = col->lista[indice+1];

    col->cont--;
}

void libera_col(StrCol *col)
{
    for(; col->cont >= 0; col->cont--)
        free(col->lista[col->cont]);

    free(col);
}

int tamanho_col(StrCol *col)
{
    return col->cont;
}

void le_string(StrCol *col, int indice, char *str)
{
    printf("indice:::::%d",indice);
    int i;
    for(i=0; col->lista[indice][i]!= '\0'; i++)
        str[i] = col->lista[indice][i];
}

