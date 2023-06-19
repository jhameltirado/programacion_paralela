#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int N = 0, i = 0, suma = 0, inferiores = 0, superiores = 0;
    float media = 0;

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

    media = (float)suma/(float)(N-1);  
    printf("La media es: %.2f\n", media);

    #pragma omp parallel sections 
    {
        #pragma omp section // inferiores
        {
            printf("INFERIORES\n");
            for(i = 0; i < N-1; i++)
            {
                if((float)datos[i] < media)
                {
                    inferiores++;
                    printf("%d\n", datos[i]);
                }
            }
        }
        #pragma omp section // superiores
        {
            printf("SUPERIORES\n");
            for(i = 0; i < N-1; i++)
            {
                if((float)datos[i] > media)
                {
                    superiores++;
                    printf("%d\n", datos[i]);
                }
            }
        }
    }

    printf("Hay %d inferiores a la media\n", inferiores);
    printf("Hay %d superiores a la media\n", superiores);

}