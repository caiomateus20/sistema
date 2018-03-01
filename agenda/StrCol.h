
typedef struct _strcol
{
    int cont;
    int blocos;
    char** lista;
} StrCol;


void inicia_col(StrCol *col);
void insere_string(StrCol *col, char *s);
void remove_string(StrCol *col, int indice);
void libera_col(StrCol *col);
int tamanho_col(StrCol *col);
void le_string(StrCol *col, int indice, char *str);
