// reducción buscando el mayor
#include <stdio.h>
#include <mpi.h>
#define tam 20

int idProc, nProc, datos[tam], i, tag = 99, primero, ultimo, bloque, maxmin[2];
int  mayor, menor, pmayor = 0, pmenor = 0, cont_mayor = 0, cont_menor = 0, suma_mayor = 0, suma_menor = 0, mayorp = 0;
MPI_Status status;

int main (int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);

    // El proceso 0 rellena el vector datos
    if (idProc == 0)
    {
        FILE * fichero;
        int j = 0;
        fichero = fopen(argv[1], "r");

        while(!feof(fichero))
        {
            fscanf(fichero, "%d", &datos[j]);
            j++;
        }

        fclose(fichero);

        printf("datos: ");
        for (i = 0; i < tam; i++){
            printf("%d ", datos[i]);
        }
        printf("\n");
    }

    // Difunde el vector datos
    MPI_Bcast(datos,tam,MPI_INT,0,MPI_COMM_WORLD);

    // Determina particiones del arreglo para cada proceso
    bloque = tam/nProc;
    if (idProc == nProc - 1)
    {
        primero = (nProc - 1)*bloque;
        ultimo = tam - 1;
    }
    else 
    {
        primero = idProc*bloque;
        ultimo = (idProc + 1)*bloque - 1;
    }

    // cada proceso calcula su máximo
    pmayor = datos[primero];

    for (i=primero;i<=ultimo;i++)
    {
        if (pmayor < datos[i])
        {
            pmayor = datos[i];
        } 
    }
            
    // cada proceso calcula su minimo
    pmenor = datos[primero];

    for (i=primero;i<=ultimo;i++)
    {
        if (pmenor > datos[i])
        {
            pmenor = datos[i];
        }   
    }
            
    // Se hace la reducción de los mayores y menores parciales para obtener el mayor y el menor de todos
    MPI_Reduce(&pmayor,&mayor,1,MPI_INT, MPI_MAX,0,MPI_COMM_WORLD);
    MPI_Reduce(&pmenor,&menor,1,MPI_INT, MPI_MIN,0,MPI_COMM_WORLD);

    // el proceso 0 guarda el mayor y el menor en un arreglo para enviarlo con MPI_Bcast
    if(idProc == 0)
    {
        maxmin[0] = mayor;
        maxmin[1] = menor;
    }

    // se envían los valores obtenidos de máximo y mínimo
    MPI_Bcast(maxmin, 2, MPI_INT,0,MPI_COMM_WORLD);

    cont_menor = 0;
    cont_mayor = 0;

    // cada proceso cuenta cuántas veces aparece el máximo y el mínimo en su partición
    for (i=primero;i<=ultimo;i++)
    {
        if(datos[i] == maxmin[0])
        {
            cont_mayor++;
        }
        else if(datos[i] == maxmin[1])
        {
            cont_menor++;
        }
    }

    // se suman los contadores de todos los procesos
    MPI_Reduce(&cont_mayor,&suma_mayor,1,MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&cont_menor,&suma_menor,1,MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);

    // el proceso 0 imprime cuántas veces aparece el máximo y el mínimo en todo el arreglo
    if (idProc == 0)
    {
        printf("El mayor aparece %d veces.\n",suma_mayor);
        printf("El menor aparece %d veces.\n",suma_menor);
    }            

    MPI_Finalize();
}