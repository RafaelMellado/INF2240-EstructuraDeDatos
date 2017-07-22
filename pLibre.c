#include <stdio.h>
#define tam 100

main()
{
	int pLibre=0, i, arreglo[tam];

	/*Se agregaran 3 elementos*/
	for(i=0; i<3; i++)
	{
		printf("Ingrese un valor:");
		scanf ("%d", &arreglo[i]);
		pLibre++;
	}

	/*Se muestran los valores usando pLibre*/
	for(i=0; i<pLibre; i++)
	{
		printf("%d", arreglo[i]);
	}

}
