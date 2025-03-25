#include <stdio.h>
#include <stdlib.h>

struct Compra
{
    char *nombreCliente;
    int montoCompra;
    char *fecha;
};
struct Compra **compras;

float getPromedio(struct Compra **compras, int max)
{
    float promedio=0;
    int i, contador=0;

    for(i=0; i<max; i++)
    {
        if(compras[i]!=NULL)
        {
            promedio=promedio + compras[i]->montoCompra;
            contador++;
        }
    }
    if(contador>0)
        return promedio/contador;
    return 0;
}

int contarComprasBajoPromedio(struct Compra **compras, int max, float promedio)
{
    int contador=0, i;

    for(i=0; i<max; i++)
    {
        if(compras[i]!=NULL && compras[i]->montoCompra < promedio)
            contador++;
    }
    return contador;
}

void llenarArregloNuevo(struct Compra **compras, int max, float promedio, struct Compra **arregloNuevo)
{
    int i, indiceNuevo=0;

    for(i=0; i<max; i++)
    {
        if(compras[i]!=NULL && compras[i]->montoCompra < promedio)
        {
            arregloNuevo[indiceNuevo]=compras[i];
            compras[i]=NULL;
            indiceNuevo++;
        }
    }
}

void eliminarComprasBajoPromedio(struct Compra **compras, int max, float promedio)
{
    int i;

    for(i=0; i<max; i++)
    {
        if(compras[i]!=NULL && compras[i]->montoCompra < promedio)
        {
            free(compras[i]);
            compras[i]=NULL;
        }

    }
}




struct Compra ** QuitarClientesMenorCantidadCompras (struct Compra **compras, int max){

    /*
     * 1. vamos a calcular promedio
     * 2. determinaremos si hay compras < al promedio
     * 2.1 Si existen entonces se crea el arreglo nuevo y se procede a su llenado y borrado del arreglo antiguo
     * 2.2 Si no existen, entonces se retorna null*/

    int cantidad;
    float promedio;
    struct Compra **nuevo = NULL;

    promedio= getPromedio(compras,max);
    cantidad= contarComprasBajoPromedio(compras,max,promedio);

    if(cantidad>0)
    {
        nuevo=(struct Compra **)malloc(cantidad*sizeof (struct Compra *));
        llenarArregloNuevo(compras,max,promedio,nuevo);
    }
    return nuevo;
}

int EliminarClientesMenorCantidadCompras (struct Compra **compras, int max){

    int cantidad;
    float promedio;

    promedio= getPromedio(compras,max);
    cantidad= contarComprasBajoPromedio(compras,max,promedio);

    if(cantidad>0)
    {
        eliminarComprasBajoPromedio(compras,max,promedio);
        return 1; //Significa que si eliminó elementos
    }
    return 0; //Significa que no eliminó elementos
}





int main(void) {
    printf("Hello, World!\n");
    return 0;
}
