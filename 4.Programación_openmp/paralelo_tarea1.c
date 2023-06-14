#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{  
    int menores[argc-1], mayores[argc-1], i = 0;

    if(argc > 1)
    {
        int num = argc - 1;

        #pragma omp parallel num_threads(num)
        {
            int numeros[20], i = 0, menor, mayor;
            int  IdHilo,NumHilos, NumCPUs;  

            IdHilo = omp_get_thread_num();  

            FILE * fichero;
            int j = 0, cant = 0;
            fichero = fopen(argv[IdHilo + 1], "r");

            while(!feof(fichero))
            {
                fscanf(fichero, "%d", &numeros[j++]);
                cant++;
            }
                
            fclose(fichero);

            menor = numeros[0];
            mayor = numeros[0];
        
            for(i = 0; i < cant-1; i++)
            {
                if(numeros[i] < menor)
                {
                    menor = numeros[i];
                }
            }

            menores[IdHilo] = menor;

            for(i = 0; i < cant-1; i++)
            {
                if(numeros[i] > mayor)
                {
                    mayor = numeros[i];
                }
            }

            mayores[IdHilo] = mayor;
        }
    }

    printf("\nMENORES\n");

    for(i = 0;i < argc-1; i++)
    {
        printf("%d, ", menores[i]);
    }
    printf("\n\n");

    printf("MAYORES\n");

    for(i = 0;i < argc-1; i++)
    {
        printf("%d, ", mayores[i]);
    }

return 0;
}

