#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dias 30

struct Programa{
    char *nombre;
    char *conductor;
    float rating[dias];
};

struct NodoPrograma{
    struct NodoPrograma *ant, *sig;
    struct Programa *programa;
};

struct CanalTV{
    int numero;
    char *nombre;
    char *propietario;
    struct NodoPrograma *headProgramas;
};

struct NodoCanalTV{
    struct NodoCanalTV *izq, *der;
    struct CanalTV *datosCanal;
};

struct SistemaTV{
    struct NodoCanalTV *canales;
};


float getPromedioRating(float *ratings)
{
    float promedio=0;
    int contador=0, i;

    for(i=0; i<dias; i++)
    {
        if(ratings[i]>0)
        {
            promedio+=ratings[i];
            contador++;
        }
    }
    if(contador>0)
        return promedio/contador;
    return 0;
}

struct Programa *getProgramaMayorRating(struct NodoPrograma *listaProgramas){
    struct Programa *ganador=NULL;

    while(listaProgramas!=NULL)
    {
        if(ganador==NULL || getPromedioRating(listaProgramas->programa->rating)> getPromedioRating(ganador->rating))
            ganador=listaProgramas->programa;
        listaProgramas=listaProgramas->sig;
    }

    return ganador;
}

char *getNombreProgramaMayorRating(struct NodoCanalTV *abb, int numeroCanal){

    if(abb!=NULL)
    {
        /*CASOS EN QUE ESTA MAS ABAJO*/
        if(numeroCanal>abb->datosCanal->numero)
            return getNombreProgramaMayorRating(abb->der, numeroCanal);

        /*CASO DE QUE ENCONTRAMOS EL ELEMENTO*/
        if(abb->datosCanal->numero==numeroCanal && getProgramaMayorRating(abb->datosCanal->headProgramas)!=NULL)
            return (getProgramaMayorRating(abb->datosCanal->headProgramas))->nombre;

        if(numeroCanal<abb->datosCanal->numero)
            return getNombreProgramaMayorRating(abb->izq, numeroCanal);
    }
    return NULL;
}

float getPromedioCanal(struct NodoPrograma *headProgramas){

    struct NodoPrograma *rec;
    float suma=0;
    int cantidadProgramas=0;

    rec=headProgramas;
    while(rec!=NULL)
    {
        suma=suma+getPromedioRating(rec->programa->rating);
        cantidadProgramas++;

        rec=rec->sig;
    }

    if (cantidadProgramas>0)
        return suma/cantidadProgramas;
    return 0;
}

void getCanalMayorRating(struct NodoCanalTV *abbCanales, struct CanalTV **canalMayor){

    if(abbCanales!=NULL)
    {
        getCanalMayorRating(abbCanales->izq, &(*canalMayor));

        if(*canalMayor==NULL || getPromedioCanal(abbCanales->datosCanal->headProgramas)> getPromedioCanal((*canalMayor)->headProgramas))
            *canalMayor=abbCanales->datosCanal;

        getCanalMayorRating(abbCanales->der, canalMayor);
    }
}

float getMayorRatingPrograma(float *ratings){
    float mayor=0;
    int i=0;

    for(i=0; i<dias; i++)
    {
        if(mayor==0 || ratings[i]>mayor)
            mayor=ratings[i];
    }
    return mayor;
}

struct Programa *getProgramaMayorPicRating(struct NodoPrograma *listaProgramas){
    struct Programa *mayor=NULL;

    /*BUSCAMOS EL PROGRAMA CON EL MAYOR RATING*/
    while(listaProgramas!=NULL)
    {
        if(mayor==NULL || getMayorRatingPrograma(listaProgramas->programa->rating)> getMayorRatingPrograma(mayor->rating))
            mayor=listaProgramas->programa;
        listaProgramas=listaProgramas->sig;
    }
    return mayor;
}

char * getProgramaMejorRatingCanal(struct NodoCanalTV *abbCanales, int numeroCanal){

    struct Programa *auxGanador=NULL;

    if(abbCanales!=NULL)
    {
        return getProgramaMejorRatingCanal(abbCanales->izq, numeroCanal);
        return getProgramaMejorRatingCanal(abbCanales->der, numeroCanal);

        if(abbCanales->datosCanal->numero==numeroCanal)
        {
            auxGanador=getProgramaMayorPicRating(abbCanales->datosCanal->headProgramas);
            if(auxGanador!=NULL)
                return auxGanador->nombre;
        }
    }
    return NULL;
}



int main()
{
    struct SistemaTV *TVChile;

    TVChile=(struct SistemaTV*) malloc (sizeof(struct SistemaTV));

    /*AGREGAR EN TODOS LOS NIVELES*/

    /*INVOCAR LA FNCION*/
    printf("Hello, World!\n");
    return 0;
}
