#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "StrCol.h"
#define BLOCK 10

typedef struct _contato
{
    char nome[50];
    StrCol tel;
    StrCol mail;
} contato;

int id = 0;
contato **agenda;

void Listar_contatos(void);
void Inserir_contato(void);
void Remover_contato(void);
void Editar_contato(void);
void Limpar_agenda(void);

void Alocacao_Memoria(void)
{
    if (agenda == NULL)
        agenda = (contato**) malloc (BLOCK * sizeof (contato*));

    if (agenda == NULL)
    {
        printf ("Não há memoria suficiente!");
        system ("pause");
        exit(0);
    }
    if (id != 0 && id%BLOCK == 0)
    {
        agenda = (contato**) realloc(agenda, (id+BLOCK) * sizeof (contato*));
    }
    agenda[id] = (contato*) malloc (sizeof (contato));

}


void main(void)
{
    setlocale (LC_ALL, "");



    int resp;


    do
    {
        printf ("\n---------------------------------------------------------");
        printf ("\n\t\t\tMENU");
        printf ("\n---------------------------------------------------------");
        printf ("\n\nO que você deseja fazer?\n\n");
        printf ("1 - Inserir Contato\n\n");
        printf ("2 - Listar Contatos\n\n");
        printf ("3 - Remover Contato\n\n");
        printf ("4 - Editar Contato\n\n");
        printf ("5 - Limpar toda a agenda\n\n");
        printf ("6 - Encerrar o programa\n\n");
        printf ("Digite um número: ");

        scanf ("%i", &resp);

        switch (resp)
        {
        case 1:
        {
            printf ("\n---------------------------------------------------------\n\n");
            Inserir_contato();
            break;
        }

        case 2:
        {
            printf ("\n---------------------------------------------------------\n\n");
            Listar_contatos();
            break;
        }

        case 3:
        {
            printf ("\n---------------------------------------------------------\n\n");
            Remover_contato();
            break;
        }

        case 4:
        {
            printf ("\n---------------------------------------------------------\n\n");
            Editar_contato();
            break;
        }

        case 5:
        {
            printf ("\n---------------------------------------------------------\n\n");
            Limpar_agenda();
            break;
        }


        case 6:
        {
            resp = 6;
            break;
        }

        default:
            printf("\n\nNúmero Inválido!");
        }


    }
    while (resp != 6);


    printf("\n\n\n\n");
}

void Listar_contatos(void)
{
    if(id == 0)
    {
        puts ("\n\nNão há nenhum contato cadastrado!\n\n\n");
        return;
    }

    int i;

    for(i = 0; i<id; i++)
    {
        printf("%d: %s\n",i+1, agenda[i]->nome);

        printf("Telefone(s)\n");
        lista_String(&agenda[i]->tel);
        putchar('\n');

        printf("E-mail(s)\n");
        lista_String(&agenda[i]->mail);
        putchar('\n');
        printf("---------------------\n");
    }

    printf ("\n\n----------------Fim dos Contatos------------------\n\n\n\n");
}

void Inserir_contato(void)
{
    char tel[30], mail[30];
    int i, end, j;

    printf ("\n\n\t\t\tInserir Contato\n\n\n");
    Alocacao_Memoria();

    printf("\n\nDigite o nome o contato (até 50 caracteres): ");
    fflush(stdin);
    gets(agenda[id]->nome);
    fflush(stdin);

    inicia_col(&agenda[id]->tel);
    inicia_col(&agenda[id]->mail);

    while(1)
    {
        printf ("\n\n----->Digite o nº do telefone deste contato (-1 para parar): ");
        gets(tel);
        fflush(stdin);
        if(!strcmp(tel,"-1"))
            break;

        insere_string(&agenda[id]->tel, &tel);
    }
    while(1)
    {
        printf ("\n\n----->Digite o e-mail deste contato (-1 para parar): ");
        gets(mail);
        fflush(stdin);
        if(!strcmp(mail,"-1"))
            break;

        insere_string(&agenda[id]->mail, &mail);
    }

    for(i=id; i > 0; i--)
    {
        if(id == 0)
            break;
        if(0 <= strcasecmp(agenda[i]->nome,agenda[i-1]->nome))
            break;

        end = agenda[i];
        agenda[i] = agenda[i-1];
        agenda[i-1] = end;


    }
    id++;

    printf ("\n\n\nDados Cadastrados com Sucesso!\n\n\n");


    printf ("-------------------------------------------------------------");
}

