#include <stdio.h>
#include <stdlib.h>

struct Dato
{
	int valor;
};
struct Nodo
{
	struct Dato *dato;
	struct Nodo *sig;
};

struct Nodo *crearNodo(struct Dato *dato)
{
	struct Nodo *nuevo;

	/*Se obtiene la memoria al nuevo nodo*/
	nuevo=((struct Nodo*)malloc(sizeof(struct Nodo)));

	nuevo->dato=dato;
	nuevo->sig=NULL;

	return nuevo;
}

void enlazarNodo(struct Nodo **head, struct Nodo *nuevo)
{
	struct Nodo *rec=*head;

	/*No existe nodo inicial, ya que es el fantasma*/
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

main()
{

	/*Declaracion de la lista*/
	struct Nodo *lista;
	struct Dato *dato;

	/*Se crea lista con nodo fantasma*/
	lista=crearNodo(NULL);
	
	/*Se agrega otro elemento*/
	dato=((struct Dato*)malloc(sizeof(struct Dato)));

	printf("Ingrese un dato");
	scanf("%d", &dato->valor);

	enlazarNodo(&lista,crearNodo(dato));
}



