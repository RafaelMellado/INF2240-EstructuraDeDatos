#include <stdio.h>
#include <stdlib.h>

struct Alumno{
    int id;
    char *nombre;
    int edad;
};

struct NodoAlumno{
    struct Alumno *datosAlumno;
    struct NodoAlumno *sig;
};


struct Alumno *crearAlumno(int id, char *nombre, int edad)
{
    struct Alumno *nuevo;

    nuevo=(struct Alumno *)malloc(sizeof (struct Alumno));

    nuevo->id=id;
    nuevo->nombre=nombre;
    nuevo->edad=edad;

    return nuevo;
}

struct Alumno * obtenerAlumno(struct NodoAlumno *head, int idBuscado)
{
    struct NodoAlumno *current;

    current=head;
    while(current!=NULL)
    {
        if(current->datosAlumno->id==idBuscado)
            return current->datosAlumno;
        current=current->sig;
    }
    return NULL;
}

int agregarAlumno(struct NodoAlumno **lista, struct Alumno *nuevo)
{
    struct NodoAlumno *aux, *rec;
    /*Caso 1: lista está vacia*/
    if(*lista==NULL)
    {
        *lista=(struct NodoAlumno *)malloc(sizeof (struct NodoAlumno));
        (*lista)->datosAlumno=nuevo;
        (*lista)->sig=NULL;

        return 1;
    }
    else
    {
        /*Si no está repetido, lo agregaremos*/
        if(obtenerAlumno(*lista, nuevo->id)==NULL)
        {
            rec=*lista;
            while(rec->sig!=NULL)
                rec=rec->sig;

            rec->sig=(struct NodoAlumno *)malloc(sizeof (struct NodoAlumno));
            rec->sig->datosAlumno=nuevo;
            rec->sig->sig=NULL;

            return 1;
        }
    }
    return 0;
}




int main(void) {

    struct NodoAlumno *head=NULL, *nuevoAlumno;
    int resultado;

    nuevoAlumno= crearAlumno(1,"Silvia",22);
    resultado= agregarAlumno(&head,nuevoAlumno);

    if(resultado==1)
        printf("agregado!");
    else
        printf("Fracaso :(");

    return 0;
}
