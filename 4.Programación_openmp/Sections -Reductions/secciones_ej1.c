#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int N = 0, i = 0, suma = 0, suma2 = 0;
    float media = 0, desviacion = 0, varianza = 0;
    int datos[50];

    FILE * archivo;
    archivo = fopen(argv[1], "r");

    while(!feof(archivo))
    {
        fscanf(archivo, "%d", &datos[N]);
        N++;
    }

    fclose(archivo);

    #pragma omp parallel for private(i) reduction(+:suma)   
    for(i = 0; i < N-1; i++)
    { 
        suma+=datos[i];
    }
    
    printf("La suma es %d \n",suma);

    media = (float)suma/(float)(N-1);  
    printf("La media es: %.2f\n", media);

    #pragma omp parallel for private(i) reduction(+:suma2)   
    for(i = 0; i < N-1; i++)
    { 
        suma2 += pow((datos[i]-media),2);
    }

    varianza = (float)suma2/(float)(N-1);    
    desviacion = sqrt(varianza);

    printf("La desviación estántar es: %.2f\n", desviacion);
    printf("La varianza es: %.2f\n", varianza);

}