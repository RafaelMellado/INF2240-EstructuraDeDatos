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

int contarAlumnosAsignatura(struct Alumno **alumnosInscritos, int maxInscritos)
{
    int i, contador=0;
    
    for(i=0; i<maxInscritos; i++)
    {
        if(alumnosInscritos[i]!=NULL)
        {
            contador++;
        }
    }
    return contador;
}

