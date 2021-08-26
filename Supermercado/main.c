#include <stdio.h>
#include <stdlib.h>
#define maxArreglos 1000

struct Cliente{
    int numeroCliente;
    char *rut;
    char *nombre;
    int cupo;
};

struct Sucursal{
    int id;
    char *nombre;
    char *direccion;
    struct Cliente **clientes;
};

struct Supermercado{
    char *nombreGerente;
    char *rut;
    struct Sucursal **sucursales;
};

float promedioCuposClientes(struct Cliente **clientes){
    int contador=0, i;
    float promedio=0;

    for(i=0; i<maxArreglos; i++)
    {
        if(clientes[i]!=NULL)
        {
            promedio+=clientes[i]->cupo;
            contador++;
        }
    }

    if(contador>0)
        return promedio/contador;
    return 0;
}

float promedioCupoSucursales(struct Sucursal **sucursales){
    int contador=0, i;
    float promedio=0;

    for(i=0; i<maxArreglos && sucursales[i]!=NULL; i++)
    {
        promedio+= promedioCuposClientes(sucursales[i]->clientes);
        contador++;
    }

    if(contador>0)
        return promedio/contador;
    return 0;
}

struct Sucursal *quitarSucursalCupoMasBajo(struct Sucursal **sucursales){
    int i, posicionAEliminar=-1;
    float menor;
    struct Sucursal *sucursalEliminada=NULL;

    /*BUSCAMOS CUAL SE DEBE ELIMINAR*/
    for(i=0; i<maxArreglos; i++)
    {
        if(posicionAEliminar==-1 || promedioCupoSucursales(sucursales[i]->clientes)< promedioCuposClientes(sucursales[posicionAEliminar]->clientes))
            posicionAEliminar=i;
    }

    /*AHORA ELIMINAMOS*/
    if(posicionAEliminar>-1)
    {
        /*QUITAR Y RESPALDAR*/
        sucursalEliminada=sucursales[posicionAEliminar];
        sucursales[posicionAEliminar]=NULL;

        /*COMPACTAR*/
        for(i=posicionAEliminar; i<maxArreglos-1; i++)
            sucursales[i]=sucursales[i+1];
        sucursales[maxArreglos-1]=NULL;
    }

    return sucursalEliminada;
}

struct Cliente *crearCliente(int numeroCliente, char *rut, char *nombre, int cupo){


    struct Cliente *cliente=(struct Cliente)malloc(sizeof(struct Cliente));

    /*COPIO....*/

    return cliente;
}




int main() {
    struct Sucursal *sucursalEliminada;

    sucursalEliminada= quitarSucursalCupoMasBajo((/*parametros*/));
    if(sucursalEliminada!=NULL)
    {

    }


    printf("Hello, World!\n");
    return 0;
}
