#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxColegios 5000

struct Ministerio
{
    char *nombreMinistro;
    char *direccion;
    struct Colegio **colegios;
};

struct Colegio
{
    char *nombre;
    char *id;
    struct NodoCurso *headCursos;
};

struct NodoCurso
{
    struct DatosCurso *detalleCurso;
    struct NodoCurso *sig;
};

struct DatosCurso
{
    char *nombre;
    int sigla;
    int grado;
    struct nodoAlumno *headAlumnos;
};

struct NodoAlumno
{
    struct DatosAlumno *detalleAlumno;
    struct NodoAlumno *sig;
};

struct DatosAlumno
{
    char *nombre;
    char *direccion;
    char *rut;
    int puntajeObtenido;
};

float getPromedioPuntajeAlumnosCurso(struct nodoAlumno *headAlumnos)
{
    float promedio=0;
    int contador=0;

    while(headAlumnos!=NULL)
    {
        promedio+=headAlumnos->detalleAlumno->puntajeObtenido;
        contador++;
        headAlumnos=headAlumnos->sig;
    }

    if(contador>0)
        return promedio/contador;
    return 0;
}

float getPromedioPuntajeColegio(struct NodoCurso *headCursos)
{
    float promedio=0;
    int contador=0;

    while(headCursos!=NULL)
    {
        promedio+= getPromedioPuntajeAlumnosCurso(headCursos->detalleCurso->headAlumnos);
        contador++;
        headCursos=headCursos->sig;
    }

    if(contador>0)
        return promedio/contador;
    return 0;
}

struct Colegio *getColegioMenorPuntajePSU(struct Colegio **colegios)
{
    int i;
    struct Colegio *menor=NULL;

    for(i=0; i<maxColegios; i++)
    {
        if(colegios[i]!=NULL && (menor==NULL || getPromedioPuntajeColegio(colegios[i]->headCursos)< getPromedioPuntajeColegio(menor->headCursos)))
            menor=colegios[i];
    }
    return menor;
}

struct Colegio *quitarColegio(struct Ministerio *mineduc)
{
    struct Colegio *quitado=NULL;
    int i;

    quitado= getColegioMenorPuntajePSU(mineduc->colegios);
    if(quitado!=NULL)
    {
        for(i=0; i<maxColegios; i++)
        {
            if(mineduc->colegios[i]!=NULL && mineduc->colegios[i]==quitado)
            {
                mineduc->colegios[i]=NULL;
                return quitado
            }
        }
    }
    return quitado;
}

struct DatosCurso *getCurso(struct NodoCurso *cursos, int sigla)
{
    while(cursos!=NULL)
    {
        if(cursos->detalleCurso->sigla==sigla)
            return cursos->detalleCurso;
        cursos=cursos->sig;
    }
    return NULL;
}

struct DatosAlumno *getAlumno(struct NodoAlumno *alumnos, char *rutAlumno)
{
    struct NodoAlumno *rec= alumnos;

    while(rec!=NULL)
    {
        if(strcmp(rutAlumno, rec->detalleAlumno->rut)==0)
            return rec->detalleAlumno;
        rec=rec->sig;
    }
    return NULL;
}

struct DatosCurso *buscarCursoDeAlumno(struct NodoCurso *cursos, char *rutAlumno)
{
    while(cursos!=NULL)
    {
        if(getAlumno(cursos->detalleCurso->headAlumnos,rutAlumno)!=NULL)
            return cursos->detalleCurso;
        cursos=cursos->sig;
    }
    return NULL;
}

int agregarAlumnoCurso(struct NodoAlumno **alumnos, struct DatosAlumno *alumno)
{
    struct NodoAlumno *rec;

    if(*alumnos==NULL)
    {
        *alumnos=(struct NodoAlumno *)malloc(sizeof(struct NodoAlumno));
        (*alumnos)->detalleAlumno=alumno;
        (*alumnos)->sig=NULL;
    }
    else
    {
        rec=*alumnos;
        while(rec->sig!=NULL)
            rec=rec->sig;

        rec->sig=(struct NodoAlumno *)malloc(sizeof(struct NodoAlumno));
        rec->sig->detalleAlumno=alumno;
        rec->sig->sig=NULL;
    }
    return 1;
}



struct DatosAlumno *quitarAlumnoCurso(struct NodoAlumno **headAlumnos, char *rutAlumno)
{
    struct NodoAlumno *rec;
    struct DatosAlumno *respaldo=NULL;

    if(strcmp((*headAlumnos)->detalleAlumno->rut,rutAlumno)==0)
    {
        respaldo=(*headAlumnos)->detalleAlumno;
        *headAlumnos=(*headAlumnos)->sig;
        return respaldo;
    }
    else
    {
        rec=*headAlumnos;
        while(rec->sig!=NULL)
        {
            if(strcmp(rec->sig->detalleAlumno->rut,rutAlumno)==0)
            {
                respaldo=(*headAlumnos)->detalleAlumno;
                rec->sig=rec->sig->sig;
                return respaldo;
            }
            rec=rec->sig;
        }
    }
    return NULL;
}

int cambiarAlumnoDeCurso(struct Ministerio *mineduc, char *rutAlumno, char *idColegio, int SiglaCursoNuevo)
{
    int i;
    struct DatosCurso *cursoOrigen, *cursoDestino;

    for(i=0; i<maxColegios; i++)
    {
        if(mineduc->colegios[i]!=NULL && strcmp(mineduc->colegios[i]->id,idColegio)==0)
        {
            cursoOrigen=getCurso(mineduc->colegios[i]->headCursos,SiglaCursoNuevo);
            cursoDestino=buscarCursoDeAlumno(mineduc->colegios[i]->headCursos,rutAlumno);
            if(cursoOrigen!=NULL && cursoDestino!=NULL)
                return agregarAlumnoCurso(&(cursoDestino->headAlumnos),quitarAlumnoCurso(cursoOrigen->headAlumnos,rutAlumno));
        }
    }
    return 0;
}


int main() {
    printf("Hello, World!\n");
    return 0;
}
