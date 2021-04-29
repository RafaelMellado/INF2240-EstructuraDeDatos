#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxPasajeros 5000

struct Pasajero
{
    char *DNI;
    char *nombre;
    int edad;
};

struct NodoPasajero
{
    struct Pasajero *pasajero;
    struct NodoPasajero *ant, *sig;
};

struct Avion
{
    int numeroVuelo;
    int capacidad;
    char *destino;
    struct NodoPasajero *listaPasajeros;
};

struct NodoAvion
{
    struct Avion *vuelo;
    struct NodoAvion *sig;
};

struct LineaAerea
{
    struct NodoAvion *flota;
    struct Pasajero **pasajeros;
};


int main() {
    printf("Hello, World!\n");
    return 0;
}
