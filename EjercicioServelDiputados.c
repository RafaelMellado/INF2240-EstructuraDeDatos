#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Servel
{
	char *nombreDirector;
	struct Distrito **distritos;
	int pLibreDistritos;
	struct CamaraDiputados *camara;
};

struct Distrito
{
	int numero;
	char *nombre;
	struct NodoCandidato *candidatos;
};

struct CamaraDiputados
{
	char *nombrePresidente;
	struct NodoParlamentario *diputados;
};

struct NodoCandidato
{
	struct Persona *persona;
	struct NodoCandidato *ant, *sig;
};

struct NodoParlamentario
{
	struct Persona *diputado;
	struct NodoParlamentario *sig;
};

struct Persona
{
	char *nombre;
	char *rut;
};


/*Ejercicio 1*/

struct Persona *buscarCandidatoEnUnDistrito(struct NodoCandidato *head, char *rut)
{
	struct NodoCandidato *rec=head;
	
	if(head!=NULL)
	{
		/*Se recorre la lista circular buscando un candidato que tenga el mismo rut*/
		do
		{
			if(strcmp(rec->persona->rut,rut)==0)
			{
				return rec->persona;
			}
			rec=rec->sig;
		}while(rec!=head);
	}
	return NULL;
}

struct Persona *buscarCandidatoEnDistritos(struct Distrito **distritos, int pLibreDistritos, char *rut)
{
	int i;
	
	for(i=0; i<pLibreDistritos; i++)
	{
		if(buscarCandidatoEnUnDistrito(distritos[i]->candidatos, rut)!=NULL)
		{
			return buscarCandidatoEnUnDistrito(distritos[i]->candidatos, rut);
		}
	}
	return NULL;
}

int buscarCandidatoEnCamara(struct CamaraDiputados *camara, struct Persona *diputadoBuscado)
{
	struct NodoParlamentario *rec=camara->diputados;

	/*Recordar que en este caso se parte del siguiente debido a que hay nodo fantasma*/
	while(rec->sig!=NULL)
	{
		if(rec->sig->diputado == diputadoBuscado)
		{
			return 1;
		}
		rec=rec->sig;
	}
	return 0;
}

struct NodoParlamentario *crearNodoParlamentario(struct Persona *diputado, struct NodoParlamentario *sig)
{
	struct NodoParlamentario *nuevo;

	nuevo= (struct NodoParlamentario *)malloc(sizeof(struct NodoParlamentario));
	nuevo->diputado=diputado;
	nuevo->sig=sig;
	
	return nuevo;
}

void agregarDiputadoACamara(struct CamaraDiputados *camara, struct Persona *diputadoNuevo)
{
	struct NodoParlamentario *rec=camara->diputados; 

	/*Se busca el final de la lista, no olvidar el nodo fantasma*/
	while(rec->sig!=NULL)
	{
		rec=rec->sig;
	}

	rec->sig=crearNodoParlamentario(diputadoNuevo,NULL);
}


int agregarDiputado(struct Servel *s, char *rut)
{
	struct Persona *candidato;

	candidato=buscarCandidatoEnDistritos(s->distritos, s->pLibreDistritos, rut);
	
	if(candidato!=NULL)
	{
		/*Buscamos que el candidato no exista ya como diputado*/
		if(buscarCandidatoEnCamara(s->camara,candidato)==0)
		{
			agregarDiputadoACamara(s->camara, candidato);
			return 1;
		}
	}
	return 0;
}


/*Ejercicio 2*/

int contarCandidatosDistrito(struct NodoCandidato *head)
{
	struct NodoCandidato *rec=head;
	int cont=0;

	if(head!=NULL)
	{
		do
		{
			if(rec->persona!=NULL)
			{
				cont++;
			}
			rec=rec->sig;
		}while(rec!=head);
	}
	return cont;
}

char **arregloRutDeCandidatos(struct NodoCandidato *head)
{
	char **arregloCandidatos=NULL;
	struct NodoCandidato *rec=head;
	int indice=0;

	if(contarCandidatosDistrito(head)>0)
	{
		/*Se crea el arreglo de candidatos*/
		arregloCandidatos=(char **)malloc(contarCandidatosDistrito(head)*sizeof(char *));

		/*Se llena el arreglo*/
		if(head!=NULL)
		{
			do
			{
				if(rec->persona!=NULL)
				{
					arregloCandidatos[indice]=rec->persona->rut;
					indice++;
				}
				rec=rec->sig;
			}while(rec!=head);
		}
	}
	return arregloCandidatos;
}


int contarCandidatosQueSonDiputados(struct CamaraDiputados *camara, char ** rutDiputados, int cantRuts)
{
	int contador=0, i, encontrar;
	struct NodoParlamentario *rec= camara->diputados;
	
	while(rec->sig!=NULL)
	{
		encontrar=0;
		for(i=0; i<cantRuts && encontrar==0; i++)
		{
			if(strcmp(rutDiputados[i], rec->sig->diputado->rut)==0)
			{
				contador++;
				encontrar=1;
			}
		}
		rec=rec->sig;
	}

	return contador;
}


int numeroDistritoConMasDiputados(struct Servel *s)
{
	int i, cantidadActual, cantidadMayor;
	struct Distrito *mayor=NULL;

	for(i=0; i<s->pLibreDistritos; i++)
	{
		if(mayor==NULL)
		{
			mayor=s->distritos[i];
		}
		else
		{
			cantidadActual=contarCandidatosQueSonDiputados(s->camara,arregloRutDeCandidatos(s->distritos[i]->candidatos),contarCandidatosDistrito(s->distritos[i]->candidatos));
			cantidadMayor=contarCandidatosQueSonDiputados(s->camara,arregloRutDeCandidatos(mayor->candidatos),contarCandidatosDistrito(mayor->candidatos));
			if(cantidadActual>cantidadMayor)
			{
				mayor=s->distritos[i];
			}
		}
	}

	if(mayor!=NULL)
		return mayor->numero;
	return -1;
}

main()
{
}