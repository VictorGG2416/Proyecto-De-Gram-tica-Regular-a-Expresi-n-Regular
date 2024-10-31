#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
typedef struct
{
    char name[N], c;
} TDato;
typedef struct node
{
    struct node *next, *prev;
    TDato dato;
} TnodeD;
TnodeD *crearN(TDato dato);
TnodeD *crearN(TDato dato)
{
    TnodeD *nuevo = (TnodeD *)malloc(sizeof(TnodeD));
    nuevo->next = nuevo->prev = nuevo;
    strcpy(nuevo->dato.name, dato.name);
    nuevo->dato.c = dato.c;
    return nuevo;
}
void inicializarlista(TnodeD **cent);
void inicializarlista(TnodeD **cent)
{
    TDato dato = {"\0", 0};
    *cent = crearN(dato);
    (*cent)->next = (*cent)->prev = *cent;
}
void insertarnodo(TnodeD *nuevo, TnodeD *cent);
void insertarnodo(TnodeD *nuevo, TnodeD *cent)
{
    nuevo->next = cent;
    nuevo->prev = cent->prev;
    cent->prev->next = nuevo;
    cent->prev = nuevo;
}
void insertar(TnodeD *cent, TDato dato);
void insertar(TnodeD *cent, TDato dato)
{
    TnodeD *nuevo = crearN(dato);
    insertarnodo(nuevo, cent);
}
void removeblanks(char *name);
void removeblanks(char *name)
{
    int i, j = 0;
    for (i = 0; i < (int)strlen(name); i++)
        if (name[i] != ' ')
            name[j++] = name[i];
    name[j] = '\0';
}
void separacadena(char *name, TDato *dato);
void separacadena(char *name, TDato *dato)
{
    int i, j = 0;
    dato->c = name[0];
    for (i = 3; i < (int)strlen(name); i++)
        dato->name[j++] = name[i];
    dato->name[j] = '\0';
}
void lecturaGR(char *name, TnodeD *cent);
void lecturaGR(char *name, TnodeD *cent)
{
    FILE *fgr;
    char linea[N];
    TDato dato;
    fgr = fopen(name, "r");
    while (!feof(fgr))
    {
        fscanf(fgr, " %[^\n]", linea);
        removeblanks(linea);
        separacadena(linea, &dato);
        insertar(cent, dato);
    }
    fclose(fgr);
}
void imprimir(TnodeD *cent);
void imprimir(TnodeD *cent)
{
    TnodeD *actual;
    for (actual = cent->next; actual != cent; actual = actual->next)
        printf(" %c %s\n", actual->dato.c, actual->dato.name);
    printf("\n");
}
void OR(char *str1, char *str2);
void OR(char *str1, char *str2)
{
    int i, j = 1, strsize = strlen(str1);
    str1[strsize] = '|';
    for (i = 0; i < (int)strlen(str2); i++)
        str1[strsize + j++] = str2[i];
    str1[strsize + j] = '\0';
}
void comprimir(TnodeD *cent);
void comprimir(TnodeD *cent)
{
    TnodeD *i, *j;
    char start = cent->next->dato.c;
    for (i = j = cent->next->next; i != cent; i = i->next)
        if (start != i->dato.c)
        {
            strcpy(j->dato.name, i->dato.name);
            j->dato.c = start = i->dato.c;
            j = j->next;
        }
    j = j->prev;
    i = cent->prev;
    while (i != j)
    {
        i = i->prev;
        free(i->next);
    }
    cent->prev = j;
    j->next = cent;
}
void agrupacion(TnodeD *cent);
void agrupacion(TnodeD *cent)
{
    TnodeD *i, *j;
    for (i = cent->next; i != cent; i = j)
        for (j = i->next; j != cent && i->dato.c == j->dato.c; j = j->next)
            OR(i->dato.name, j->dato.name);
    comprimir(cent);
}
char *strchrpos(char *str, char c, int pos);
char *strchrpos(char *str, char c, int pos)
{
    int i;
    char *cut = strchr(str, c),*cpy=NULL;
    if (cut)
    {
        cpy = strdup(cut);
        for (i = pos; i <= (int)strlen(cpy); i++)
            cpy[i - pos] = cpy[i];
    }
    return cpy;
}
void agregarllaves(TnodeD *actual);
void agregarllaves(TnodeD *actual)
{
    char *cut = strchrpos(actual->dato.name,actual->dato.c,1);
    if(!cut)
        return;
    int pos,i;
    char beforeChar[N],*or1,*or2;
    or1=strchr(actual->dato.name,'|');
    or2=strrchr(actual->dato.name,'|');
    if(or1!=or2)
    {
        cut[0]='(';
        cut[strlen(cut)]=')';
        cut[strlen(cut)+1]='\0';
    }
    if(or1==or2)
        for (i = 1; i <= (int)strlen(cut); i++)
            cut[i - 1] = cut[i];
    for (pos = 0; pos<(int)strlen(actual->dato.name) && actual->dato.name[pos] != actual->dato.c; pos++)
        beforeChar[pos]=actual->dato.name[pos];
    beforeChar[pos]='\0';
    actual->dato.name[1]='\0';
    actual->dato.name[0]='{';
    strcat(actual->dato.name,beforeChar);
    pos=strlen(actual->dato.name);
    actual->dato.name[pos]='}';
    actual->dato.name[pos+1]='\0';
    strcat(actual->dato.name,cut);
}
void cambiarOR(TnodeD *cent);
void cambiarOR(TnodeD *cent)
{
    TnodeD *i;
    for (i = cent->next; i != cent; i = i->next)
        agregarllaves(i);
}
void cambioLetra(TnodeD *dest, TnodeD *org, char *cut);
void cambioLetra(TnodeD *dest, TnodeD *org, char *cut)
{
    int pos;
    for (pos = 0; dest->dato.name[pos] != org->dato.c; pos++);
    dest->dato.name[pos]='\0';
    strcat(dest->dato.name, org->dato.name);
    strcat(dest->dato.name, cut);
}
void sustitucion(TnodeD *cent);
void sustitucion(TnodeD *cent)
{
    TnodeD *i=cent->next, *j=i->next;
    char *cut;
    for (i = cent->next; i != cent; i = i->next)
        for (j = i->next; j != cent; j = j->next)
        {
            cut = strchrpos(j->dato.name, i->dato.c, 1);
            if (cut)
            {
                cambioLetra(j, i, cut);
                agregarllaves(j);
                free(cut);
            }
        }
    for (i = cent->prev; i != cent; i = i->prev)
        for (j = i->prev; j != cent; j = j->prev)
        {
            cut = strchrpos(j->dato.name, i->dato.c, 1);
            if (cut)
            {
                cambioLetra(j, i, cut);
                agregarllaves(j);
                free(cut);
            }
        }
}
int main()
{
    char nombre[N]; //4 horas
    TnodeD *cent = NULL;
    printf("Dame el nombre del archivo: ");
    scanf(" %[^\n]",nombre);
    inicializarlista(&cent);
    lecturaGR(nombre, cent);
    agrupacion(cent);
    cambiarOR(cent);
    sustitucion(cent);
    printf("EXPRESION REGULAR: %s",cent->next->dato.name);
    return 0;
}