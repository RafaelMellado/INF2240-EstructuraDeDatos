#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cantidad 5

struct Persona
{
	char *nombre;
	char *carnetIdentidad;
	int edad;
};

struct Persona personas[cantidad];

main()
{
	int i, size;
	char buffer[50];

	for(i=0; i<cantidad; i++)
	{
		printf("Ingrese nombre: ");
		scanf(" %[^\n]", buffer);
		size=strlen(buffer);
		personas[i].nombre=(char *) malloc (size*sizeof(char));
		strcpy(personas[i].nombre, buffer);

		printf("Ingrese rut: ");
		scanf(" %[^\n]", buffer);
		size=strlen(buffer);
		personas[i].carnetIdentidad=(char *) malloc (size*sizeof(char));
		strcpy(personas[i].carnetIdentidad, buffer);

		printf("Ingrese edad: ");

		scanf("%d", &personas[i].edad);
	}
}