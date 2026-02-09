#include "memoria.h"
t_log* logger;
t_log_level log_level;
t_config* config;
int puerto_escucha;
int socket_servidor;
int socket_cpu;
int socket_kernel;
int tam_memoria;
void* memoria_fisica;




int main(int argc, char* argv[]) {
    saludar("memoria");
    ObtenerConfig();
    logger = log_create("memoria.log","MEMORIA",true,log_level);
    socket_servidor = IniciarServidor(puerto_escucha);

    /* Por ahora comento estas lineas
    //No podemos saber cual es cual, después lo hago bien
    socket_cpu = EsperarConexion(socket_servidor);
    log_info(logger,"Se conecto cpu");
    socket_kernel = EsperarConexion(socket_servidor);
    log_info(logger,"Se conecto kernel");
    */

    memoria_fisica = malloc(tam_memoria);

    EscribirMemoria(500,"Holaaaaa");
    LeerMemoria(500,8);

    char* string;

    log_info(logger,"El contenido del string es %s",string);
    
    return 0;
}

char* LeerMemoria(int dir, int tam){
    char* lectura = malloc(tam + 1);
    memcpy(lectura,memoria_fisica + dir,tam);
    lectura[tam] = '\0'; // *(lectura + sizeof(char)*tam) = '\0'
    log_info(logger,"Lectura realizada. Dir: %d. Contenido: %s",dir,lectura);
    return lectura;
}

void EscribirMemoria(int dir, char* contenido){
    memcpy(memoria_fisica + dir, contenido,strlen(contenido));
    log_info(logger,"Escritura realizada. dir %d. Contenido: %s",dir,contenido);
}


void ObtenerConfig(){
    config = config_create("memoria.config");
    puerto_escucha = config_get_int_value(config,"PUERTO_ESCUCHA");
    log_level = log_level_from_string(config_get_string_value(config,"LOG_LEVEL"));
    tam_memoria = config_get_int_value(config,"TAM_MEMORIA");
}