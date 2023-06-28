// Funciones Básicas de Comunicación
// MPI_Send y MPI_ Recv.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int idProc, nProc, i, tag = 99, primero, tamBloque, flag, tamNombre;
char nombre[30];
int mayor;

MPI_Status status;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Get_processor_name(nombre, &tamNombre);

    nombre[tamNombre] = '\0';
    int tam = atoi(argv[2]);
    /* Calcula el tamaño de las partes a enviar a los otros */
    tamBloque = tam / nProc;

    int numeros[tam];
    int mayores[nProc];

    if (idProc == nProc - 1)
    {
        FILE * fichero;
        int j = 0;
        fichero = fopen(argv[1], "r");

        while(!feof(fichero))
        {
            fscanf(fichero, "%d", &numeros[j]);
            j++;
        }
        
        fclose(fichero);

        printf("datos: ");
        for (i = 0; i < tam; i++){
            printf("%d ", numeros[i]);
        }
        printf("\n");

        /* Envia los bloques de datos los otros procesos*/
        for (i = 0; i < nProc - 1; i++)
        {
            primero = i * tamBloque;
            MPI_Send(&numeros[primero], tamBloque, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
        /* determina lo que debo sumar yo (nproc-1) */
        primero = idProc * tamBloque;
        /* calculo mi mayor */

        mayor = numeros[0];

        for (i = primero; i < tam; i++)
        {
            if (numeros[i] > mayor)
            {
                mayor = numeros[i];
            }
        }
        
        mayores[idProc] = mayor;
        printf("Mi numero mayor es: %d\n", mayor);

        for (i = 0; i < nProc - 1; i++)
        {
            MPI_Recv(&mayor, 1, MPI_LONG, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            printf("Respondio %d - envio: %d\n", status.MPI_SOURCE, mayor);

            mayores[status.MPI_SOURCE] = mayor;
        }

        for (i = 0; i < nProc; i++)
        {
            if(mayores[i] > mayor)
            {
                mayor = mayores[i];
            }
        }

        printf("El número mayor es: %d\n", mayor);
    }
    else
    {
        /* recibe mi parte */
        MPI_Recv(numeros, tamBloque, MPI_LONG, nProc - 1, tag, MPI_COMM_WORLD, &status);
        /* efectua mi suma parcial */
        mayor = numeros[0];
        for (i = 0; i < tamBloque; i++)
        {
            if(numeros[i] > mayor)
            {
                mayor = numeros[i];
            }
        }
        /* devuelve mi suma parcial a (nproc - 1) */
        MPI_Send(&mayor, 1, MPI_LONG, nProc - 1, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}