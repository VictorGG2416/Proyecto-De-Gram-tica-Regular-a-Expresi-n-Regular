#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50
typedef struct nodo
{
	char nom[50];
	struct nodo *sig;
}TNodo;

void leeDatos(FILE *fp, TNodo **cab);
TNodo *CreaNodo(char d[N]);
void insertaInicio(TNodo **cab, char d[N]);
void imprime(TNodo *cab);
void libera(TNodo **cab);

