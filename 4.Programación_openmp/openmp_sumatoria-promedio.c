// Distrución de tareas con for y uso de variables
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char *argv[] )
{
    int i = 0, N = 0, suma = 0, suma_final = 0, prom = 0, idHilo;
    int datos[50];
    
    if (argc == 3)
    {
        int num = atoi(argv[1]);

        FILE * archivo;
        archivo = fopen(argv[2], "r");

        while(!feof(archivo))
        {
            fscanf(archivo, "%d", &datos[i++]);
            N++;
        }
        fclose(archivo);

        int sumatorias[num];

        #pragma omp parallel for num_threads(num) shared(i, sumatorias) firstprivate(suma, idHilo)
        for(i = 0; i < N-1; i++) 
        {
            idHilo = omp_get_thread_num(); 

            suma += datos[i];    
            sumatorias[idHilo] = suma;
        }
        
        for(i = 0; i < num; i++)
        {
            suma_final += sumatorias[i];
            printf("\nHilo %d\nSumatoria: %d\n", i, sumatorias[i]);
        }

        printf("\nLa sumatoria final es: %d \n", suma_final);
        prom = suma_final/(N-1);
        printf("El promedio es: %d \n\n", prom);
    }


 return 0;
}