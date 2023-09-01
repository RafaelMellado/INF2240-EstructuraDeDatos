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

/*1. Agregar un nuevo cliente al sistema, verificando que no esté repetido (numero ID) y agregandolo de forma ordenada en la lista ascendentemente*/

/*Nota mental:
 * buscar
 * crear cliente
 * enlazar*/


struct Cliente *buscarCliente(struct NodoCliente *head, int numeroID)
{
    while(head!=NULL)
    {
        if(head->datosCliente->numeroID == numeroID)
            return head->datosCliente;
        head=head->sig;
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


/*Agregar cliente*/
int agregarCliente(struct NodoCliente **headClientes, int numeroID, char *nombre)
{
    struct NodoCliente *rec, *nuevoNodo;

    /*Si el cliente no existe, por eso es NULL*/
    if(buscarCliente(*headClientes,numeroID)==NULL)
    {
        /*Creamos el cliente y su nodo*/
        nuevoNodo=(struct NodoCliente*)malloc(sizeof (struct NodoCliente));
        nuevoNodo->datosCliente=crearCliente(numeroID,nombre);
        nuevoNodo->sig=NULL;

        /*Enlazamos cliente*/
        if(*headClientes==NULL)
        {
            *headClientes=nuevoNodo;
            return 1;
        }
        else
        {
            rec=*headClientes;
            while(rec->sig!=NULL)
                rec=rec->sig;

            rec->sig=nuevoNodo;
            return 1;
        }
    }
    return 0;
}


/*Agrega cliente ordenado*/
int agregarClienteOrdenado(struct NodoCliente **headClientes, int numeroID, char *nombre)
{
    struct NodoCliente *rec, *nuevoNodo;

    /*Si el cliente no existe, por eso es NULL*/
    if(buscarCliente(*headClientes,numeroID)==NULL)
    {
        /*Creamos el cliente y su nodo*/
        nuevoNodo=(struct NodoCliente*)malloc(sizeof (struct NodoCliente));
        nuevoNodo->datosCliente=crearCliente(numeroID,nombre);
        nuevoNodo->sig=NULL;

        /*Enlazamos cliente*/
        /*Caso 0: lista vacia*/
        if(*headClientes==NULL)
        {
            *headClientes=nuevoNodo;
            return 1;
        }
        else
        {
            rec=*headClientes;

            /*avanzamos hasta el lugar donde se debe agregar*/
            while(rec->sig!=NULL && numeroID>rec->sig->datosCliente->numeroID)
                rec=rec->sig;

            /*Caso 1: agrego el siguiente al head, osea el segundo*/
            if(*headClientes==rec)
            {
                nuevoNodo->sig=(*headClientes)->sig;
                (*headClientes)->sig=nuevoNodo;
                return 1;
            }
            else
            {
                /*Caso 2: agregar despues del segundo*/
                nuevoNodo->sig=rec->sig;
                rec->sig=nuevoNodo;
                return 1;
            }
        }
    }
    return 0;
}





/*
struct Cliente *buscarCliente(struct NodoCliente *head, int numeroID)
{
    struct NodoCliente *rec;

    rec=head;
    while(rec!=NULL)
    {
        if(rec->datosCliente->numeroID == numeroID)
            return rec->datosCliente;
        rec=rec->sig;
    }
    return NULL;
}

*/

int main() {

    struct NodoCliente *head=NULL;

    printf("Hello, World!\n");
    return 0;
}
