#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

/* 1.1 PROCESOS, TAREA 1:
   Desarrolle el ejercicio anterior tomando los datos desde un archivo de texto 
   y considerando que estos son con fracción decimal.
   El número de datos a procesar del archivo será el primero de ellos (entero).*/ 
 
int main()
{
    int n = 0, i;
    char caracter;
    float num = 0, sum = 0, promedio;
    FILE * file = fopen("promedio.txt", "r");

    if(file == NULL)
    {
        perror("Error al abrir el archivo");
    }
    else
    {
        while(feof(file) == 0)
        {
            fscanf(file, "%d", &n);
            //printf("%d\n", n);

            for (i = 0; i < n; i++)
            {
                fscanf(file, "%f", &num);
                //printf("%.2f\n", num);
                sum = sum + num;
                //printf("%.2f\n\n", sum);
            }
            if(i == n)
            {
                break;
            }
        }
        fclose(file);  
        promedio = sum/n;
        printf("El promedio es: %.3f\n", promedio);
    }
}
