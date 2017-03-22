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

struct Persona *personas[cantidad];

main()
{
	int i, size;
	char buffer[50];

	for(i=0; i<cantidad; i++)
	{
		struct Persona *nueva;
		nueva=((struct Persona*)malloc(sizeof(struct Persona)));


		printf("Ingrese nombre: ");
		scanf(" %[^\n]", buffer);
		size=strlen(buffer);
		nueva->nombre=((char *)malloc(size*sizeof(char)));
		strcpy(nueva->nombre, buffer);

		printf("Ingrese rut: ");
		scanf(" %[^\n]", buffer);
		size=strlen(buffer);
		nueva->carnetIdentidad=((char *)malloc(size*sizeof(char)));
		strcpy(nueva->carnetIdentidad, buffer);

		printf("Ingrese edad: ");
		scanf("%d", &nueva->edad);

		personas[i]=nueva;
	}
}