#include <stdio.h>
#include <stdlib.h>

struct Avion
{
    int id;
    char *marca;
    char *modelo;
    int capacidad;
};

float promedioCapacidades(struct Avion **aviones, int pLibre)
{
    int i;
    float suma=0;

    if(pLibre>0)
    {
        for(i=0; i<pLibre; i++)
        {
            suma+=aviones[i]->capacidad;
        }
        return suma/pLibre;
    }
    return 0;
}

int contarAvionesBajaCapacidad(struct Avion **aviones, int pLibre, float promedioCapacidad)
{
    int i, cont=0;

    for(i=0; i<pLibre; i++)
    {
        if(aviones[i]->capacidad<promedioCapacidad)
        {
            cont++;
        }
    }
    return cont;
}

void quitarAvion(struct Avion **aviones, int *pLibre, int idAvion)
{
    int i, j;
    for(i=0; i<*pLibre; i++)
    {
        if(aviones[i]->id==idAvion)
        {
            aviones[i]=NULL;

            /*Compactación*/
            for(j=i; j<(*pLibre)-1; j++)
            {
                aviones[j]=aviones[j+1];
            }
            aviones[*pLibre-1]=NULL;
            (*pLibre)--;
        }
    }
}

struct Avion **quitarAvionesBajaCapacidad(struct Avion **aviones, int *pLibre)
{
    struct Avion **avionesEliminados=NULL;
    int i, posicion=0;
    float promCapacidades;

    promCapacidades=promedioCapacidades(aviones,*pLibre);
    if(contarAvionesBajaCapacidad(aviones,*pLibre,promCapacidades)>0)
    {
        avionesEliminados=(struct Avion**)malloc(contarAvionesBajaCapacidad(aviones,*pLibre,promCapacidades)*sizeof(struct Avion*));
        for(i=0; i<*pLibre; i++)
        {
            if(aviones[i]->capacidad<promCapacidades)
            {
                avionesEliminados[posicion]=aviones[i];
                posicion++;
                quitarAvion(aviones,&(*pLibre),aviones[i]->id);
            }
        }
    }
    return avionesEliminados;
}




int main() {
    struct Avion **aviones, **avionesEliminados;
    int pLibre=0;

    avionesEliminados=quitarAvionesBajaCapacidad(aviones, &pLibre);

    return 0;
}
