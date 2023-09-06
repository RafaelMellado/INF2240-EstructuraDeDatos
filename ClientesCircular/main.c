#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define comprasMaximas 10000

struct Compra{
    int numeroCompra;
    char *fecha;
    int monto;
};

struct Cliente{
    int numeroID;
    char *nombre;
    struct Compra **compras;
    int pLibreCompras;
};

struct NodoCliente{
    struct Cliente *datosCliente;
    struct NodoCliente *sig;
};

/*1. Agregar un nuevo cliente al sistema, verificando que no esté repetido (numero ID)*/

struct Cliente *buscarCliente (struct NodoCliente *head, int IDCliente)
{
    struct NodoCliente *rec;

    if(head!=NULL)
    {
        rec=head;
        do {
            if(rec->datosCliente->numeroID==IDCliente)
                return rec->datosCliente;
            rec=rec->sig;
        }while(rec!=head);
    }
    return NULL;
}

struct Cliente *crearCliente(int numeroID, char *nombre)
{
    struct Cliente *nuevo=NULL;

    nuevo=(struct Cliente *)malloc(sizeof (struct Cliente));

    nuevo->numeroID=numeroID;
    strcpy(nuevo->nombre,nombre);
    nuevo->compras=(struct Compra **)malloc(comprasMaximas * sizeof (struct Compra *));
    nuevo->pLibreCompras=0;

    return nuevo;
}

int enlazarCliente(struct NodoCliente **head, int IDCLiente, char *nombre)
{
    struct NodoCliente *rec, *nuevo;

    /*Primero buscamos que el cliente no exista*/
    if(buscarCliente(*head,IDCLiente)==NULL)
    {
        /*Como sabemos que no existe el cliente, entonces creamos al cliente con su nodo sin enlazarlo aún*/
        nuevo=(struct NodoCliente *)malloc(sizeof (struct NodoCliente));
        nuevo->datosCliente=crearCliente(IDCLiente,nombre);

        /*Ahora, vamos a enlazar....*/

        /*Caso 1: La lista está vacia*/
        if(*head==NULL)
        {
            /*Hacemos en enlace, quedando el nuevo como único elemento, por ende, referenciado a si mismo*/
            *head=nuevo;
            (*head)->sig=*head;
            return 1;
        }
        else
        {
            /*Caso 2: existen más elementos*/
            rec=*head;
            do{
                rec=rec->sig;
            }while(rec->sig!=(*head));

            /*Enlazamos el nuevo nodo*/
            rec->sig=nuevo;
            nuevo->sig=*head;
            return 1;
        }
    }
    return 0;
}

/*Determinar el cliente que tiene la sumatoria de montos de compra mayor en el sistema, en el caso de empate retorna solo el primero*/

int getSumatoriaMontosCompra(struct Compra **compras, int pLibreCompras)
{
    int i, suma=0;
    for(i=0; i<pLibreCompras; i++)
        suma+=compras[i]->monto;
    return suma;
}

struct Cliente *getClientePudiente(struct NodoCliente *head)
{
    struct NodoCliente *rec;
    struct Cliente *mayor=NULL;

    if(head!=NULL)
    {
        mayor=head->datosCliente;
        rec=head->sig;

        do {
            if(getSumatoriaMontosCompra(rec->datosCliente->compras,rec->datosCliente->pLibreCompras)>getSumatoriaMontosCompra(mayor->compras,mayor->pLibreCompras))
                mayor=rec->datosCliente;
            rec=rec->sig;
        }while(rec!=head);
    }
    return mayor;
}

int main() {

    struct NodoCliente *head=NULL;

    printf("Hello, World!\n");
    return 0;
}
