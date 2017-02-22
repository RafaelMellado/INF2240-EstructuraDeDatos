#include <stdio.h>
#define limite 10

main()
{
	/*Declaracion*/
	int arregloDeEnteros[10];
	int i;

	/*Llenado de la coleccion*/
	for(i=0; i<limite; i++)
	{
		printf("Ingrese un valor para llenar el arreglo:");
		scanf("%d", &arregloDeEnteros[i]);
	}

	/*Despliegue de la coleccion*/
	for(i=0; i<limite; i++)
	{
		printf("[%d]", arregloDeEnteros[i]);
	}
}

