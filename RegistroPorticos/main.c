#include <stdio.h>
#include <stdlib.h>
#define maxRegistros 10000

struct Auto
{
    int id;
    char *patente;
    char *marca;
    char *modelo;
    int anio;
    float consumo;
};

struct NodoAuto
{
    struct Auto *automovil;
    struct NodoAuto *izq, *der;
};

struct Registro
{
    int numero;
    float velocidad;
    char *fecha;
    struct Auto *autoRegistrado;
};

struct Portico
{
    int numeroId;
    char *ubicacion;
    int valorPeaje;
    struct Registro **registros;
    int PLibreRegistros;
};

struct NodoPortico
{
    struct Portico *portico;
    struct NodoPortico *sig;
};

struct Autopista
{
    struct NodoAuto *automoviles;
    struct NodoPortico *porticos;
};


int main() {

}

struct Auto *buscarAutomovil(struct NodoAuto *abb, char *patente)
{
    if(abb)
    {
        if(strcmp(abb->automovil->patente,patente)==0)
        {
            return abb->automovil;
        }
        return buscarAutomovil(abb->izq,patente);
        return buscarAutomovil(abb->der,patente);
    }
    return NULL;
}

struct Registro *buscarRegistroMayor(struct Registro **registros, int pLibreRegistros, struct Auto *automovil)
{
    int i;
    struct Registro *registroMayor=NULL;
    
    for(i=0; i<pLibreRegistros; i++)
    {
        if(registros[i]==automovil)
        {
            if(registroMayor==NULL || registros[i]->velocidad>=registroMayor->velocidad)
            {
                registroMayor=registros[i];
            }
        }
    } 
    return registroMayor;
}

struct Registro *buscarRegistroEnPorticos(struct NodoPortico *headPorticos, int numeroPortico, struct Auto *automovil)
{
    struct NodoPortico *rec;
    
    rec=headPorticos;
    
    while(rec)
    {
        if(rec->portico->numeroId==numeroPortico)
        {
            return buscarRegistroMayor(rec->portico->registros, rec->portico->PLibreRegistros, automovil);
        }
        rec=rec->sig;
    }
    return NULL;
}

float buscarVelocidadAutomovil(struct Autopista *au, char *patente, int numeroPortico)
{
    struct Registro *reg=NULL;
    
    if(buscarAutomovil(au->automoviles,patente)!=NULL)
    {
        reg=buscarRegistroEnPorticos(au->porticos,numeroPortico,buscarAutomovil(au->automoviles,patente));
        
        if(reg!=NULL)
        {
            return reg->velocidad;
        }
    }
    return -1;
}

int contarVecesRegistro(struct Registro **registros, int pLibreRegistros, struct Auto *automovil)
{
    int i, contador=0;
    
    for(i=0; i<pLibreRegistros; i++)
    {
        if(registros[i]->autoRegistrado==automovil)
        {
            contador++;
        }
    }
    return contador;
}

int totalAPagar(struct Autopista *au, char *patente)
{
    struct NodoPortico *rec;
    int totalPagar=0;
    
    if(buscarAutomovil(au->automoviles,patente)!=NULL)
    {
        rec=au->porticos;
        while(rec)
        {
            totalPagar=totalPagar+(rec->portico->valorPeaje*contarVecesRegistro(rec->portico->registros,rec->portico->PLibreRegistros,buscarAutomovil(au->automoviles,patente)));
            rec=rec->sig;
        }
    }
    return totalPagar;
}

int buscarAutoRegistros(struct Registro **registros, int pLibreRegistros, struct Auto *automovil)
{
    int i;
    for(i=0; i<pLibreRegistros; i++)
    {
        if(registros[i]->autoRegistrado==automovil)
        {
            return 1;
        }
    }
    return 0;
}

int buscarAutosPorticos(struct NodoPortico *headPorticos, struct Auto *automovil)
{
    struct NodoPortico *rec;
    int contadorPorticos=0;
    
    rec=headPorticos;
    
    while(rec)
    {
        if(buscarAutoRegistros(rec->portico->registros,rec->portico->PLibreRegistros,automovil)==1)
        {
            contadorPorticos++;
        }
        rec=rec->sig;
    }
    return contadorPorticos;
}

int cantidadPorticosPorAuto(struct Autopista *au, char *patente)
{
    if(buscarAutomovil(au->automoviles,patente)!=NULL)
    {
        return buscarAutosPorticos(au->porticos, buscarAutomovil(au->automoviles,patente));
    }
    return -1;
}

int cantPorticosPorAuto(struct Autopista *au, char *patente)
{
    struct NodoPortico *rec;
    int contadorPorticos=0;
    
    if(buscarAutomovil(au->automoviles,patente)!=NULL)
    {
        rec=au->porticos;
        while(rec!=NULL)
        {
            if(contarVecesRegistro(rec->portico->registros, rec->portico->PLibreRegistros,buscarAutomovil(au->automoviles,patente))>0)
            {
                contadorPorticos++;
            }
            rec=rec->sig;
        }
    }
    return contadorPorticos;
}


