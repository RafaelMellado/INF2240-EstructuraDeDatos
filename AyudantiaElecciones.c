#include <stdio.h>
#include <stdlib.h>
#define CANT 28

struct Candidato
{
	char *rut;
	char *nombre;
	char *partidoPolitico;
	int cantidadVotos;
};

struct NodoCandidato
{
	struct Candidato *candidato;
	struct NodoCandidato *sig;
};

struct Distrito
{
	int numeroDistrito;
	int cantidadDiputados;
	struct NodoCandidato *head;
};

struct Distrito **distritos;

main()
{
	int opcion=0;
	distritos=(struct Distrito**)malloc(CANT*sizeof(struct Distrito*));

	do
	{
		printf("Menu Principal:\n");
		printf(".....");
		scanf("%d, &opcion");

		switch(opcion)
		{
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}

	}while(opcion!=0);

}
