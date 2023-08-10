#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente
{
    char *rut;
    char *nombre;
    int edad;
    int montoCompra;
};

int buscarCliente(struct Cliente **clientes, int tamTotal, char *rutBuscado)
{
    int i;

    for(i=0; i<tamTotal && clientes[i]!=NULL; i++)
    {
        if(strcmp(rutBuscado,clientes[i]->rut)==0)
            return 1;
    }
    return 0;
}

int agregarCliente(struct Cliente **clientes, int tamTotal, char *rutNuevo, char *nombreNuevo, int edad, int montoCompra)
{
    int i;

    if(buscarCliente(clientes,tamTotal,rutNuevo)==0)
    {
        for(i=0; i<tamTotal; i++)
        {
            if(clientes[i]==NULL)
            {
                clientes[i]=(struct Cliente *)malloc(sizeof(struct Cliente));

                strcpy(clientes[i]->rut,rutNuevo);
                strcpy(clientes[i]->nombre,nombreNuevo);
                clientes[i]->edad=edad;
                clientes[i]->montoCompra=montoCompra;

                return 1;
            }
        }
    }
    return 0;
}

struct Cliente * quitarCliente(struct Cliente **clientes, int tamTotal, char *rutAQuitar)
{
    int i, j;
    struct Cliente *quitado=NULL;

    for(i=0; i<tamTotal && clientes[i]!=NULL; i++)
    {
        if(strcmp(clientes[i]->rut,rutAQuitar)==0)
        {
            quitado=clientes[i];
            clientes[i]=NULL;

            /*compactar arreglo*/
            for(j=i; j<tamTotal-1; j++)
                clientes[j]=clientes[j+1];

            clientes[tamTotal-1]=NULL;

            return quitado;
        }
    }
    return quitado;
}


int eliminarCliente(struct Cliente **clientes, int tamTotal, char *rutAQuitar)
{
    int i, j;

    for(i=0; i<tamTotal && clientes[i]!=NULL; i++)
    {
        if(strcmp(clientes[i]->rut,rutAQuitar)==0)
        {
            /*compactar arreglo*/
            for(j=i; j<tamTotal-1 && clientes[j]!=NULL; j++)
                clientes[j]=clientes[j+1];

            clientes[tamTotal-1]=NULL;

            return 1;
        }
    }
    return 0;
}

/*OBLIGATORIOS*/
/*1. Hacer el main*/
/*2. Determinar el cliente que tiene el mayor monto de compra
 *
 * char * getRutClienteMayorMontoCompra(struct Cliente **clientes, int tamTotal)
 *
 * */

/*OPCIONALMENTE*/
/*3. Retorne los clientes que tienen un monto de compra mayor al promedio de monto de compra de todos los clientes
 *
 * struct Cliente ** getClientesComprasMayorAlPromedio(struct Cliente **clientes, int tamTotal)
 *
 * */




int main() {

    int cantidadClientes=0;

    /*Declaramos el arreglo*/
    struct Cliente **clientes;

    //struct Cliente * clientes[];

    /*Obtener tamaño del arreglo*/
    do {
        printf("Ingrese la cantidad de clientes a almacenar: ");
        scanf ("%d", &cantidadClientes);
    }while (cantidadClientes<=0);

    /*creamos el arreglo*/
    clientes=(struct Cliente **)malloc(cantidadClientes*sizeof (struct Cliente *));


}
