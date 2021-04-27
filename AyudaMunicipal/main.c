#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxRepartidores 400

struct Ayudado
{
    char *rut;
    char *nombre;
    int ingresos;
    int montoAyuda;
};

struct NodoAyudado
{
    struct Ayudado *familia;
    struct NodoAyudado *sig;
};

struct RepartidorAyuda
{
    int id;
    struct NodoAyudado *headAyudados;
};

struct Ciudad
{
    char *nombreAlcalce;
    char *nombreCiudad;
    struct RepartidorAyuda **repartidores;
};

float promedioAyudasRepartidor(struct NodoAyudado *listaAyudados)
{
    int suma=0, contador=0;

    while(listaAyudados!=NULL)
    {
        suma+=listaAyudados->familia->montoAyuda;
        contador++;
        listaAyudados=listaAyudados->sig;
    }
    if(contador>0)
        return suma/contador;

    return 0;
}

float promedioAyudasRepartidores(struct RepartidorAyuda **repartidores)
{
    int contador=0, i;
    float suma=0;

    for(i=0; i<maxRepartidores; i++)
    {
        if(repartidores[i]!=NULL)
        {
            suma+=promedioAyudasRepartidor(repartidores[i]->headAyudados);
            contador++;
        }
    }

    if(contador>0)
        return suma/contador;
    return 0;
}

int cantidadRepartidoresAyudaSobrePromedio(struct RepartidorAyuda **repartidores)
{
    float promedioAyuda;
    int contador=0, i;

    promedioAyuda=promedioAyudasRepartidores(repartidores);

    if(promedioAyuda>0)
    {
        for(i=0; i<maxRepartidores; i++)
        {
            if(repartidores[i]!=NULL && promedioAyudasRepartidor(repartidores[i]->headAyudados)>promedioAyuda)
                contador++;
        }
    }
    return contador;
}

int eliminarAyudado(struct NodoAyudado **listaAyudados, char *rut)
{
    struct NodoAyudado *rec;
    if(*listaAyudados!=NULL)
    {
        if(strcmp((*listaAyudados)->familia->rut,rut)==0)
        {
            *listaAyudados=(*listaAyudados)->sig;
            return 1;
        }
        rec=*listaAyudados;
        while(rec->sig!=NULL)
        {
            if(strcmp(rec->sig->familia->rut,rut)==0)
            {
                rec->sig=rec->sig->sig;
                return 1;
            }
            rec=rec->sig;
        }
    }
    return 0;
}

int eliminarAyudadosRepartidor(struct NodoAyudado **listaAyudados, int montoReferencia)
{
    int contador=0;
    struct NodoAyudado *rec;

    rec=(*listaAyudados);

    while(rec!=NULL)
    {
        if(rec->familia->montoAyuda>montoReferencia)
            contador+=eliminarAyudado(listaAyudados,rec->familia->rut);
        rec=rec->sig;
    }
    return contador;
}

int quitarAyudaFamilias(struct RepartidorAyuda **repartidores, int montoReferencia)
{
    int contador=0, i;

    for(i=0; i<maxRepartidores; i++)
    {
        if(repartidores[i]!=NULL)
            contador+=eliminarAyudadosRepartidor(&(repartidores[i]->headAyudados),montoReferencia);
    }
    return contador;
}



int main()
{

}
