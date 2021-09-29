#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxRegiones 20
#define maxEnvios 5000

struct ChileanExpress{
    char *nombreGerente;
    struct Region **regiones;
    struct NodoCliente *clientes;
};

struct Region{
    int numero;
    struct NodoSucursal *sucursales;
};

struct NodoCliente{
    struct Cliente *datosCliente;
    struct NodoCliente *ant, *sig;
};

struct Cliente{
    char *rut;
    char *nombre;
    struct NodoEnvio *paquetesEnviados;
};

struct NodoEnvio{
    struct Envio *paquete;
    struct NodoEnvio *sig;
};

struct Envio{
    int id;
    char *fecha;
    int valor;
    int diasDeAtraso;
};

struct NodoSucursal{
    struct Sucursal *datosSucursal;
    struct NodoSucursal *sig;
};

struct Sucursal{
    int id;
    char *direccion;
    struct Envio **paquetesRepartir;
};

/*Funcion que cuenta la cantidad de envíos que tiene un cliente*/
int getCantidadEnviosCliente(struct NodoEnvio *listaEnvios){
    struct NodoEnvio *rec;
    int cont=0;

    rec=listaEnvios->sig;
    while(rec!=NULL)
    {
        cont++;
        rec=rec->sig;
    }
    return cont;
}

struct Envio **getEnviosCliente(struct NodoEnvio *listaEnvios, int *tam){
    struct Envio **enviosCliente;
    struct NodoEnvio *rec;
    *tam=0;

    if(getCantidadEnviosCliente(listaEnvios)>0)
    {
        /*Se crea el arreglo*/
        enviosCliente=(struct Envio **)malloc(getCantidadEnviosCliente(listaEnvios)*sizeof(struct Envio *));

        /*SE LLENA EL ARREGLO*/
        rec=listaEnvios->sig;
        while(rec!=NULL)
        {
            enviosCliente[(*tam)]=rec->paquete;
            rec=rec->sig;
            (*tam)++;
        }
        return enviosCliente;
    }
    return NULL;
}

struct Envio **getEnviosClienteBuscar(struct NodoCliente *listaClientes, char *rutCliente, int *tam){
    struct NodoCliente *rec;
    *tam=0;

    if(listaClientes!=NULL)
    {
        rec=listaClientes;
        do
        {
            if(strcmp(rutCliente,rec->datosCliente->rut)==0)
                return getEnviosCliente(rec->datosCliente->paquetesEnviados, tam);
            rec=rec->sig;
        }while(rec!=listaClientes);
    }
    return NULL;
}

int buscarEnvioSucursal(struct Envio **envios, int idEnvio){
    int i, contador=0;

    for(i=0; i<maxEnvios; i++)
    {
        if(envios[i]!=NULL && envios[i]->id==idEnvio)
            return 1;
    }
    return 0;
}

int getCantidadEnviosClienteEnSucursal(struct Envio **enviosSucursal, struct Envio **enviosCliente, int cantEnviosClientes){
    int i, contador=0;

    for(i=0; i<cantEnviosClientes; i++)
    {
        if(buscarEnvioSucursal(enviosSucursal,enviosCliente[i]->id)==1)
            contador++;
    }
    return contador;
}

int getIdSucursalMasEnviosClienteSucursales(struct NodoSucursal *listaSucursales, struct Envio **enviosCliente, int cantEnviosClientes, int *cantEnviosGanador){
    int idSucursalMayor=0, auxContadorEnvios;
    *cantEnviosGanador=0;

    auxContadorEnvios=getCantidadEnviosClienteEnSucursal(listaSucursales->datosSucursal->paquetesRepartir,enviosCliente,cantEnviosClientes);

    while(listaSucursales!=NULL)
    {
        if(auxContadorEnvios>0 || auxContadorEnvios>*cantEnviosGanador){
            idSucursalMayor=listaSucursales->datosSucursal->id;
            *cantEnviosGanador=auxContadorEnvios;
        }
        listaSucursales=listaSucursales->sig;
    }
    return idSucursalMayor;
}

int getIdSucursalMasEnviosClienteRegiones(struct Region **regiones, struct Envio **enviosCliente, int cantEnviosClientes){
    int i, cantidadGanadora=-1, idGanador=-1, idGanadorRegion=0, cantidadGanadoraRegion=0;

    for(i=0; i<maxRegiones && regiones[i]!=NULL; i++)
    {
        idGanadorRegion=getIdSucursalMasEnviosClienteSucursales(regiones[i]->sucursales,enviosCliente,cantEnviosClientes,&cantidadGanadoraRegion);
        if(idGanador==-1 || cantidadGanadoraRegion>cantidadGanadora)
        {
            idGanador=idGanadorRegion;
            cantidadGanadora=cantidadGanadoraRegion;
        }
    }
    return idGanador;
}

int idSucursalMasOcupada(struct ChileanExpress *CP, char *rutCliente){
    struct Envio **enviosCliente;
    int *tamArregloEnvios;

    /*PASO 1: OBTENER ARREGLO ENVIOS*/
    enviosCliente=getEnviosClienteBuscar(CP->clientes,rutCliente,tamArregloEnvios);
    if(enviosCliente!=NULL)
    {
        /*PASO 2: BUSCAR GANADOR*//*PASO 3: RETORNAR RESULTADO*/
        return getIdSucursalMasEnviosClienteRegiones(CP->regiones,enviosCliente,tamArregloEnvios);
    }

    /*PASO 3: RETORNAR RESULTADO*/
    return -1;
}



int main() {
    printf("Hello, World!\n");
    return 0;
}
