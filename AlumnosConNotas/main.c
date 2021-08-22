#include <stdio.h>
#include <string.h>
#define maxNotas 30
#define maxAlumnos 1000

struct Evaluacion{
    int id;
    int nota;
};

struct Alumno{
    char *rut;
    char *nombre;
    struct Evaluacion **evaluaciones;
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

int eliminarAlumno(struct Alumno **alumnos, int *pLibre, char *rutAlumnoEliminar){

    int i;

    if(buscarAlumno(alumnos,rutAlumnoEliminar,pLibre)==1)
    {
        for(i=0; i<pLibre; i++)
        {
            if(strcmp(alumnos[i]->rut,rutAlumnoEliminar)==0)
            {
                alumnos[i]=NULL;
                alumnos[i]=alumnos[(*pLibre)-1];
                alumnos[(*pLibre)-1]=NULL;
                (*pLibre)--;

                return 1;
            }
        }
    }
    return 0;
}

struct Alumno* quitarAlumno(struct Alumno **alumnos, int *pLibre, char *rutAlumnoEliminar){

    int i;
    struct Alumno *eliminado=NULL;

    if(buscarAlumno(alumnos,rutAlumnoEliminar,pLibre)==1)
    {
        for(i=0; i<pLibre; i++)
        {
            if(strcmp(alumnos[i]->rut,rutAlumnoEliminar)==0)
            {
                eliminado=alumnos[i];
                alumnos[i]=NULL;
                alumnos[i]=alumnos[(*pLibre)-1];
                alumnos[(*pLibre)-1]=NULL;
                (*pLibre)--;

                return eliminado;
            }
        }
    }
    return NULL;
}














float getPromedio(struct Evaluacion **evaluaciones){
    int i, notasValidas=0, acumuladorNotas=0;
    float promedio=0;

    for(i=0; i<maxNotas; i++)
    {
        if(evaluaciones[i]!=NULL){
            acumuladorNotas+=evaluaciones[i]->nota;
            notasValidas++;
        }
    }

    if(notasValidas>0)
        promedio=(float)acumuladorNotas/notasValidas;

    return promedio;
}

char *getAlumnoMejorPromedio(struct Alumno **alumnos, int *pLibre){
    int i, posicionAlumnoMayor=-1;

    if(*pLibre>0)
    {
        posicionAlumnoMayor=*pLibre;

        for(i=0; i<*pLibre; i++)
        {
            if(getPromedio(alumnos[i]->evaluaciones)> getPromedio(alumnos[posicionAlumnoMayor]->evaluaciones))
                posicionAlumnoMayor=*pLibre;
        }
    }
    if(posicionAlumnoMayor!=-1)
        return alumnos[posicionAlumnoMayor]->rut;
    return NULL;
}




int main() {
    printf("Hello, World!\n");
    return 0;
}
