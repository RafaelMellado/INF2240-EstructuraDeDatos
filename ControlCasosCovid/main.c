#include <stdio.h>
#include <stdlib.h>
#define maxContactos 1000

struct Asistente{
    int id;
    char *nombre;
    int edad;
    char *fonoContacto;
};

struct NodoAsistente{
    struct Asistente *asistente;
    struct NodoAsistente *izq, *der;
};

struct Evento{
    int id;
    char *fecha;
    char *nombre;
    struct NodoAsistente *abbAsistentes;
};

struct NodoEvento{
    struct Evento *datosEvento;
    struct NodoEvento *sig;
};

struct Caso{
    int numero;
    struct Asistente **contactos;
};

struct NodoCaso{
    struct Caso *caso;
    struct NodoCaso *ant, *sig;
};

struct SistemaEventos{
    struct NodoEvento *eventos;
    struct NodoCaso *casos;
};

int buscarAsistente(struct NodoAsistente *abbAsistentes, int idAsistente){

    /*Verificamos que exista el nodo que se está visitando*/
    if(abbAsistentes!=NULL)
    {
        if(abbAsistentes->asistente->id==idAsistente)
            return 1;
        return buscarAsistente(abbAsistentes->izq,idAsistente);
        return buscarAsistente(abbAsistentes->der,idAsistente);
    }
    return 0;
}

int buscarAsistenteEnEvento(struct NodoEvento *eventos, int idAsistente){

    while(eventos->sig!=NULL)
    {
        if(buscarAsistente(eventos->sig->datosEvento->abbAsistentes,idAsistente))
            return 1;
        eventos=eventos->sig;
    }
    return 0;
}

int buscarAsistenteEnCaso(struct Asistente **contactos, int idAsistente){
    int i;

    for(int i=0; i<maxContactos; i++)
    {
        if(contactos[i]!=NULL && contactos[i]->id==idAsistente)
            return 1;
    }
    return 0;
}

int contarContactosEstrechosAsistente(struct NodoCaso *casos, int idAsistente){
    int contadorCasosPositivos=0;

    while(casos!=NULL)
    {
        if(buscarAsistenteEnCaso(casos->caso->contactos,idAsistente)==1)
            contadorCasosPositivos++;
        casos=casos->sig;
    }
    return contadorCasosPositivos;
}

int getCantidadCasosPersona(struct SistemaEventos *se, int idAsistente)
{
    /*Si existe la persona en al menos un evento*/
    if(buscarAsistenteEnEvento(se->eventos,idAsistente)==1)
        return contarContactosEstrechosAsistente(se->casos,idAsistente);
    return 0;
}




int main() {
    printf("Hello, World!\n");
    return 0;
}
