#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Voto{
    int id;
    char *DNI;
    char *nombreVotante;
    char *nombreCandidato;
};

struct Voto ** crearArreglo(int tam)
{
    struct Voto **arregloNuevo;
    if(tam>0)
    {
        arregloNuevo=(struct Voto **)malloc(tam*sizeof (struct Voto *));
        return arregloNuevo;
    }
    return NULL;
}

struct Voto * crearVoto(int id, char *DNIVotante, char *nombreVotante, char *nombreCandidato)
{
    struct Voto *nuevoVoto;

    /*1. CREAR EL VOTO*/
    nuevoVoto=(struct Voto *)malloc(sizeof (struct Voto));

    /*2. LLENAR CON LOS DATOS
     * 2.1 EN EL CASO DE QUE LA VARIABLE (CAMPO) DEL VOTO SEA CHAR * DEBO DAR MEMORIA */
    nuevoVoto->id=id;
    nuevoVoto->DNI=(char *)malloc(strlen(DNIVotante)*sizeof (char));
    strcpy(nuevoVoto->DNI,DNIVotante);
    nuevoVoto->nombreVotante=(char *)malloc(strlen(nombreVotante)* sizeof(char));
    strcpy(nuevoVoto->nombreVotante,nombreVotante);
    nuevoVoto->nombreCandidato=(char *)malloc(strlen(nombreVotante)* sizeof(char));
    strcpy(nuevoVoto->nombreCandidato,nombreVotante);
    return nuevoVoto;
}

int buscarVoto(struct Voto ** votos, int max, int id)
{
    int i;

    for(i=0; i<max; i++)
    {
        if(votos[i]!=NULL && votos[i]->id==id)
            return 1;
    }
    return 0;
}

int agregarVoto(struct Voto **votos, int max, struct Voto *votoNuevo)
{
    int i;
    if(buscarVoto(votos,max, votoNuevo->id)==0)
    {
        for(i=0; i<max; i++)
        {
            if(votos[i]==NULL)
            {
                votos[i]=votoNuevo;
                return 1;
            }
        }
    }
    return 0;
}

struct Voto *quitarVoto(struct Voto **votos, int max, int idBuscado)
{
    struct Voto *quitado=NULL;
    int i;

    for(i=0; i<max; i++)
    {
        if(votos[i]!=NULL && votos[i]->id==idBuscado)
        {
            quitado=votos[i];
            votos[i]=NULL;
            return quitado;
        }
    }
    return NULL;
}


int eliminarVoto(struct Voto **votos, int max, int idBuscado)
{
    int i;

    for(i=0; i<max; i++)
    {
        if(votos[i]!=NULL && votos[i]->id==idBuscado)
        {
            votos[i]=NULL;
            return 1;
        }
    }
    return 0;
}

void mostrarVotos(struct Voto **votos, int max)
{
    int i;
    for(i=0; i<max; i++)
    {
        if(votos[i]!=NULL)
        {
            printf("\n id voto: %d", votos[i]->id);
            printf("nombre votante: %s", votos[i]->nombreVotante);
        }
    }
}








int main(void) {

    struct Voto **votos;
    struct Voto *votoNuevo, *votoQuitado;
    int cantidad, id, resultado;
    char DNI[100], votante[100], candidato[100];

    /*CREACIÓN DEL ARREGLO*/
    printf("Ingrese la cantidad de votos que desea registrar");
    cantidad= scanf("%d", &cantidad);

    votos= crearArreglo(cantidad);

    if(votos!=NULL)
        printf("Arreglo creado correctamente!");
    else
        printf("Error en la creación del arreglo");

    if(votos!=NULL)
    {
        /*Vamos a crear un voto*/
        printf("Ingrese los datos del voto:");
        scanf("%d", &id);
        scanf("%s", DNI);
        scanf("%s", votante);
        scanf("%s", candidato);

        votoNuevo=crearVoto(id, DNI, votante,candidato);

        /*Agregaremos el voto*/
        resultado= agregarVoto(votos,cantidad,votoNuevo);
        if(resultado==1)
            printf("Voto agregado con éxito!!");
        else
            printf("No se pudo agregar su voto");

        /*Quitar un voto*/
        votoQuitado= quitarVoto(votos,cantidad,677);
        if(votoQuitado!=NULL)
        {
            printf("Voto quitado existosamente.");
            printf("Este voto era para el candidato: %s", votoQuitado->nombreCandidato);
        }
        else
            printf("No se pudo quitar el voto");


        /*Eliminar voto*/
        resultado= eliminarVoto(votos,cantidad,677);
        if(resultado==1)
            printf("Hemos eliminado el voto");
        else
            printf("Voto no se ha podido eliminar");



    }








    printf("Hello, World!\n");
    return 0;
}
