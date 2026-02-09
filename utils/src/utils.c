#include "utils.h"


void saludar(char* quien) {
    printf("Hola desde %s!!\n", quien);
}

int IniciarServidor(int puerto)
{

	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

    // Convertimos el puerto de entero a cadena
	char puerto_str[6]; // Máximo 5 dígitos para el puerto + 1 para el terminador nulo
    snprintf(puerto_str, sizeof(puerto_str), "%d", puerto);
	getaddrinfo(NULL, puerto_str, &hints, &servinfo);

	// Creamos el socket de escucha del servidor
	socket_servidor = socket(servinfo->ai_family,
                        servinfo->ai_socktype,
                        servinfo->ai_protocol);
						
	int opt = 1;
    if (setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        
    }
	// Asociamos el socket a un puerto
	bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);
	// Escuchamos las conexiones entrantes
	listen(socket_servidor, SOMAXCONN);

	freeaddrinfo(servinfo);

	return socket_servidor;
}
int EsperarConexion(int socket_servidor)
{

	// Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor, NULL, NULL);
    if (socket_cliente == -1) {
        perror("Error al aceptar conexión");
        return -1;
    }
	//log_info(logger, "Se conecto un cliente!");
	//cambio temporal hasta que se creen los logs
	return socket_cliente;
}

int CrearConexion(char *ip, int puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	char puerto_str[6]; // Máximo 5 dígitos para el puerto + 1 para el terminador nulo
    snprintf(puerto_str, sizeof(puerto_str), "%d", puerto);
	if (getaddrinfo(ip, puerto_str, &hints, &server_info) != 0) {
        //perror("Error en getaddrinfo");
        return -1;
    }

	// Ahora vamos a crear el socket.
	int socket_cliente = socket(server_info->ai_family,
                         server_info->ai_socktype,
                         server_info->ai_protocol);

	if (socket_cliente == -1) {
		//perror("Error al crear el socket");
		freeaddrinfo(server_info);
		return -1;
	}
	// Ahora que tenemos el socket, vamos a conectarlo				
	if (connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1) {
		//perror("Error al conectar");
		close(socket_cliente);
		freeaddrinfo(server_info);
		return -1;
	}

	freeaddrinfo(server_info);

	return socket_cliente;
}