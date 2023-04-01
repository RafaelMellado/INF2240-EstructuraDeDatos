#include <stdio.h>
#include <stdlib.h>
#define maxCanciones 5000

struct Cancion{
    int id;
    char *nombre;
    int duracion;
    int cantidadReproducciones;
};

struct Artista{
    int id;
    char *nombre:
    char *genero;
    struct Cancion **canciones;
};

struct NodoArtista{
    struct Artista *artista;
    struct NodoArtista *sig;
};

struct Spotify{
    int numeroSuscriptores;
    struct NodoArtista *headArtistas;
};

struct Artista *quitarArtistaCancionConMenosReproducciones (struct Spotify *sptf){

}

int main() {
    struct Cancion
    return 0;
}
