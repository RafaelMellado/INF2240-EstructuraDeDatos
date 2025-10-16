#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Banco{
    char *nombre;
    char *direccion;
    int saldo;
};

struct NodoBanco{
    struct Banco *datosBanco;
    struct NodoBanco *sig, *ant;
};

struct Robo{
    char *fecha;
    int monto;
    struct Banco *bancoRobado;
};

struct Ladron{
    char *apodo;
    char *rut;
    int maxRobos;
    struct Robo **robos;
    int pLibreRobos;
};

struct NodoLadron{
    struct Ladron *datosLadron;
    struct NodoLadron *sig;
};

struct BandaCriminal{
    char *nombre;
    struct NodoLadron *headLadrones;
    struct NodoBanco *headBancos;
};

int sumarMontosRobadosPorLadron(struct Robo **robos, int PlibreRobos) {
    int suma=0, i;

    for (i=0; i<PlibreRobos; i++)
        suma=suma+(robos[i]->monto);

    return suma;
}

float calcularPromedioRobos(struct NodoLadron *headLadrones) {
    int suma=0, contador=0;
    struct NodoLadron *recorrido;

    if (headLadrones!=NULL)
    {
        recorrido=headLadrones;
        do {
            suma+= sumarMontosRobadosPorLadron(recorrido->datosLadron->robos,recorrido->datosLadron->pLibreRobos);
            contador++;

            recorrido=recorrido->sig;
        }while (recorrido!=headLadrones);
    }

    if (contador>0)
        return ((float)suma)/contador;
    return 0;
}

int contarLadronesBajoPromedio(struct NodoLadron *headLadrones) {
    int contador=0;
    float promedio;
    struct NodoLadron *rec;

    if (headLadrones!=NULL) {
        rec=headLadrones;
        promedio=calcularPromedioRobos(headLadrones);
        do {
            if (sumarMontosRobadosPorLadron(rec->datosLadron->robos,rec->datosLadron->pLibreRobos)<promedio)
                contador++;
            rec=rec->sig;
        }while (rec!=headLadrones);
    }
    return contador;
}

struct Ladron *quitarLadron(struct NodoLadron **headLadrones, char *rut) {
    struct NodoLadron *rec;
    struct Ladron *retorno=NULL;

    if (headLadrones!=NULL) {
        rec=*headLadrones;

        if (strcmp((*headLadrones)->datosLadron->rut,rut)==0) {
            retorno=(*headLadrones)->datosLadron;
            do {
                rec=rec->sig;
            }while (rec->sig!=*headLadrones);
            rec->sig=(*headLadrones)->sig;
            *headLadrones=(*headLadrones)->sig;
            return retorno;
        }
        else {
            do {
                if (strcmp(rec->sig->datosLadron->rut,rut)==0) {
                    retorno=rec->sig->datosLadron;
                    rec=rec->sig;
                    return retorno;
                }
                rec=rec->sig;
            }while (rec->sig!=*headLadrones);
        }
    }
    return NULL;
}


struct Ladron **quitarLadronesMenosRentables(struct BandaCriminal *LosCareNodo) {
    struct Ladron **ladronesNoRentables = NULL;
    int contador=0, i=0;
    float promedio;
    struct NodoLadron *recorrido, *ultimo;

    /*determinar la cantidad*/
    contador=contarLadronesBajoPromedio(LosCareNodo->headLadrones);
    if (contador>0) {
        /*si es mayor a cero hago el malloc*/
        ladronesNoRentables=(struct Ladron **)malloc(contador * sizeof (struct Ladron *));
        promedio=calcularPromedioRobos(LosCareNodo->headLadrones);
        recorrido=LosCareNodo->headLadrones;

        do {
            if (sumarMontosRobadosPorLadron(recorrido->datosLadron->robos,recorrido->datosLadron->pLibreRobos)<promedio) {
                ladronesNoRentables[i]=quitarLadron(LosCareNodo->headLadrones,recorrido->datosLadron->rut);
                i++;
            }
            recorrido=recorrido->sig;
        }while (recorrido!=LosCareNodo->headLadrones);
    }
    return ladronesNoRentables;

}

int main(void) {
    printf("Hello, World!\n");
    return 0;
}