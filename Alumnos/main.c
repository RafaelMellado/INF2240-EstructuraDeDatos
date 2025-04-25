#include <stdio.h>
#include <stdlib.h>

struct Evaluacion
{
    int id;
    char *fecha;
    int nota;
};

struct Alumno
{
    char *rut;
    char *nombre;
    struct Evaluacion **evaluaciones;
    int tam;
};

struct NodoAlumno
{
    struct Alumno *datosAlumno;
    struct NodoAlumno *sig;
};

struct Curso
{
    int sigla;
    struct NodoAlumno *head;
};

/*
 * Contar cantidad de evaluaciones -- ok
 * El menor en cantidad (alumno) --OK
 * Contar cuantos cumplen con ese menor --OK
 * Crear el arreglo de ese tamaño --OK
 * llenar el arreglo
 * Retornar este arreglo
 * */

int contarEvaluaciones(struct Evaluacion **evaluaciones, int tam)
{
    int cont=0, i;

    for(i=0; i<tam; i++)
    {
        if(evaluaciones[i]!=NULL)
            cont++;
    }
    return cont;
}

struct Alumno *alumnoConMenosEvaluaciones(struct NodoAlumno *head)
{
    struct Alumno *menor=NULL;

    while(head!=NULL)
    {
        if(menor==NULL || contarEvaluaciones(head->datosAlumno->evaluaciones, head->datosAlumno->tam)<
                          contarEvaluaciones(menor->evaluaciones,menor->tam))
        {
            menor=head->datosAlumno;
        }
        head=head->sig;
    }
    return menor;
}

int getCantidadAlumnosMenosEvaluaciones(struct NodoAlumno *headAlumnos)
{
    int contador=0, cantidadMenor;
    struct NodoAlumno *rec;
    struct Alumno *alumnoMenor;

    rec=headAlumnos;
    alumnoMenor= alumnoConMenosEvaluaciones(headAlumnos);

    if(alumnoMenor!=NULL)
    {
        cantidadMenor= contarEvaluaciones(alumnoMenor->evaluaciones, alumnoMenor->tam);

        while(rec!=NULL)
        {
            if(contarEvaluaciones(rec->datosAlumno->evaluaciones,rec->datosAlumno->tam)==cantidadMenor)
                contador++;
            rec=rec->sig;
        }
    }
    return contador;
}

struct Alumno **getAlumnosMenosEvaluaciones(struct NodoAlumno *headAlumnos)
{
    int tamArreglo=0, indice=0, cantidadEvaluaciones=0;
    struct Alumno **arregloMenores=NULL, *alumnoMenor;
    struct NodoAlumno *rec=headAlumnos;

    tamArreglo = getCantidadAlumnosMenosEvaluaciones(headAlumnos);
    if(tamArreglo>0)
    {
        arregloMenores=(struct Alumno **)malloc(tamArreglo*sizeof (struct Alumno*));

        alumnoMenor= alumnoConMenosEvaluaciones(headAlumnos);
        cantidadEvaluaciones= contarEvaluaciones(alumnoMenor->evaluaciones,alumnoMenor->tam);

        while(rec!=NULL)
        {
            if(contarEvaluaciones(rec->datosAlumno->evaluaciones,rec->datosAlumno->tam)==cantidadEvaluaciones)
            {
                arregloMenores[indice]=rec->datosAlumno;
                indice++;
            }
            rec=rec->sig;
        }
    }
    return arregloMenores;
}


int main(void) {
    printf("Hello, World!\n");
    return 0;
}
