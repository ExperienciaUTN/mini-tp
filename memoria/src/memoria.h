#ifndef MEMORIA_H
#define MEMORIA_H

#include <utils.h>

void ObtenerConfig();
char* LeerMemoria(int dir, int tam);
void EscribirMemoria(int dir, char* contenido);
#endif