#include <stdio.h>
#include <string.h>
#include <mpi.h>

int idproc, nproc, resultlen;
char nombre[30];

int main (int argc, char** argv)
{
    int i, cant = 0;
    char archivos[4][30];
    cant = argc - 1;

    for(i = 0; i< cant; i++)
    {
        strcpy(archivos[i],argv[i+1]);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idproc);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Get_processor_name(nombre, &resultlen);

    float numeros[20], menor, mayor, promedio = 0, suma = 0;

    FILE * fichero;
    int j = 0;
    fichero = fopen(argv[idproc + 1], "r");
    

    while(!feof(fichero))
    {
        fscanf(fichero, "%f", &numeros[j]);
        j++;
    }
        
    fclose(fichero);

    menor = numeros[0];
    mayor = numeros[0];

    for(i = 0; i < j-1; i++)
    {
        if(numeros[i] < menor)
        {
            menor = numeros[i];
        }
    }

    for(i = 0; i < j-1; i++)
    {
        if(numeros[i] > mayor)
        {
            mayor = numeros[i];
        }
        suma += numeros[i];
    }

    promedio = suma/(float)(j-1);

    char archivos_salida[40];

    strcat(strcpy(archivos_salida,"salida"),archivos[idproc]);

    FILE * fichero_s;
    fichero_s = fopen(archivos_salida, "wt");
    fprintf(fichero_s, "Menor: %.2f\nMayor: %.2f\nPromedio: %.2f", menor, mayor, promedio);
    fclose(fichero);
    MPI_Finalize();
}
