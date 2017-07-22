#include <stdio.h>
#define tam 100

main()
{
	int ultValor=0, i, arregloDeValores[tam];

	/*Se agregaran 3 elementos*/
	for(i=0; i<3; i++)
	{
		printf("Ingrese un valor:");
		scanf ("%d", &arregloDeValores[i]);
		ultValor++;
	}

	/*Se muestran los valores usando pLibre*/
	for(i=0; i<=ultValor; i++)
	{
		printf("%d", arregloDeValores[i]);
	}
}
