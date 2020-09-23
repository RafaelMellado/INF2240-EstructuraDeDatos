#include <stdio.h>
#include <stdlib.h>
#define tamCancionesArtista 1000

struct Spotify
{
    int cantidadUsuarios;
    int numeroLicencia;
    NodoArtista *headArtistas;
    NodoUsuario *headUsuarios;
};

struct NodoArtista
{
    struct Artista *datosArtista;
    struct NodoArtista *sig;
};

struct Artista
{
    int id;
    char *nombre;
    char *nacionalidad;
    struct Cancion **canciones;
};

struct Cancion
{
    int id;
    char *nombre;
    int duracion;
};

struct NodoUsuario
{
    struct Usuario *datosUsuario;
    struct NodoUsuario *sig;
};

struct Usuario
{
    int id;
    char *correoElectronico;
    int montoSuscripcion;
    struct Cancion **cancionesFavoritas;
    int pLibreCanciones;
};

int contarCancionFavorita(struct Cancion **cancionesFavoritas, int pLibre, int idCancion)
{
    int contador=0, i;
    
    for(i=0; i<pLibre; i++)
    {
        if(idCancion==cancionesFavoritas[i]->id)
            contador++;
    }
    return contador;
}

int contarCancionFavoritaUsuarios(struct NodoUsuario *headUsuarios, int idCancion)
{
    struct NodoUsuario *recUsuarios;
    int contador=0;
    
    if(headUsuarios!=NULL)
    {
        recUsuarios=headUsuarios;
        do
        {
            contador+=contarCancionFavorita(recUsuarios->datosUsuario->cancionesFavoritas,recUsuarios->datosUsuario->pLibreCanciones,idCancion);
            recUsuarios=recUsuarios->sig;
        }while(recUsuarios!=headUsuarios);
    }
    return contador;
}

struct Cancion *cancionMasFavoritaArtista(struct Cancion **cancionesArtista, struct NodoUsuario *listaUsuarios)
{
    struct Cancion *mayor=NULL;
    int i;
    
    for(i=0; i<tamCancionesArtista; i++)
    {
        if(cancionesArtista[i]!=NULL)
        {
            if(mayor==NULL || contarCancionFavoritaUsuarios(listaUsuarios,cancionesArtista[i]->id)>contarCancionFavoritaUsuarios(listaUsuarios,mayor->id))
            {
                mayor=cancionesArtista[i];
            }
        }
    }
    return mayor;
}


int idCancionMasFavorita(NodoArtista *headArtistas, NodoUsuario *headUsuarios)
{
    NodoArtista *recArtistas;
    struct Cancion *mayorTotal=NULL, *mayorCancionArtista;
    
    recArtistas=headArtistas->sig;
    
    while(recArtistas!=NULL)
    {
        mayorCancionArtista=cancionMasFavoritaArtista(recArtistas->datosArtista->canciones, headUsuarios);
        
        if(mayorCancionArtista!=NULL)
        {
            if(mayorTotal==NULL || contarCancionFavoritaUsuarios(headUsuarios,mayorCancionArtista->id)>contarCancionFavoritaUsuarios(headUsuarios,mayorTotal->id))
                mayorTotal=mayorCancionArtista;
        }
        recArtistas=recArtistas->sig;
    }
    return mayorTotal;
}








int main() 
{

    return (EXIT_SUCCESS);
}

