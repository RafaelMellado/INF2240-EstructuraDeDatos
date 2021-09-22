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

struct NodoConvencional{
    struct Convencional *datosConvencional;
    struct NodoConvencional *ant, *sig;
};

struct ConvencionConstitucional{
    char *fechaInicio:
    char *fechaFin;
    char *nombrePresidente;
    struct NodoConvencional *convencionales;
    struct Distrito **distritos;

};

int contarConvencionalesDistrito(struct NodoConvencional *head, int idDistrito){
    int contador=0;
    struct NodoConvencional *rec;

    /*Caso lista no vacia*/
    if(head!=NULL)
    {
        rec=head;
        do{
            /*Si el elemento en la lista es un convencional de ese distrito*/
            if(rec->datosConvencional->distritoRepresentado->id==idDistrito)
                contador++;
            rec=rec->sig;
        }while(rec!=head);
    }

    return contador;
}

struct Convencional **respaldarConvencionalesDistrito(struct NodoConvencional *head, int idDistrito){
    struct Convencional **convencionalesRespaldados=NULL;
    int cantConvencionales, i=0;
    struct NodoConvencional *rec;

    cantConvencionales= contarConvencionalesDistrito(head,idDistrito);

    if(cantConvencionales>0)
    {
        convencionalesRespaldados=(struct Convencional**)malloc(cantConvencionales*sizeof(struct Convencional *));

        if(head!=NULL)
        {
            rec=head;
            do{
                if(rec->datosConvencional->distritoRepresentado->id==idDistrito)
                {
                    convencionalesRespaldados[i]=rec->datosConvencional;
                    i++;
                }
                rec=rec->sig;
            }while(rec!=head);
        }
    }
    return convencionalesRespaldados;
}

void eliminarConvencionalesDistrito(struct NodoConvencional **head, int idDistrito){
    struct NodoConvencional *aux, *rec;

    if(*head!=NULL)
    {
        /*Si fuera el primer elemento*/
        if((*head)->datosConvencional->distritoRepresentado->id==idDistrito)
        {
            (*head)->sig->ant=(*head)->ant;
            (*head)->ant->sig=(*head)->sig;

            /*Ahora lo borramos*/
            aux=(*head)->sig;
            free(*head);
            *head=aux;
        }
        else
        {
            rec=(*head)->sig;
            do{
                if(rec->datosConvencional->distritoRepresentado->id==idDistrito)
                {
                    rec->sig->ant=rec->ant;
                    rec->ant->sig=rec->sig;

                    /*ahora borramos*/
                    aux=rec->sig;
                    free(rec);
                    rec=aux;
                }
                else
                {
                    rec=rec->sig;
                }
            }while(rec!=*head);
        }
    }
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

    /*Respaldo convencionales y quito los convencionales de la lista*/
    convencionalesQuitados=respaldarConvencionalesDistrito(convencion->convencionales,idDistrito);
    eliminarConvencionalesDistrito(convencion->convencionales, idDistrito);

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
