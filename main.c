#include "main.h"

int main () 
{
	FILE *fp;
	TNodo *cab;
	cab=NULL;
	char nom[N];
	
	printf("Nombre del archivo: ");
	scanf("%s",nom);
	
	if((fp=fopen(nom,"r"))==NULL)
	{
		printf("Archibo no encontrado :(");
		exit(0);
	}
	printf("**********DATOS DEL ARCHIVO**********");
	leeDatos(fp,&cab);
	imprime(cab);
	
	libera(&cab);
	fclose(fp);
}

void leeDatos(FILE *fp, TNodo **cab)
{
	char nom[N];
	
	while(!feof(fp))
	{
		fgets(nom,N,fp);
		insertaInicio(cab,nom);
	}
}

void insertaInicio(TNodo **cab, char d[N])
{
	TNodo *nodo=CreaNodo(d);
	if(*cab == NULL)
		*cab=nodo;
	else
	{
		nodo->sig = *cab;
		*cab=nodo;
	}
}

TNodo *CreaNodo(char d[N])
{
	TNodo *nodo=(TNodo *)malloc(sizeof(TNodo));
	
	if(nodo)
	{
		nodo->nom[0]='\0';
		strcpy(nodo->nom,d);
		nodo->sig=NULL;
		return nodo;
	}
	printf("Error :(");
	exit(0);	
}

void imprime(TNodo *cab)
{
	TNodo *ptr=cab;
	while(ptr)
	{
		printf("%s\n",ptr->nom);
		ptr=ptr->sig;
	}
}

void libera(TNodo **cab)
{
	TNodo *ptr;
	while(*cab)
	{
		ptr= *cab;
		*cab=ptr->sig;
		free(ptr);
	}
}
