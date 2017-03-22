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

void enlazarNodo(struct Nodo **head, struct Nodo *nuevo)
{
	struct Nodo *rec=*head;

	if(*head==NULL)
	{
		*head=nuevo;
		(*head)->sig=*head;
	}
	else
	{
		do
		{
			if(rec!=NULL)
			{
				if(rec->sig==*head)
				{
					nuevo->sig=rec->sig;
					rec->sig=nuevo;
					rec=rec->sig;
				}
			}

		}while(rec->sig!=*head);
	}
}

main()
{
	/*En este ejemplo se agregarán 3 elementos a la lista*/

	/*Declaracion de la lista*/
	struct Nodo *listaCircular=NULL, *aux, *rec;

	/*Primer elemento*/
	aux=crearNodo();
	enlazarNodo(&listaCircular,aux);

	
	/*Segundo elemento sin usar aux*/
	enlazarNodo(&listaCircular,crearNodo());

	/*Mostrar elementos de la lista*/
	rec=listaCircular;
	if(rec)
	{
		do
		{
			printf("[%d]->", rec->elemento);
			rec=rec->sig;
		}while(rec!=listaCircular);
	}
	printf("NULL\n\n");
}



