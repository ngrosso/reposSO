#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <commons/error.h>
#include <commons/config.h>
#include <commons/string.h>

t_config* getConfiguration(char* path);
int checkIntegrity(t_config* diccionario);

char* replace_char(char* str, char find, char replace);

#endif /* CONFIGURACION_H_ */
