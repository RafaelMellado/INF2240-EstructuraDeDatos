#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pasajero{
    int id;
    char *rut;
    char *nombre;
    int puntosChileanAirline;
};

struct NodoPasajero{
    struct Pasajero *pasajero;
    struct NodoPasajero *sig;
};

struct Vuelo{
    int id;
    int capacidad; //cantidad maxima de asientos del vuelo
    char *destino;
    struct Pasajero **pasajerosEnAsientos; //compacto sin plibre
};

struct NodoVuelo{
    struct Vuelo *datosVuelo;
    struct NodoVuelo *ant, *sig;
};

struct SistemaLineaAerea{
    struct NodoVuelo *headVuelos;
    struct NodoPasajero *headPasajeros;
};

char *getDestinoVuelo(struct NodoVuelo *head, int idVueloBuscado)
{
    struct NodoVuelo *rec;

    if(head!=NULL)
    {
        rec=head;
        do{
            if(rec->datosVuelo->id==idVueloBuscado)
                return rec->datosVuelo->destino;
            rec=rec->sig;
        }while(rec!=head);
    }
    return NULL;
}

int getCantidadPasajerosVuelo(struct Pasajero **pasajerosEnAsientos, int capacidadAsientos)
{
    int i, contador=0;
    for(i=0; i<capacidadAsientos && pasajerosEnAsientos[i]!=NULL; i++)
            contador++;
    return contador;
}

int getCapacidadTotalDestino(struct NodoVuelo *head, char *destinoBuscado)
{
    int contador=0;
    struct NodoVuelo *rec;

    if(head!=NULL)
    {
        rec=head;
        do {
            if(strcmp(rec->datosVuelo->destino,destinoBuscado)==0)
                contador+=(rec->datosVuelo->capacidad - getCantidadPasajerosVuelo(rec->datosVuelo->pasajerosEnAsientos, rec->datosVuelo->capacidad));
            rec=rec->sig;
        }while(rec!=head);
    }
    return contador;
}

struct Vuelo *getVuelo(struct NodoVuelo *head, int idVueloBuscado)
{
    struct NodoVuelo *rec=NULL;

    if(head!=NULL)
    {
        rec=head;
        do {
            if(rec->datosVuelo->id==idVueloBuscado)
                return rec->datosVuelo;
            rec=rec->sig;
        }while(rec!=head);
    }
    return rec;
}

int agregarPasajeroAVuelo(struct Vuelo *vuelo, struct Pasajero *pasajero)
{
    int i;
    for(i=0; i<vuelo->capacidad; i++)
    {
        if(vuelo->pasajerosEnAsientos[i]==NULL)
        {
            vuelo->pasajerosEnAsientos[i]=pasajero;
            return 1;
        }
    }
    return 0;
}

void moverPasajerosDeVuelo(struct NodoVuelo *headVuelos, struct Vuelo *vueloAEliminar)
{
    int i;
    struct NodoVuelo *rec;

    for(i=0; i<vueloAEliminar->capacidad && vueloAEliminar->pasajerosEnAsientos[i]!=NULL; i++)
    {
        if(headVuelos!=NULL)
        {
            rec=headVuelos;
            do {
                //Si se puede agregar al vuelo debo romper el ciclo de recorrido de vuelos, sino avanzar al siguiente vuelo
                if(rec->datosVuelo!=vueloAEliminar && strcmp(rec->datosVuelo->destino,vueloAEliminar->destino)==0 && agregarPasajeroAVuelo(rec->datosVuelo,vueloAEliminar->pasajerosEnAsientos[i])==1)
                    rec=headVuelos;
                else
                    rec=rec->sig;
            }while(rec!=headVuelos);
        }
    }
}

void eliminarVueloSistema(struct NodoVuelo **headVuelos, struct Vuelo *vueloAEliminar)
{
    struct NodoVuelo *rec;
    if(headVuelos!=NULL)
    {
        //1: Es el head
        if((*headVuelos)->datosVuelo==vueloAEliminar)
        {
            (*headVuelos)->ant->sig=(*headVuelos)->sig;
            (*headVuelos)->sig->ant=(*headVuelos)->ant;
            *headVuelos=(*headVuelos)->sig;
            return;
        }
        else
        {
            //2: No es el head
            rec=(*headVuelos)->sig;
            do {
                if(rec->datosVuelo==vueloAEliminar)
                {
                    rec->ant->sig=rec->sig;
                    rec->sig->ant=rec->ant;
                    rec=NULL;
                    return;
                }
                rec=rec->sig;
            }while(rec!=*headVuelos);
        }
    }
}


int eliminarVuelo(struct SistemaLineaAerea *chileanAirlines, int idVueloEliminar)
{
    int asientosDisponibles=0;
    struct Vuelo *vueloAEliminar=NULL;

    //1: determinar si hay espacio en otros vuelos al mismo destino
    if(chileanAirlines->headVuelos!=NULL)
    {
        vueloAEliminar= getVuelo(chileanAirlines->headVuelos,idVueloEliminar);
        if(vueloAEliminar!=NULL)
            asientosDisponibles= getCapacidadTotalDestino(chileanAirlines->headVuelos, vueloAEliminar->destino) - getCantidadPasajerosVuelo(vueloAEliminar->pasajerosEnAsientos,vueloAEliminar->capacidad);

        /*Se procede con la solución sólo si la cantidad disponible es mayor o igual a la de pasajeros a mover*/
        if(asientosDisponibles >= getCantidadPasajerosVuelo(vueloAEliminar->pasajerosEnAsientos,vueloAEliminar->capacidad))
        {
            //2: mover los pasajeros
            moverPasajerosDeVuelo(chileanAirlines->headVuelos, vueloAEliminar);

            //3: eliminar el vuelo
            eliminarVueloSistema(&(chileanAirlines->headVuelos), vueloAEliminar);

            return 1;
        }
    }
    return 0;
}







int main() {
    struct SistemaLineaAerea *chileanAirlines;
    int resultado;


    resultado=eliminarVuelo(chileanAirlines, 65524);
    if(resultado==1)
        printf("Vuelo eliminado correctamente");
    else
        printf("Error, no se puede borrar el vuelo");

    printf("Hello, World!\n");
    return 0;
}
