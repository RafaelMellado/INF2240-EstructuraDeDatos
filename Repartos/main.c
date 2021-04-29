#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxDestinatarios 5000

struct Destinatario
{
    char *rut;
    char *nombre;
    char *direccion;
};

struct Reparto
{
    int numero;
    char *fecha;
    char *ciudadOrigen;
    struct Destinatario *destino;
};

struct NodoReparto
{
    struct Reparto *datosReparto;
    struct NodoReparto *sig;
};

struct ServiExpress
{
    struct NodoReparto *headRepartos;
    struct Destinatario **destinatarios;
};

int contarRespartosDestinatario(struct NodoReparto *repartos, char *rutDestinatario) {
    int contador = 0;

    while (repartos->sig != NULL) {
        if (strcmp(repartos->sig->datosReparto->destino->rut, rutDestinatario) == 0)
            contador++;
        repartos = repartos->sig;
    }
    return contador;
}

char * rutDestinatarioConMasRepartos(struct ServiExpress *empresa)
{
    char *clienteMayor=NULL;
    int cantidadMayor=0;
    int i;

    for(i=0; i<maxDestinatarios && empresa->destinatarios[i]!=NULL; i++)
    {
        if(clienteMayor==NULL || contarRespartosDestinatario(empresa->headRepartos,empresa->destinatarios[i]->rut)>cantidadMayor)
        {
            clienteMayor=empresa->destinatarios[i]->rut;
            cantidadMayor=contarRespartosDestinatario(empresa->headRepartos,empresa->destinatarios[i]->rut);
        }
    }
    return clienteMayor;
}

struct Reparto *quitarRepartoSinNodoFantasma(struct NodoReparto **repartos, int numeroReparto)
{
    struct Reparto *repartoQuitado=NULL;
    struct NodoReparto *rec;

    /*Caso que sea el head*/
    if((*repartos)->datosReparto->numero==numeroReparto)
    {
        repartoQuitado=(*repartos)->datosReparto;
        *repartos=(*repartos)->sig;
        return repartoQuitado;
    }
    else
    {
        rec=*repartos;
        while(rec->sig!=NULL)
        {
            if(rec->sig->datosReparto->numero==numeroReparto)
            {
                repartoQuitado=rec->sig->datosReparto;
                rec->sig=rec->sig->sig;
                return repartoQuitado;
            }
            rec=rec->sig;
        }
    }
    return repartoQuitado;
}


struct Reparto *quitarRepartoConNodoFantasma(struct NodoReparto *repartos, int numeroReparto)
{
    struct Reparto *repartoQuitado=NULL;
    struct NodoReparto *rec=repartos;

    while(rec->sig!=NULL)
    {
        if(rec->sig->datosReparto->numero==numeroReparto)
        {
            repartoQuitado=rec->sig->datosReparto;
            rec->sig=rec->sig->sig;
            return repartoQuitado;
        }
        rec=rec->sig;
    }
    return repartoQuitado;
}







int main() {




}
