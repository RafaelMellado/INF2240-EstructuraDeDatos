#include <stdio.h>
#include <stdlib.h>
#define maxArreglo 5000

struct Distrito{
    int id;
    char *nombre;
    float cantidadPoblacion;
};

struct Convencional{
    char *rut;
    char *nombre;
    char *comuna;
    struct Distrito *distritoRepresentado;
};

struct ConvencionConstitucional{
    char *fechaInicio;
    char *fechaFin;
    char *nombrePresidente;
    struct Convencional **convencionales;
    struct Distrito **distritos;

};

int contarConvencionalesDistrito(struct Convencional **convencionales, int idDistrito){
    int contador=0, i;
    for(i=0; i<maxArreglo; i++)
    {
        if(convencionales[i]!=NULL && convencionales[i]->distritoRepresentado->id==idDistrito)
            contador++;
    }
    return contador;
}

struct Convencional **quitarRespaldarConvencionales(struct Convencional **convencionales, int idDistrito){
    struct Convencional **convencionalesEliminados;
    int maxConvencionalesEliminados=0, i, j;

    maxConvencionalesEliminados=contarConvencionalesDistrito(convencionales,idDistrito);

    /*Si hay convencionales en el problema que representan dicho distrito*/
    if(maxConvencionalesEliminados>0)
    {
        /*Creamos el arreglo*/
        convencionalesEliminados=(struct Convencional **)malloc(maxConvencionalesEliminados*sizeof(struct Convencional *));
        j=0;

        /*Respaldamos los convencionales y se elimamos*/
        for(i=0; i<maxArreglo; i++)
        {
            if(convencionales[i]!=NULL && convencionales[i]->distritoRepresentado->id==idDistrito)
            {
                convencionalesEliminados[j]=convencionales[i];
                convencionales[i]=NULL;
                j++;
            }
        }
        return convencionalesEliminados;
    }
    return NULL;
}

void quitarDistrito(struct Distrito **distritos, int idDistrito){
    int i, j;

    /*Recorremos el arreglo de distritos hasta encontrar el elemento buscado*/
    for(i=0; i<maxArreglo && distritos[i]!=NULL; i++)
    {
        /*Encontramos el elemento buscado*/
        if(distritos[i]->id==idDistrito)
        {
            /*Se realiza la compactación*/
            for(j=i; j<maxArreglo-1; j++)
                distritos[j]=distritos[j+1];
            distritos[maxArreglo-1]=NULL;
        }
    }
}

struct Convencional **elimDistrito(struct ConvencionConstitucional *convencion, int idDistrito){
    struct Convencional **convencionalesQuitados=NULL;

    /*Respaldo convencionales*/
    convencionalesQuitados=quitarRespaldarConvencionales(convencion->convencionales,idDistrito);

    /*Se quita el distrito*/
    quitarDistrito(convencion->distritos,idDistrito);

    /*Se retorna el resultado: NUll o el Arreglo están dentro de la variables convencionalesQuitados*/
    return convencionalesQuitados;
}




int main()
{
    struct ConvencionConstitucional **constituyente;

    return 0;
}