#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cantidadMaxima 1000

struct Alumno{
    char *rut;
    char *nombre;
    float promedio;
};

struct Alumno **alumnos;
int pLibre=0;

int buscarAlumno(struct Alumno **alumnos, char *rutBuscado, int pLibre){
    int i=0;
    for(i=0; i<pLibre; i++)
    {
        if(strcmp(alumnos[i]->rut,rutBuscado)==0)
            return 1;
    }
    return 0;
}

int agregarAlumno(struct Alumno **alumnos, int *pLibre, char *rut, char *nombre, float promedio){

    struct Alumno *nuevoAlumno;
    if(pLibre<cantidadMaxima && buscarAlumno(alumnos,rut,*pLibre)==0)
    {
        nuevoAlumno=(struct Alumno *)malloc(sizeof (struct Alumno));
        strcpy(nuevoAlumno->rut,rut);
        strcpy(nuevoAlumno->nombre,nombre);
        nuevoAlumno->promedio=promedio;

        alumnos[*pLibre]=nuevoAlumno;
        (*pLibre)++;
        return 1;
    }
    return 0;
}

char *getAlumnoMejorPromedio(struct Alumno **alumnos, int *pLibre){
    int i, posicionAlumnoMayor=-1;

    if(*pLibre>0)
    {
        posicionAlumnoMayor=*pLibre;

        for(i=0; i<*pLibre; i++)
        {
            if(alumnos[i]->promedio>alumnos[posicionAlumnoMayor]->promedio)
                posicionAlumnoMayor=*pLibre;
        }
    }
    if(posicionAlumnoMayor!=-1)
        return alumnos[posicionAlumnoMayor]->rut;
    return NULL;
}





void hello(void) {
    int resultado;
    alumnos=(struct Alumno **)malloc(cantidadMaxima*sizeof(struct Alumno *));


    resultado= agregarAlumno(alumnos,&pLibre,"21444555-4","Juanito",55);
}
