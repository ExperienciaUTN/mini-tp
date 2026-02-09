#include "cpu.h"
t_config* config;
char* ip_kernel;
int puerto_kernel;
t_log_level log_level;
t_log* logger;
int socket_kernel;
int socket_memoria;
char* ip_memoria;
int puerto_memoria;



int main(int argc, char* argv[]) {
    saludar("cpu");
    ObtenerConfig();
    logger = log_create("cpu.log","CPU",true,log_level);
    socket_kernel = CrearConexion(ip_kernel,puerto_kernel);
    socket_memoria = CrearConexion(ip_memoria,puerto_memoria);
    
    return 0;
}

void ObtenerConfig(){
    config = config_create("cpu.config");
    ip_kernel = config_get_string_value(config,"IP_KERNEL");
    puerto_kernel = config_get_int_value(config,"PUERTO_KERNEL");
    log_level = log_level_from_string(config_get_string_value(config,"LOG_LEVEL"));
    ip_memoria = config_get_string_value(config,"IP_MEMORIA");
    puerto_memoria = config_get_int_value(config,"PUERTO_MEMORIA");

}