void Remover_contato(void)
{
    printf ("\n\n\t\t\tRemover Contato\n\n\n");

    int i,indice;

    if (id == 0)
    {
        puts ("\n\nNão há nenhum contato cadastrado!\n\n\n");
        return;
    }


    printf ("\n\nSegue-se os contatos cadastrados abaixo\n\n\n");
    Listar_contatos();

    do
    {
        printf ("\n\n\n-----> Digite o nº do Contato para deletar: ");
        scanf ("%d", &indice);
    }
    while(indice > id || indice-1 < 0);
    indice--;
    free(agenda[indice]);
    for(; indice<id; indice++)
        agenda[indice] = agenda[indice+1];
    agenda = (contato**) realloc(agenda, (id-1) * BLOCK * sizeof (contato*));
    id--;

    printf ("\n\n\nContato Removido com Sucesso!\n\n\n");
}

void Editar_contato(void)
{
    int indice, indiceCol;
    int resp;
    Listar_contatos();
    if(id == 0)
    {
        return;
    }
    else
    {
        do
        {
            printf("Digite o indice que deseja alterar:");
            scanf("%d",&indice);
            indice--;
        }
        while(!(indice < id && indice >= 0));

        printf ("\n---------------------------------------------------------");
        printf ("\n\t\t\tMENU");
        printf ("\n---------------------------------------------------------");
        printf ("\n\nO que você deseja fazer?\n\n");
        printf ("1 - Inserir Telefone\n\n");
        printf ("2 - Remover Telefone\n\n");
        printf ("3 - Inserir Email\n\n");
        printf ("4 - Remover Email\n\n");
        printf ("5 - Voltar\n\n");
        printf ("Digite um número: ");
        scanf ("%i", &resp);
        fflush(stdin);
        switch (resp)
        {

        case 1:
        {
            char telefone[30];

            printf("Digite o telefone:");
            gets(telefone);
            fflush(stdin);
            insere_string(&agenda[indice]->tel,&telefone);

            break;
        }

        case 2:
        {
            int tamanhoCol = tamanho_col(&agenda[indice]->tel);
                printf("%d",tamanhoCol);
            do{
                printf("Digite o indice do telefone a ser removido: ");
                scanf("%d", &indiceCol);
            indiceCol--;
            }while(indiceCol >= tamanhoCol || indiceCol < 0);

            remove_string(&agenda[indice]->tel,indiceCol);
                printf("Telefone removido com sucesso!");

            break;
        }

        case 3:
        {
            char email[30];

            printf("Digite o E-mail:");
            gets(email);
            fflush(stdin);
            insere_string(&agenda[indice]->mail,&email);

            break;
        }
        case 4:
        {
            int tamanhoCol = tamanho_col(&agenda[indice]->tel);
            do{
                printf("Digite o indice do e-mail a ser removido: ");
                scanf("%d", &indiceCol);
            indiceCol--;
            }while(indiceCol >= tamanhoCol || indiceCol < 0);

            remove_string(&agenda[indice]->mail,indiceCol);
                printf("E-mail removido com sucesso!");
        }
        case 5:
        {
            break;
        }
        default:
            printf("\n\nNúmero Inválido!");
        }
    }
}

void Limpar_agenda()
{
    int result;
    int  i, j;


    printf ("\n\n\t\t\tLimpar Agenda\n\n\n");

    do
    {
        printf ("\n\n\tDeseja realmente limpar agenda? 1 - Sim / 2 - Não\n\nDigite: ");
        scanf ("%d", &result);
    }
    while(result != 1 && result != 2);

    if (result == 2)
    {

        printf ("\n\n\n");
        return;

    }

    for (i = 0; i < id; i++)
    {
        libera_col(&agenda[i]->tel);
        libera_col(&agenda[i]->mail);

        free (agenda[i]);
    }

    free (agenda);
    agenda = NULL;

    id = 0;

    printf ("\n\n\n\n\tA agenda foi limpa com sucesso!\n\n\n\n");


}
