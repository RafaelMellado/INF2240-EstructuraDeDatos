#include <stdio.h>
#include <stdlib.h>
#define maxZombies 10000

struct Zombie
{
    int id;
    char *nombreHumano;
    float indicePeligrosidad;
};

struct Ciudad
{
    char *nombre;
    int codigo;
    char *nombreAlcalde;
    struct Zombie **zombies;
};

struct NodoCiudad
{
    struct Ciudad *ciudad;
    struct NodoCiudad *sig;
};

struct Pais
{
    char *nombre;
    char *nombrePresidente;
    struct NodoCiudad *headCiudades;
};


int main() 
{
    struct Pais *pais;
}

float promedioPeligrosidadCiudad(struct Zombie **zombies)
{
    float suma=0;
    int contador=0, i;
    
    for(i=0; i<maxZombies; i++)
    {
        if(zombies[i]!=NULL)
        {
            suma=suma+zombies[i]->indicePeligrosidad;
            contador++;
        }
    }
    if(contador>0)
    {
        return suma/contador;
    }
    return suma;
}

float promedioPeligrosidadGeneral(struct NodoCiudad *head)
{
    float suma=0;
    int contador=0;
    struct NodoCiudad *rec=head;
    
    while(rec!=NULL)
    {
        if(promedioPeligrosidadCiudad(rec->ciudad->zombies)>0)
        {
            suma=suma+promedioPeligrosidadCiudad(rec->ciudad->zombies);
            contador++;
        }
        rec=rec->sig;
    }
    if(contador>0)
    {
        return suma/contador;
    }
    return suma;
}

int eliminarCiudadesSobrePromedio(struct NodoCiudad **head)
{
    struct NodoCiudad *rec;
    int contador=0, flag=0;
    float promedioGeneral=promedioPeligrosidadGeneral(*head);
    
    if(*head)
    {
        /*CASO EN QUE SEA EL HEAD*/
        while(*head!=NULL && promedioPeligrosidadCiudad(*head->ciudad->zombies)>promedioGeneral)
        {
            *head=*head->sig;
            contador++;
        }
        
        rec=head;
        if(rec!=NULL)
        {
            while(rec->sig!=NULL)
            {
                flag=0;
                if(promedioPeligrosidadCiudad(rec->sig->ciudad->zombies)>promedioGeneral)
                {
                    rec=rec->sig;
                    contador++;
                    flag=1;
                }
                if(flag==0)
                {
                    rec=rec->sig;
                }
            }
        }
    }
    return contador;
}

int contarZombiesPosibleCura(struct Zombie **zombies, float indiceReferencia)
{
    int contador=0, i;
    
    for(i=0; i<maxZombies; i++)
    {
        if(zombies[i]!=NULL && zombies[i]->indicePeligrosidad<indiceReferencia)
        {
            contador++;
        }
    }
    return contador;
}

struct Zombie **zombiesCurables(struct NodoCiudad *ciudadActual, float indiceReferencia)
{
    int i, indice=0;
    struct Zombie **coleccionZombies=NULL;
    
    if(contarZombiesPosibleCura(ciudadActual->ciudad->zombies,indiceReferencia)>0)
    {
        coleccionZombies=(struct Zombie **)malloc(contarZombiesPosibleCura(ciudadActual->ciudad->zombies,indiceReferencia)*sizeof(struct Zombie*));
        
        for(i=0; i<maxZombies; i++)
        {
            if(ciudadActual->ciudad->zombies[i]!=NULL && ciudadActual->ciudad->zombies[i]->indicePeligrosidad<indiceReferencia)
            {
                coleccionZombies[indice]=ciudadActual->ciudad->zombies[i];
                indice++;
            }   
        }
    }
    return coleccionZombies;
}


struct Zombie **zombiesPosibleCura(struct NodoCiudad *head, int codigoCiudad, float indiceReferencia)
{
    struct NodoCiudad *rec;
    
    rec=head;
    while(rec!=NULL)
    {
        if(rec->ciudad->codigo==codigoCiudad)
        {
            return zombiesCurables(rec->ciudad,indiceReferencia);
        }
        rec=rec->sig;
    }
    return NULL;
}




struct Zombie* zombieMasPeligroso(struct Zombie **zombie)
{
    int i;
    struct Zombie *mayor=NULL;
    
    for(i=0; i<maxZombies; i++)
    {
        if(zombie[i]!=NULL && (mayor==NULL || zombie[i]->indicePeligrosidad>mayor->indicePeligrosidad))
        {
            mayor=zombie[i];
        }
    }
    
    if(mayor!=NULL)
    {
        return mayor;
    }
    return NULL;
}

int nombreZombieMasLetal(struct NodoCiudad *head)
{
    struct NodoCiudad *rec;
    struct Zombie *mayor=NULL;
    
    rec=head;
    while(rec!=NULL)
    {
        if(zombieMasPeligroso(rec->ciudad->zombies)!=NULL && (mayor==NULL || (zombieMasPeligroso(rec->ciudad->zombies))->indicePeligrosidad>mayor->indicePeligrosidad))
        {
            mayor=zombieMasPeligroso(rec->ciudad->zombies);
        }
        rec=rec->sig;
    }
    if(mayor!=NULL
    {
        return mayor->id;
    }
    return -1;
}