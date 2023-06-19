#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int triangular_superior(int (*datos)[4])
{
    int suma_ts = 0, i, j, c = 4;

    for(i = 0; i < c; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(i < j)
            {
                suma_ts+= datos[i][j];
            }
        }
    }
    return suma_ts;
}

int triangular_inferior(int (*datos)[4])
{
    int suma_ti = 0, i, j, c = 4;

    for(i = 0; i < c; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(i > j)
            {
                suma_ti+= datos[i][j];
            }
        }
    }
    return suma_ti;
}

int diagonal(int (*datos)[4])
{
    int suma_d = 0, i, j, c = 4;

    for(i = 0; i < c; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(i == j)
            {
                suma_d+= datos[i][j];
            }
        }
    }
    return suma_d;
}

int main(int argc, char *argv[])
{
    int f = 0, c = 0, i = 0, j = 0, suma_d = 0, suma_ts = 0, suma_ti = 0;
    float media = 0;

    int datos[4][4];

    FILE * archivo;
    archivo = fopen(argv[1], "r");

    while(!feof(archivo))
    {
        fscanf(archivo, "%d", &datos[c][f]);
        f++;

        if(f == 4)
        {
            c++;
            f = 0;       
        }
    }

    fclose(archivo);

    #pragma omp parallel sections 
    {
        #pragma omp section // diagonal
        {
            suma_d = diagonal(datos);
        }
        #pragma omp section // trangular superior
        {
            suma_ts = triangular_superior(datos);
        }
        #pragma omp section // triangular inferior
        {
            suma_ti = triangular_inferior(datos);
        }
    }

    printf("Suma diagonal =  %d\n", suma_d);
    printf("Suma triangular superior =  %d\n", suma_ts);
    printf("Suma triangular inferior =  %d\n", suma_ti);
}