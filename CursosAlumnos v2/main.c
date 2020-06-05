#include <stdio.h>
#include <stdlib.h>

struct Alumno
{
    int id;
    char *nombre;
    int edad;
};

struct NodoAlumno
{
    struct Alumno *alumno;
    struct NodoAlumno *izq, *der;
};

struct Asignatura
{
    int codigo;
    char *nombre;
    int cantidadHoras;
    int maxInscritos;
    struct Alumno **inscritos;
};

struct NodoAsignatura
{
    struct Asignatura *asignatura;
    struct NodoAsignatura *sig; 
};

struct ListaAsignaturas
{
    struct NodoAsignatura *headAsignatura;
};

struct Colegio
{
    struct NodoAlumno *alumnos;
    struct ListaAsignaturas *asignaturas;
};

int main() {

}

int buscarAlumnoEnAsignatura(struct Alumno **inscritos, int maxInscrito, int idAlumno)
{
    int i;
    for(i=0; i<maxInscrito; i++)
    {
        if(inscritos[i]!=NULL && inscritos[i]->id==idAlumno)
        {
            return 1;
        }
    }
    return 0;
}

int contarAlumnoAsignaturas(struct NodoAsignatura *headAsignaturas, int idAlumno)
{
    int contador=0;
    
    while(headAsignaturas!=NULL)
    {
        contador+=buscarAlumnoEnAsignatura(headAsignaturas->asignatura->inscritos,headAsignaturas->asignatura->maxInscritos, idAlumno);
        headAsignaturas=headAsignaturas->sig;
    }
    return contador;
}

void idAlumnoConMasAsignaturas(struct NodoAlumno *alumno, struct NodoAsignatura *headAsignaturas, struct Alumno *ganador)
{
    if(alumno!=NULL)
    {
        if(*ganador==NULL && contarAlumnoAsignaturas(headAsignaturas, alumno->alumno->id)>contarAlumnoAsignaturas(headAsignaturas, ganador->id))
        {
            *ganador=alumno;
        }
        idAlumnoConMasAsignaturas(alumno->izq, headAsignaturas, ganador);
        idAlumnoConMasAsignaturas(alumno->der, headAsignaturas, ganador);
    }
}