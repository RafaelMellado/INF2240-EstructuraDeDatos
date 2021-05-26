#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Servel
{
    char *nombreEncargado;
    struct NodoRegion *regiones;
    struct ListaCandidatos *candidatos;
};

struct ListaCandidatos
{
    struct NodoCandidato *ABBCandidatos;
    int cantidadCandidatos;
};

struct NodoCandidato
{
    struct Candidato *datosCandidato;
    struct NodoCandidato *izq, *der;
};

struct Candidato
{
    int idCandidato;
    char *nombre;
    char *nombrePartidoPolitico;
};

struct NodoRegion
{
    struct Region *datosRegion;
    struct NodoRegion *sig;
};

struct Region{
    int numeroRegion;
    char *nombre;
    struct Votante **votantes;
    int cantMaximaVotantes;
};
struct Votante
{
    char *rut;
    char *nombre;
    struct Candidato *voto;
};

struct NodoCandidato *buscarCandidato(struct NodoCandidato *raizCandidatos, int idCandidato)
{
    if(!raizCandidatos || raizCandidatos->datosCandidato->idCandidato==idCandidato)
    {
        return raizCandidatos;
    }
    else
    {
        if(raizCandidatos->datosCandidato->idCandidato>idCandidato)
            return (buscarCandidato(raizCandidatos->izq,idCandidato));
        else
            return (buscarCandidato(raizCandidatos->der,idCandidato));
    }
}

int contarVotosEnRegion(struct Votante **votantes, int cantMaxVotantes, int idCandidato)
{
    int i, contadorVotos=0;
    for(i=0; i<cantMaxVotantes; i++)
    {
        if(votantes[i]!=NULL)
        {
            if(votantes[i]->voto!=NULL && votantes[i]->voto->idCandidato==idCandidato)
                contadorVotos++;
        }
    }
    return contadorVotos;
}

int contarVotosCandidato(struct NodoRegion *headRegiones, int idCandidato)
{
    struct NodoRegion *rec;
    int contadorVotos=0;

    if(headRegiones!=NULL)
    {
        rec=headRegiones;
        while(rec)
        {
            contadorVotos+=contarVotosEnRegion(rec->datosRegion->votantes,rec->datosRegion->cantMaximaVotantes,idCandidato);
            rec=rec->sig;
        }
    }
    return contadorVotos;
}

int totalVotantesEnRegion(struct Votante **votantes, int cantMaxVotantes)
{
    int i, contadorVotantes=0;
    for(i=0; i<cantMaxVotantes; i++)
    {
        if(votantes[i]!=NULL)
            contadorVotantes++;
    }
    return contadorVotantes;
}

int contarTotalVotantes(struct NodoRegion *region)
{
    struct NodoRegion *rec;
    int contadorVotantes=0;

    if(region!=NULL)
    {
        rec=region;
        while(rec)
        {
            contadorVotantes+=totalVotantesEnRegion(rec->datosRegion->votantes,rec->datosRegion->cantMaximaVotantes);
            rec=rec->sig;
        }
    }
    return contadorVotantes;
}

float porcentajeVotosCandidato(struct Servel *elecciones, int idCandidato)
{
    int votosObtenidos=0, votosTotales=0;
    if(elecciones!=NULL)
    {
        if(buscarCandidato(elecciones->candidatos, idCandidato)!=NULL)
        {
            votosObtenidos=contarVotosCandidato(elecciones->regiones,idCandidato);
            votosTotales=contarTotalVotantes(elecciones->regiones);

            if(votosTotales!=0)
            {
                return (votosObtenidos/votosTotales)*100;
            }
        }
    }
    return -1;
}



int main() {
    printf("Hello, World!\n");
    return 0;
}
