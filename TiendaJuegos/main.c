#include <stdio.h>
#include <stdlib.h>

struct Juego{
    int codigo;
    char *nombre;
    char *categoria;
    int valor;
};

/*Ejercicio 1: agregar un nuevo juego al arreglo*/
int buscarJuego(struct Juego **juegos, int tam, int codigoBuscado)
{
    int i;
    for(i=0; i<tam; i++)
    {
        if(juegos[i]!=NULL && juegos[i]->codigo==codigoBuscado)
            return 1;
    }
    return 0;
}

struct Juego *crearJuegoNuevo(int codigoNuevo, char *nombreNuevo, char *categoriaNueva, int valorNuevo)
{
    struct Juego *juegoNuevo;

    juegoNuevo=(struct Juego *)malloc(sizeof (struct Juego));

    juegoNuevo->codigo=codigoNuevo;
    juegoNuevo->nombre=nombreNuevo;
    juegoNuevo->categoria=categoriaNueva;
    juegoNuevo->valor=valorNuevo;

    return juegoNuevo;
}

int agregarJuegoNuevo(int codigoNuevo, char *nombreNuevo, char *categoriaNueva, int valorNuevo, struct Juego **juegos, int tam)
{
    struct Juego *nuevoJuego=NULL;
    int i=0;
    /*Buscamos que no esté repetido*/

    if(buscarJuego(juegos,tam,codigoNuevo)==0)
    {
        for(i=0; i<tam, i++){
            if(juegos[i]==NULL){
                juegos[i]=crearJuegoNuevo(codigoNuevo,nombreNuevo,categoriaNueva,valorNuevo);
                return 1;
            }
        }
    }
    return 0;
}

//------ CON ARREGLO COMPACTO

int buscarJuegoCompacto(struct Juego **juegos, int pLibre, int codigoBuscado)
{
    int i;
    for(i=0; i<pLibre; i++)
    {
        if(juegos[i]->codigo==codigoBuscado)
            return 1;
    }
    return 0;
}


int agregarJuegoNuevoCompacto(int codigoNuevo, char *nombreNuevo, char *categoriaNueva, int valorNuevo, struct Juego **juegos, int tam, int *pLibre)
{
    struct Juego *nuevoJuego=NULL;
    int i=0;
    /*Buscamos que no esté repetido*/

    if(buscarJuegoCompacto(juegos,*pLibre,codigoNuevo)==0 && *pLibre<tam)
    {
        /*agregar Compacto*/
        juegos[*pLibre]=crearJuegoNuevo(codigoNuevo,nombreNuevo,categoriaNueva,valorNuevo);
        (*pLibre)++;
         return 1;
    }
    return 0;
}






int main() {

    struct Juego **juegos;
    int pLibre=0;
    int tam;

    do {
        /*1. Saber el tamaño*/
        printf("Ingrese la cantidad de juegos maxima a registrar:");
        scanf("%d",&tam);
    }while(tam<=0);

    /*2. Asignar memoria*/
    juegos=(struct Juego **)malloc(tam*sizeof (struct Juego *));



    printf("Hello, World!\n");
    return 0;
}
