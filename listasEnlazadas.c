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
	}
	else
	{
		/*Como no era el primer elemento a agregar se busca el ultimo elemento*/
		while(rec!=NULL)
		{
			if(rec->sig==NULL)
			{
				rec->sig=nuevo;
				rec=nuevo;
			}
			rec=rec->sig;
		}
	}
}


main()
{
	/*En este ejemplo se agregarán 3 elementos a la lista*/

	/*Declaracion de la lista*/
	struct Nodo *lista=NULL, *aux, *rec;

	/*Primer elemento*/
	aux=crearNodo();
	enlazarNodo(&lista,aux);

	
	/*Segundo elemento sin usar aux*/
	enlazarNodo(&lista,crearNodo());

	/*Tercer elemento sin usar aux*/
	enlazarNodo(&lista,crearNodo());

	/*Mostrar elementos de la lista*/
	rec=lista;
	while(rec!=NULL)
	{
		printf("[%d]->", rec->elemento);
		rec=rec->sig;
	}
	printf("NULL\n\n");
}



