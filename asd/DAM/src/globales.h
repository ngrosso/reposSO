/*
 * globales.h
 *
 *  Created on: 25/9/2018
 *      Author: utnso
 */

#ifndef GLOBALES_H_
#define GLOBALES_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <commons/error.h>
#include <commons/config.h>
#include <commons/string.h>
#include <pthread.h>


//defino el path al archivo de configuraciones
#define DIR_CONFIG "DAM_CONFIG"

fd_set setSocketsOrquestador;
int iSocketMaximoOrquestador;

int socketASAFA;


t_config* DAM_CONFIG;
t_log* LOGGER;

int conectarASAFA();


#endif /* GLOBALES_H_ */
