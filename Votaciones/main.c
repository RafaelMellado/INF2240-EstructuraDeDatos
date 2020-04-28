#include <stdio.h>
#include <stdlib.h>
#define maxCiudades 10000

struct Candidato
{
    int numero;
    char *nombre;
    char *partidoPolitico;
};

struct NodoCandidato
{
    struct Candidato *candidato;
    struct NodoCandidato *sig;
};

struct Votante
{
    int id;
    char *nombre;
    struct Candidato *voto;
};

struct NodoVotante
{
    struct Votante *votante;
    struct NodoVotante *sig;
};

struct Ciudad
{
    int numeroUnico;
    char *nombre;
    char *nombreAlcalde;
    struct NodoVotante *votantes;
};

struct Pais
{
    char *nombrePresidente;
    char *nombre;
    struct Ciudad **ciudades;
    struct NodoCandidato *candidatos;
};

int main(int argc, char** argv) 
{
}

int contarVotosCiudad(struct NodoVotante *votantes, struct Candidato *candidato)
{
    struct NodoVotante *rec;
    int votos=0;
    
    rec=rec->sig;
    while(rec!=NULL)
    {
        if(rec->votante->voto==candidato)
        {
            votos+;
        }
        rec=rec->sig;
    }
    return votos;
}

int contarVotosPais(struct Ciudad **ciudad, struct Candidato *candidato)
{
    int i, votos=0;
    
    for(i=0; i<maxCiudades && ciudad[i]!=NULL; i++)
    {
        votos+=contarVotosCiudad(ciudad[i]->votantes,candidato);
    }
    return votos;
}

struct Candidato *candidatoMasVotos(struct NodoCandidato *candidatos, struct Ciudad **ciudades)
{
    struct Candidato mayor=NULL;
    struct NodoCandidato *rec;
    int cantidadVotos=0;
    
    if(candidatos!=NULL)
    {
        rec=candidatos;
        do
        {
            if(mayor==NULL || contarVotosPais(ciudades, rec->candidato)>cantidadVotos)
            {
                mayor=rec->candidato;
                cantidadVotos=contarVotosPais(ciudades, rec->candidato);
            }
            rec=rec->sig;
        }while(rec!=candidatos);
    }
    return mayor;
}

int contarCandidatosMasVotados(struct NodoCandidato *candidatos, struct Ciudad **ciudad, int cantidadVotos)
{
    int contador=0;
    struct NodoCandidato *rec;
    
    if(candidatos!=NULL)
    {
        rec=candidatos;
        do
        {
            if(contarVotosPais(ciudad,rec->candidato)==cantidadVotos)
            {
                contador++;
            }
            rec=rec->sig;
        }while(rec!=candidatos);
    }
    return contador;
}

/* ORIGINAL:
 * 
struct Candidato **candidatosMasVotados(struct Pais *p)
{
    struct NodoCandidato *rec;
    struct Candidato **candidatosMasVotos=NULL;
    int votosMayor=0, posicion;
    
    if(p->candidatos!=NULL)
    {
        if(candidatoMasVotos(p->candidatos,p->ciudades)!=NULL)
        {
            votosMayor=contarCandidatosMasVotados(p->candidatos,p->ciudades, contarVotosPais(p->ciudades,candidatoMasVotos(p->candidatos,p->ciudades)));
            
            if(votosMayor>0)
            {
                candidatosMasVotos=(struct Candidato **)malloc(votosMayor*sizeof(struct Candidato *));
                
                posicion=0;
                rec=p->candidatos;
                do
                {
                    if(contarVotosPais(p->ciudades,rec->candidato)==contarVotosPais(p->ciudades,candidatoMasVotos(p->candidatos,p->ciudades)))
                    {
                        candidatosMasVotos[posicion]=rec->candidato;
                        posicion++;
                    }
                    rec=rec->sig;
                }while(rec!=p->candidatos);
            }
        }
    }
    return candidatosMasVotos;
}
 */

struct Candidato **candidatosMasVotados(struct Pais *p)
{
    struct NodoCandidato *rec;
    struct Candidato **candidatosMasVotos=NULL, *candidatoMayorVotos;
    int votosMayor=0, posicion, auxVotos;
    
    if(p->candidatos!=NULL)
    {
        candidatoMayorVotos=candidatoMasVotos(p->candidatos,p->ciudades);
        if(candidatoMayorVotos!=NULL)
        {
            auxVotos=contarVotosPais(p->ciudades,candidatoMayorVotos);
            votosMayor=contarCandidatosMasVotados(p->candidatos,p->ciudades,auxVotos);
            
            if(votosMayor>0)
            {
                candidatosMasVotos=(struct Candidato **)malloc(votosMayor*sizeof(struct Candidato *));
                
                /*llenado arreglo*/
                posicion=0;
                rec=p->candidatos;
                do
                {
                    if(contarVotosPais(p->ciudades,rec->candidato)==contarVotosPais(p->ciudades,candidatoMayorVotos))
                    {
                        candidatosMasVotos[posicion]=rec->candidato;
                        posicion++;
                    }
                    rec=rec->sig;
                }while(rec!=p->candidatos);
            }
        }
    }
    return candidatosMasVotos;
}
