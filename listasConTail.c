#include <stdio.h>
#include <stdlib.h>

struct Nodo
{
	int elemento;
	struct Nodo *sig;
};

struct Nodo *crearNodo()
{
	struct Nodo *nuevo;

	/*Se obtiene la memoria al nuevo nodo*/
	nuevo=((struct Nodo*)malloc(sizeof(struct Nodo)));

	/*Se completa con los datos*/
	printf("ingrese numero: ");
	scanf("%d", &nuevo->elemento);
	nuevo->sig=NULL;

	return nuevo;
}

void enlazarNodo(struct Nodo **head, struct Nodo **tail, struct Nodo *nuevo)
{
	struct Nodo *rec=*head;

	if(*head==NULL)
	{
		*head=nuevo;
		*tail=*head;
	}
	else
	{
		(*tail)->sig=nuevo;
		*tail=(*tail)->sig;
	}
}


main()
{
	/*En este ejemplo se agregarán 3 elementos a la lista*/

	/*Declaracion de la lista*/
	struct Nodo *lista=NULL, *tail, *aux, *rec;

	/*Primer elemento*/
	aux=crearNodo();
	enlazarNodo(&lista,&tail,aux);

	
	/*Segundo elemento sin usar aux*/
	enlazarNodo(&lista,&tail,crearNodo());

	/*Tercer elemento sin usar aux*/
	enlazarNodo(&lista,&tail,crearNodo());

	/*Mostrar elementos de la lista*/
	rec=lista;
	while(rec!=NULL)
	{
		printf("[%d]->", rec->elemento);
		rec=rec->sig;
	}
	printf("NULL\n\n");
}



