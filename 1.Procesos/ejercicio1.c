#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

/* 1.1 PROCESOS, EJERCICIO 1:
   Crear un proceso padre y un proceso hijo donde el hijo suma 2 números
   y el padre determine el promedio a partir de la suma del hijo.*/

int main() 
{
    int a = 10, b = 20, c, estado, suma, promedio;
    
    int hijo = fork();
    
    if (hijo == 0) // PROCESO HIJO
    {
       c = a + b;
       exit(c);
    }
    else // PROCESO PADRE
    {
        wait(&estado);    
        if (WIFEXITED(estado))
        {
            suma = WEXITSTATUS(estado);
            promedio = suma/2;
            printf("El promedio es: %d\n", promedio);
        }
    }
    return 0;
}