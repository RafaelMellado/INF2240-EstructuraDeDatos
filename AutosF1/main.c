#include <stdio.h>
#include <stdlib.h>
#define cantEquipos 100

struct Auto {
    int numero;
    char *nombrePiloto;
    int cantidadVictorias;
};

struct Equipo {
    int id;
    char *nombre;
    char *nombreDirector;
    int pLibre;
    struct Auto **autos;
};

/*
 *1. necesito saber cuantos equipos tienen un ganador (contador) OK
 *  1.1tengo que tener una funcion que determine el ganador dentro de un equipo (retorne-null)   OK
 * 2. Crear un arreglo del tamaño del contador OK
 * 3. llenar ese arreglo OK
 * 4. retornar OK
 */


struct Auto *getGanadorEnEquipo(struct Auto **autos, int pLibreAutos){
    struct Auto *mayor=NULL;
    int i;

    for(i=0; i<pLibreAutos; i++)
    {
        if(mayor==NULL || autos[i]->cantidadVictorias>0 && autos[i]->cantidadVictorias > mayor->cantidadVictorias)
        {
            mayor=autos[i];
        }
    }
    return mayor;
}

int getCantidadGanadores(struct Equipo **equipos) {
    int i, contador=0;

    for(i=0; i<cantEquipos; i++)
    {
        if(equipos[i]!=NULL && getGanadorEnEquipo(equipos[i]->autos,equipos[i]->pLibre)!=NULL)
            contador++;
    }
    return contador;
}

void llenarArregloGanadores(struct Equipo **equipos, struct Auto **ganadores, int cantGanadores)
{
    int i, recGanadores=0;
    struct Auto *ganador;

    for(i=0; i<cantEquipos; i++) {
        if (equipos[i] != NULL) {
            ganador = getGanadorEnEquipo(equipos[i]->autos, equipos[i]->pLibre);
            if (ganador != NULL) {
                ganadores[recGanadores] = ganador;
                recGanadores++;
            }
        }
    }
}


struct Auto **getAutosGanadoresPorEquipo (struct Equipo **equipos) {

    struct Auto ** arregloGanadores=NULL;
    int cantidad=0;

    /*Crear arreglo nuevo*/
    cantidad= getCantidadGanadores(equipos);
    if(cantidad>0)
    {
        arregloGanadores = (struct Auto **)malloc(cantidad*sizeof (struct Auto *));
        /*Llenamos el arreglo*/
        llenarArregloGanadores(equipos,arregloGanadores,cantidad);

        /*retornar arreglo*/
        return arregloGanadores;
    }
    return NULL;
}

/*
Ejercicio:

 Implemente una función para eliminar un auto de un equipo determinado. Para ello, nos entregan el nombre del equipo y el número de auto.
 Debe quitar el auto del equipo y retornar una referencia hacia él.
 No olvide que los autos se manejan de forma compacta. En caso de que el auto o el equipo no exista, retorna NULL.
 El prototipo de la función es:
 */

struct Auto *quitarAutoDeEquipo(struct Equipo **equipos, char *nombreEquipo, int numeroAuto)
{
    return NULL;
}





int main(void) {
    struct Equipo **equiposF1;
    struct Auto **autosGanadores;


    autosGanadores= getAutosGanadoresPorEquipo(equiposF1);





    return 0;
}
