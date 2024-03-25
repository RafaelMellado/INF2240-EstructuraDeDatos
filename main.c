#include <stdio.h>
#include <stdlib.h>
#define cantFundaciones 10000

struct Traspaso
{
    int numero;
    char *nombre;
    int monto;
    char *nombreAutorizacion;
};

struct Fundacion
{
    int id;
    char *representante;
    char *nombreFundacion;
    int pLibre;
    struct Traspaso **traspasos;
};

int calcularMontoAcumuladoTraspasos(struct Traspaso **traspasos, int pLibre){

    int sumaTraspasos=0, i;

    for(i=0; i<pLibre; i++)
        sumaTraspasos+=traspasos[i]->monto;
    return sumaTraspasos;
}

int contarFundacionesBajoMontoReferencia(struct Fundacion **fundaciones, int montoReferencia){

    int i, contador=0;

    for(i=0; i<cantFundaciones; i++)
    {
        if(fundaciones[i]!=NULL && calcularMontoAcumuladoTraspasos(fundaciones[i]->traspasos, fundaciones[i]->pLibre) < montoReferencia)
            contador++;
    }
    return contador;
}

struct Fundacion **quitarFundaciones (struct Fundacion **fundaciones, int montoReferencia) {

    int indiceArregloOriginal, indiceArregloNuevo;
    struct Fundacion **fundacionesQuitadas=NULL;

    /*Si existen fundaciones que cumplen el criterio*/
    if(contarFundacionesBajoMontoReferencia(fundaciones,montoReferencia)>0)
    {
        /*Creamos el arreglo nuevo con malloc*/
        fundacionesQuitadas=(struct Fundacion**)malloc(contarFundacionesBajoMontoReferencia(fundaciones,montoReferencia)*sizeof(struct Fundacion*));

        indiceArregloNuevo=0;
        for(indiceArregloOriginal=0; indiceArregloOriginal<cantFundaciones; indiceArregloOriginal++)
        {
            if(fundaciones[indiceArregloOriginal]!=NULL && calcularMontoAcumuladoTraspasos(fundaciones[indiceArregloOriginal]->traspasos, fundaciones[indiceArregloOriginal]->pLibre) < montoReferencia)
            {
                /*Copiamos puntero desde arreglo original al arreglo de destino*/
                fundacionesQuitadas[indiceArregloNuevo]=fundaciones[indiceArregloOriginal];
                indiceArregloNuevo++;

                /*Quitamos del arreglo existente*/
                fundaciones[indiceArregloOriginal]=NULL;
            }
        }
    }
    return fundacionesQuitadas;
}


/*Ejercicio 2.1: Eliminar un traspaso de una fundación, considerando que los traspasos NO estan ordenados*/

int eliminarTraspasoFundacionSinOrdenNumero(struct Traspaso **traspaso, int pLibre, int numeroTraspaso)
{
    int i;

    /*Buscar el traspaso,
     * Cuando lo encuentra hace null la posicion
     * Luego compacta
     * Finalmente retorn 1*/

    for(i=0; i<pLibre; i++)
    {
        if(traspaso[i]->numero==numeroTraspaso)
        {
            /*1ero: Eliminación*/
            traspaso[i]=NULL;

            /*2do: Compactación en arreglo NO ordenado*/
            traspaso[i]=traspaso[pLibre-1];
            traspaso[pLibre-1]=NULL;
            pLibre--;

            /*Retornamos éxito*/
            return 1;
        }
    }
    return 0;
}

int eliminarTraspasoSinOrdenNumero(struct Fundacion **fundaciones, int idFundacion, int numeroTraspaso)
{
    int i;

    for(i=0; i<cantFundaciones; i++)
    {
        if(fundaciones[i]!=NULL && fundaciones[i]->id==idFundacion)
            return eliminarTraspasoFundacionSinOrdenNumero(fundaciones[i]->traspasos,fundaciones[i]->pLibre,numeroTraspaso);
    }
    return 0;
}

/*Ejercicio 2.2: Eliminar un traspaso de una fundación, considerando que los traspasos SI estan ordenados*/

int eliminarTraspasoFundacionConOrdenNumero(struct Traspaso **traspaso, int pLibre, int numeroTraspaso)
{
    int i, j;

    /*Buscar el traspaso,
     * Cuando lo encuentra hace null la posicion
     * Luego compacta en un arreglo ordenado
     * Finalmente retorn 1*/

    for(i=0; i<pLibre; i++)
    {
        if(traspaso[i]->numero==numeroTraspaso)
        {
            /*1ero: Eliminación*/
            traspaso[i]=NULL;

            /*2do: Compactación en arreglo NO ordenado*/
            for(j=i; j<pLibre-1; j++)
                traspaso[j]=traspaso[j+1];

            traspaso[pLibre-1]=NULL;
            pLibre--;

            /*Retornamos éxito*/
            return 1;
        }
    }
    return 0;
}

int eliminarTraspasoConOrdenNumero(struct Fundacion **fundaciones, int idFundacion, int numeroTraspaso)
{
    int i;

    for(i=0; i<cantFundaciones; i++)
    {
        if(fundaciones[i]!=NULL && fundaciones[i]->id==idFundacion)
            return eliminarTraspasoFundacionSinOrdenNumero(fundaciones[i]->traspasos,fundaciones[i]->pLibre,numeroTraspaso);
    }
    return 0;
}







/*Compactar un arreglo*/



int main() {
    struct Fundacion **fundaciones;
    printf("Hello, World!\n");
    return 0;
}
