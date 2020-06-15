#include <stdio.h>
#include <stdlib.h>
#define cantidadNodos 100

struct BTR
{
    struct Planes *planes;
    struct NodoRed **nodosRed;
    int Plibre;
};

struct Planes
{
    struct NodoPlan *head;
    int cantidadPlanes;
};

struct NodoPlan
{
    struct Plan *datosPlan;
    struct NodoPlan *sig;
};

struct Plan
{
    int codigo;
    char *nombre;
    int valor;
    int velocidad;
};

struct NodoRed
{
    struct NodoCliente *abb;
};

struct NodoCliente
{
    struct Cliente *cliente;
    struct NodoCliente *izq, *der;
};

struct Cliente
{
    int numeroCliente;
    char* rut;
    char *nombre;
    char *direccion;
    struct Plan *planContratado;
};

int main() 
{
}

int buscarClienteEnNodo(char *rut, struct NodoCliente *abb)
{
    if(abb!=NULL || strcmp(abb->cliente->rut,rut)==0)      
    {
        return 1;
    }
    else
    {
        if(abb->cliente->rut>rut)
        {
            return (buscarClienteEnNodo(rut,abb->izq));
        }
        else
        {
            return (buscarClienteEnNodo(rut,abb->der));
        }
    }
}

int buscarClientesEnEmpresa(char *rut, struct NodoRed **nodosRed, int Plibre)
{
    int i;
    
    for(i=0; i<cantidadNodos && i<Plibre; i++)
    {
        if(buscarClienteEnNodo(rut, nodosRed[i]->abb)==1)
        {
            return 1;
        }
    }
    return 0;
}

/* BUSCAR EL NODO CON MENOS CARGA*/
void contarClientesNodo(struct NodoCliente *abb, int *contador)
{
    if(abb)
    {
        *contador=*contador+1;
        contarClientesNodo(abb->izq, contador);
        contarClientesNodo(abb->der, contador);
    }
}

struct NodoCliente *buscarNodoMenorCarga(struct NodoRed **nodosRed, int Plibre)
{
    int i, menorActual, menorNuevo;
    struct NodoCliente *menor=NULL;
    
    for(i=0; i<cantidadNodos && i<Plibre; i++)
    {
        if(menor==NULL)
        {
            menor=nodosRed[i]->abb;
        }
        else
        {
            contarClientesNodo(menor, &menorActual);
            contarClientesNodo(nodosRed[i]->abb, &menorNuevo);
            
            if(menorNuevo<menorActual)
            {
                menor=nodosRed[i]->abb;
            }
        }
    }
    return menor;
}

struct Plan *buscarPlan (struct NodoPlan *planes, int codigo)
{
    while(planes)
    {
        if(planes->datosPlan->codigo==codigo)
        {
            return planes->datosPlan;
        }
        planes=planes->sig;
    }
    return NULL;
}

void insertarCliente(struct NodoCliente **abb, struct Cliente *nuevo)
{
    if((*abb)==NULL)
    {
        *abb=(struct NodoCliente *)malloc(sizeof(struct NodoCliente));
        (*abb)->cliente=nuevo;
        (*abb)->izq=(*abb)->der=NULL;
    }
    else
    {
        if((*abb->cliente->rut)>nuevo->rut)
        {
            insertarCliente(&((*abb)->izq),nuevo);
        }
        else
        {
            insertarCliente(&((*abb)->der),nuevo);
        }
    }
}

int agregarCliente(struct BTR *empresa, struct Cliente *nuevo, int codigoPlan)
{    
    if(nuevo!=NULL && buscarClientesEnEmpresa(nuevo->rut, empresa->nodosRed, empresa->Plibre)==0)
    {
        if(buscarNodoMenorCarga(empresa->nodosRed,empresa->Plibre)!=NULL)
        {
            if(buscarPlan(empresa->planes,codigoPlan)!=NULL)
            {
                nuevo->planContratado=buscarPlan(empresa->planes,codigoPlan);
                insertarCliente(buscarNodoMenorCarga(empresa->nodosRed,empresa->Plibre),nuevo);
                return 1;
            }
        }
    }
    return 0;
}

