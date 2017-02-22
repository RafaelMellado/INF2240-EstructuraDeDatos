#include <stdio.h>
#define cantFilas 10
#define cantColumnas 15

main()
{
	/*Declaracion*/
	int matrizDeEnteros[cantFilas][cantColumnas];
	int i, j;

	/*Llenado de la coleccion*/
	for(i=0; i<cantFilas; i++)
	{
		for(j=0; j<cantColumnas; j++)
		{
			printf("Ingrese un valor para llenar la matriz:");
			scanf("%d", &matrizDeEnteros[i][j]);
		}
	}

	/*Despliegue de la coleccion*/
	for(i=0; i<cantFilas; i++)
	{
		for(j=0; j<cantColumnas; j++)
		{
			printf("[%d]", matrizDeEnteros[i][j]);
		}
	}
}

