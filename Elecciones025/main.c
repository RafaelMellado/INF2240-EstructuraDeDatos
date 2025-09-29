#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Candidato {
    char *rut;
    char *nombre;
    char *tipo;
    int edad;
};

struct PartidoPolitico {
    char *nombre;
    char *direccion;
    struct Candidato **candidatos;
    int tamCandidatos;
};

struct NodoPartidoPolitico {
    struct PartidoPolitico *datosPartido;
    struct NodoPartidoPolitico *siguiente;
};

struct Votante {
    char *rut;
    char *nombre;
    char *direccion;
    struct Candidato **votos;
    int tamVotos;
};

struct NodoVotante {
    struct Votante *datosVotante;
    struct NodoVotante *siguiente;
};

struct SERVEL {
    char *nombrePresidente;
    struct NodoPartidoPolitico *headPartidos;
    struct NodoVotante *headVotantes;
};

struct Candidato *buscarCandidatoEnCandidatos(struct Candidato **candidatos, int tamCandidatos, char *rutBuscado) {
    int i=0;
    for (i=0; i<tamCandidatos; i++) {
        if (candidatos[i]!=NULL) {
            if (strcmp(rutBuscado, candidatos[i]->rut)==0)
                return candidatos[i];
        }
    }
    return NULL;
}

struct Candidato *buscarCandidatoEnPartidos(struct NodoPartidoPolitico *listaPartidos, char *rutBuscado) {
    struct NodoPartidoPolitico *rec;
    struct Candidato *aux;

    if (listaPartidos!=NULL) {
        rec = listaPartidos;
        do {
            aux=buscarCandidatoEnCandidatos(rec->datosPartido->candidatos,rec->datosPartido->tamCandidatos,rutBuscado);
            if (aux!=NULL)
                return aux;
            rec=rec->siguiente;
        }while (rec!=listaPartidos);
    }
    return NULL;
}



int contarVotos(struct Candidato **votos, int tamVotos, struct PartidoPolitico *partidoBuscado) {
    int contador=0, i;

    for (i=0; i<tamVotos && votos[i]!=NULL; i++) {
        if (buscarCandidatoEnCandidatos(partidoBuscado->candidatos,partidoBuscado->tamCandidatos,votos[i]->rut)!=NULL) {
            contador++;
        }

    }
    return contador;
}


int contarVotosEnVotantes(struct NodoVotante *headVotantes, struct PartidoPolitico *partidoBuscado) {
    int contador=0;
    struct NodoVotante *recVotante;

    recVotante=headVotantes->siguiente;
    while (recVotante!=NULL) {
        contador+=contarVotos(recVotante->datosVotante->votos, recVotante->datosVotante->tamVotos, partidoBuscado);
        recVotante=recVotante->siguiente;
    }
    return contador;
}


struct PartidoPolitico *partidoMasVotos(struct SERVEL *SistemaElectoral) {
    struct NodoPartidoPolitico *recPartidos;
    int contador=0, contadorMayor;
    struct PartidoPolitico *mayor=NULL;

    if (SistemaElectoral->headPartidos!=NULL) {
        recPartidos=SistemaElectoral->headPartidos;
        do {
            contador=contarVotosEnVotantes(SistemaElectoral->headVotantes, recPartidos->datosPartido);
            if (mayor==NULL || contador>contadorMayor) {
                contadorMayor=contador;
                mayor=recPartidos->datosPartido;
            }
            recPartidos=recPartidos->siguiente;
        }while (recPartidos!=SistemaElectoral->headPartidos);
    }
    return mayor;
}

struct Candidato *quitarCandidato(struct SERVEL *sistemaElectoral, char *rutCandidato) {

    /* esta funcion:
     * 1. quita un candidato y retorna un puntero hacia el
     * 2. si no lo encuentra retorna null
     3. debe eliminar todos sus votos desde los votantes (implica compactar).
     */
}

struct Candidato *quitarCandidatoMenosVotos(struct SERVEL *sistemaElectoral, char *tipoCandidato) {

}


int main(void) {
    printf("Hello, World!\n");
    return 0;
}