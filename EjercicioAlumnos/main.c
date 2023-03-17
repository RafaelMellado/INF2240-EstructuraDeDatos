#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam 10000

struct Alumno{
    int id;
    char *nombre;
    float puntaje;
};



int contarAlumnos(struct Alumno **alumnos){
    int contador=0, i;
    for(i=0;i<tam;i++){
        if(alumnos[i]!=NULL)
            contador++;
    }
    return contador;
}

float getPuntajeDestacado(struct Alumno **alumnos){
    float puntajeDestacado=0;
    int i;

    for(i=0; i<tam; i++){
        if(alumnos[i]!=NULL)
            puntajeDestacado+=alumnos[i]->puntaje;
    }
    puntajeDestacado=(puntajeDestacado*contarAlumnos(alumnos))/10000;
    return puntajeDestacado;
}

int getCantidadAlumnosDestacados(struct Alumno **alumnos){
    int contador=0, i;
    for(i=0; i<tam; i++)
    {
        if(alumnos[i]!=NULL && alumnos[i]->puntaje>=getPuntajeDestacado(alumnos))
            contador++;
    }
    return contador;
}

struct Alumno **alumnosDestacados(struct Alumno **alumnos)
{
    struct Alumno **destacados=NULL;
    int i, j, totalDestacados;
    float puntajeDestacado;

    totalDestacados=getCantidadAlumnosDestacados(alumnos);
    puntajeDestacado=getPuntajeDestacado(alumnos);
    if(totalDestacados>0)
    {
        destacados=(struct Alumno**)malloc(totalDestacados*sizeof(struct Alumno*));
        j=0;
        for(i=0;i<tam;i++)
        {
            if(alumnos[i]!=NULL && alumnos[i]->puntaje>=puntajeDestacado)
            {
                destacados[j]=alumnos[i];
                j++;
            }
        }
    }
    return destacados;
}

/****** 2 */

struct Alumno *quitarAlumno(int id, struct Alumno **alumnos)
{
    int i;
    struct Alumno *quitado=NULL;

    for(i=0; i<tam; i++)
    {
        if(alumnos[i]!=NULL && alumnos[i]->id==id)
        {
            quitado=alumnos[i];
            alumnos[i]=NULL;
            return quitado;
        }
    }
    return quitado;
}

int eliminarAlumno(int id, struct Alumno **alumnos)
{
    int i;
    for(i=0; i<tam; i++)
    {
        if(alumnos[i]!=NULL && alumnos[i]->id==id)
        {
            alumnos[i]=NULL;
            return 1;
        }
    }
    return 0;
}

/*3*/

int buscarAlumno(struct Alumno **alumnos, int id)
{
    int i;
    for(i=0; i<tam; i++) {
        if (alumnos[i] != NULL && alumnos[i]->id == id)
            return 1;
    }
    return 0;
}

int agregarAlumno(struct Alumno **alumnos, struct Alumno *nuevo)
{
    int i;
    if(buscarAlumno(alumnos,nuevo->id)==0)
    {
        for(i=0; i<tam; i++)
        {
            if (alumnos[i] == NULL)
            {
                alumnos[i]=nuevo;
                return 1;
            }
        }
    }
    return 0;
}

void compactarAlumnos(struct Alumno **alumnos)
{
    int i, j;
    for(i=0; i<tam; i++)
    {
        if(alumnos[i]==NULL)
        {
            for(j=i; j<tam-1; j++)
                alumnos[j]=alumnos[j+1];

            /*Asigna null al ultimo para que no quede repetido*/
            alumnos[tam-1]=NULL;

            /*Forzar que vuelva a verificar la misma casilla*/
            i--;
        }
    }
}




int main() {
    struct Alumno **alumnos, **alumnosDestacados, *quitado, *nuevo;
    char buffer[1000];

    /*aqui pasó el llenado y todo y todo*/

    alumnosDestacados=alumnosDestacados(alumnos);

    /*2*/
    quitado= quitarAlumno(654,alumnos);
    if(quitado!=NULL)
        printf("El alumno fue quitado existosamente, su nombre es: %s", quitado->nombre);


    /*3*/
    nuevo=(struct Alumno *)malloc(sizeof (struct Alumno));
    printf("ingrese datos:");
    scanf("%d", &(nuevo->id));
    scanf("%s", buffer);
    nuevo->nombre=(char *)malloc(strlen(buffer)*sizeof (char));
    strcpy(nuevo->nombre,buffer);
    scanf("%f", &(nuevo->puntaje));

    if(agregarAlumno(alumnos,nuevo)==1)
        printf("agregado!");


    printf("Hello, World!\n");
    return 0;
}
