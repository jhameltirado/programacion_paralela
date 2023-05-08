#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include <arpa/inet.h>
#include <time.h>
int buscarip(char *ip);

char Mensaje[]="Hola desde el Servidor\n";
// Programa que envia un saludo a los clientes que establecen una conexion

int buscarip(char *ip){
 int enc=0;
 FILE *da;
 char direccion[40];
 da = fopen("lista_negra.txt","r" );
 while(!feof(da) && enc==0){

 fscanf(da, "%s", direccion);
     
    if(strcmp(ip,direccion)==0)     
                enc=1;
 }   

return enc;  

}

int main(int argc, char *argv[]){

char usuario[50];
char contrasena[50];

int mi_socket = 0;
int puerto = 0;
int estado = 0;
struct sockaddr_in dir;

if(argc != 2){

printf("Use: %s <puerto>\n", argv[0]);
exit(1);

}//fin del if

mi_socket = socket(AF_INET, SOCK_STREAM, 0);

if(mi_socket == -1){

	printf("No es posible crear socket!!\n");
	exit(1);

}
else{
	printf("Socket Creado\n");
}//fin del if


//Recupera el numero de puerto para escuchar
puerto = atoi(argv[1]);

//levanta la estructura de direccion
//utiliza INADD_ANY para relacionar a todas las direcciones locales

dir.sin_family = AF_INET;
dir.sin_addr.s_addr = htonl(INADDR_ANY);
dir.sin_port = htons(puerto);


//relacionar la direccion y puerto con nuestro socket
estado = bind(mi_socket, (struct sockaddr *)&dir, sizeof(dir));


if(estado == 0){

	printf("Enlace completado\n");

}else
{
	printf("No es posible enlace con la direccion\n");
	close(mi_socket);
	exit(1);

}//fin del if


//escuchar las conexiones en el socket
estado = listen(mi_socket, 5);

if(estado == -1){

	printf("No es posible escuchar por el socket\n");
	close(mi_socket);
	exit(1);	

}//fin del if

char usuario_recibido[50] = "";
char contrasena_recibida[50] = "";

while(1){

	int band = 0;

	struct sockaddr_in cliente = { 0 };
	int socket_hijo = 0;
	socklen_t long_cliente = sizeof(cliente);

	//esperar aqui
	socket_hijo = accept(mi_socket, (struct sockaddr *)&cliente, &long_cliente);
         
       	if(socket_hijo == -1){

		printf("No puede aceptar conexiones!\n");
		close(mi_socket);
		exit(1);
	}//fin del if
 
	//manejar la nueva solicitud de conexion
	char *ip = inet_ntoa(cliente.sin_addr);
        char cadena[20] = "";

	time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = (struct tm *)localtime ( &rawtime );

	// lee lo recibido del cliente
	read(socket_hijo,usuario_recibido,sizeof(usuario_recibido));
    read(socket_hijo,contrasena_recibida,sizeof(contrasena_recibida));

	FILE * archivo = fopen("usuarios.txt","rb");
        if(archivo == NULL)
        {
            perror("Error en la apertura del archivo\n");
            return 1;
        }

        while(feof(archivo)== 0)
        {
            fscanf(archivo,"%s%s", usuario, contrasena);

            if(strcmp(usuario,usuario_recibido) == 0 && strcmp(contrasena,contrasena_recibida) == 0)
            {
                printf("%s ha solicitado entrar.\n", usuario_recibido);
				band = 1;
                break;
            }
        }

		if(buscarip(ip) == 0 && band == 1)
		{
			send(socket_hijo, (char*) asctime (timeinfo), strlen((char*) asctime (timeinfo)),0);
			printf("Se atendió una solicitud de la IP: %s, con el usuario: %s\n", ip, usuario_recibido);
		}
		else
		{
			strcpy(cadena, "Servicio negado...\n");
		}
        
        fclose(archivo);

	//envia el mensaje al cliente
	write(socket_hijo, cadena, sizeof(cadena));
	close(socket_hijo);
          
}//fin del while


close(mi_socket);

return 0;

}//fin del main


