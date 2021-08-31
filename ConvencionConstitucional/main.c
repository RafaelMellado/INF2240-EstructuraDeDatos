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

struct ConvencionConstitucional{
    char *fechaInicio:
    char *fechaFin;
    char *nombrePresidente;
    struct Convencional **convencionales;
    struct Distrito **distritos;

};

int main()
{
    struct ConvencionConstitucional **constituyente;

    return 0;
}
