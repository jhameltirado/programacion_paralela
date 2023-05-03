#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 1.2 TUBERÍAS, TAREA 1:
   Implemente el programa de la tarea anterior utilizando tuberías 
   como mecanismo de comunicación entre ambos procesos, donde se desconoce 
   la cantidad de datos a sumar los cuales son recibidos por la línea de comandos.
 */

int main(int argc, char *argv[])
{
    FILE *da;
    int i, sumahijo = 0, sumapadre = 0, multhijo = 1, multpadre = 0, a[2], b[2];
    int num;

    pipe(a);
    pipe(b);

    int hijo = fork();
       
    if(hijo == 0)
    {       // Codigo el proceso hijo
        int cant;

        close(a[1]); //cierra la escritura para el hijo
		close(b[0]); //cierra la lectura para el hijo

        da = fdopen(a[0], "r");

        fscanf(da, "%d", &cant);

        for(i = 0;i < cant; i++)
        {
            fscanf(da, "%d", &num);
            sumahijo = sumahijo + num;
            multhijo = multhijo * num;
        }

        fclose(da); 

        da = fdopen(b[1], "w");
        fprintf(da,"%d %d", sumahijo, multhijo); // Envia los datos al hijo
        close(a[0]); //Cierra tuberia
    }

    else 
    { //Codigo del proceso padre
        int cantidad = argc-1;

        close(a[0]); //cierra la lectura
	    close(b[1]); //cierra la escritura

        da = fdopen(a[1], "w");

        fprintf(da,"%d ",cantidad);

        for(i = 1;i < cantidad+1; i++)
        {
            fprintf(da,"%d ",atoi(argv[i]));
        }

        fclose(da);  

        da = fdopen(b[0], "r");
        fscanf(da, "%d %d", &sumapadre, &multpadre);
        
        printf("La suma es: %d\nLa multiplicación es: %d\n", sumapadre, multpadre);
    }

    return 0;
}