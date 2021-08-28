#include <stdio.h>
#include <stdlib.h>
#define tamArreglos 1000

struct SistemaTransporte{
    char *nombre;
    char *representanteLegal;
    struct Linea **lineaBuses;
};

struct Linea{
    int numero;
    char *nombre;
    char *dirección;
    struct Bus **flota;
};

struct Bus{
    char *patente;
    float consumo;
    int capacidad;
};

float getPromedioConsumos(struct Bus **buses){
    int contador=0, i;
    float acumulador=0;

    for(i=0; i<tamArreglos && buses[i]!=NULL; i++)
    {
        acumulador+=buses[i]->consumo;
        contador++;
    }

    if(contador>0)
        return acumulador/contador;
    return 0;
}

float getPromedioCapacidades(struct Bus **buses){
    int contador=0, i, acumulador=0;


    for(i=0; i<tamArreglos && buses[i]!=NULL; i++)
    {
        acumulador+=buses[i]->capacidad;
        contador++;
    }

    if(contador>0)
        return (float)acumulador/contador;
    return 0;
}

int contarBusesIneficientes(struct Bus **buses, float promedioCapacidades, float promedioConsumos){
    int rec, contador=0;

    for(rec=0; rec<tamArreglos && buses[rec]!=NULL; rec++)
    {
        if(buses[rec]->capacidad<promedioCapacidades && buses[rec]->consumo>promedioConsumos)
            contador++;
    }
    return contador;
}

struct Bus **getArregloBusesIneficientes(struct Bus **buses, int cantidadBuses, float promedioCapacidades, float promedioConsumos){
    int indiceArregloNuevo=0, i, j;

    struct Bus **busesIneficientes=(struct Bus **)malloc(cantidadBuses*sizeof(struct Bus *));

    for(i=0; i<tamArreglos && buses[i]!=NULL; i++)
    {
        if(buses[i]->capacidad<promedioCapacidades && buses[i]->consumo>promedioConsumos)
        {
            busesIneficientes[indiceArregloNuevo]=buses[i];
            indiceArregloNuevo++;

            buses[i]=NULL;

            /*COMPACTAMOS*/
            for(j=i; j<tamArreglos-1 && buses[j]!=NULL; j++)
                buses[j]=buses[j+1];
            buses[tamArreglos-1]=NULL;

            i--;
        }
    }
    return busesIneficientes;
}


struct Bus **quitarBusesIneficientes(struct SistemaTransporte *transtortuga, int numeroLinea, int *tamBusesIneficientes){
    float promedioCapacidades, promedioConsumos;

    promedioCapacidades= getPromedioCapacidades(transtortuga);
    promedioConsumos= getPromedioConsumos(transtortuga);

    if(contarBusesIneficientes(transtortuga,promedioCapacidades,promedioConsumos)>0)
    {
        *tamBusesIneficientes=contarBusesIneficientes(transtortuga,promedioCapacidades,promedioConsumos);
        return getArregloBusesIneficientes(transtortuga, contarBusesIneficientes(transtortuga,promedioCapacidades,promedioConsumos), promedioCapacidades, promedioConsumos);
    }
    return NULL;
}



int main() {
    struct SistemaTransporte *transtortuga;



    return 0;
}
