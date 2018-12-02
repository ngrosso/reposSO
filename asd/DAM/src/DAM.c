/*
 ============================================================================
 Name        : DAM.c
 Author      : Nicolas Grosso
 Version     :
 Copyright   : Your copyright notice
 Description : DAM
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <protocolo.h>
#include <sys/sendfile.h>
#include "globales.h"
#include "estructuras.h"
#include "configuracion.h"
#include <sockets.h>
#include <unistd.h>
#include <commons/collections/list.h>

fd_set setSocketsOrquestador;
int iSocketMaximoOrquestador;

int main(void){
	printf("Inicia DAM\n");

	// Definicion de variables para los sockets
	FD_ZERO(&setSocketsOrquestador);
	int iSocketEscucha, iSocketComunicacion;

	//Levanto Config e inicializo el log.
	if(iniciarDAM()){
		return EXIT_FAILURE;
	}

	//Inicializo el socket Listener
	iSocketEscucha = crearSocketEscucha(atoi(config_get_string_value(DAM_CONFIG,"PUERTO")), LOGGER);
	FD_SET(iSocketEscucha, &setSocketsOrquestador);
	iSocketMaximoOrquestador = iSocketEscucha;

	tPaquete paquete;
	char* payLoad;

	//Conecto a SAFA
	conectarASAFA(); //TODO: Metodo para conectar a SAFA
	//Conecto a MDJ
	//conectarAMDJ(); //TODO: Metodo para conectar a MDJ
	//conecto a FM9
	//conectarAFM9(); //TODO: Metodo para conectar a FM9

	while(1){
		iSocketComunicacion = obtenerConexion(&setSocketsOrquestador, &iSocketMaximoOrquestador, iSocketEscucha, &paquete, LOGGER);
		if(iSocketComunicacion!=-1) {
			switch (paquete.type){
				case SAFA:
					if(paquete.operationType == HANDSHAKE){
						tPaquete pkgHandshake;
						pkgHandshake.type = SAFA;
						pkgHandshake.operationType = HANDSHAKE;
						pkgHandshake.length = sizeof(int);
						*pkgHandshake.payload =  1;
						enviarPaquete(iSocketComunicacion, &pkgHandshake, LOGGER,"Rta Handshake SAFA");
					}
			}

		}

	}
}


int inicializarDAM() {
	if((DAM_CONFIG = getConfiguration(DIR_CONFIG)) == NULL) {
		error_show("Error al levantar la configuracion.\n");
		return -1;
	}
	//Instanciar logger
	if((LOGGER = log_create("DAM.log","DAM: ", false, LOG_LEVEL_TRACE)) == NULL) {
		config_destroy(DAM_CONFIG);
		return -1;
	}
	return 0;
}

int conectarASAFA(){
	char* ip_SAFA = config_get_string_value(DAM_CONFIG,"IP_SAFA");
	int puerto_SAFA = atoi(config_get_string_value(DAM_CONFIG,"PUERTO_SAFA"));
	socketASAFA = connectarAServidor(ip_SAFA, puerto_SAFA, LOGGER);
	if(socketASAFA == -1){
		log_error(LOGGER,"Error al conectarse a SAFA");
	}else{
		log_info(LOGGER, "Conectado a SAFA");
		tPaquete* paquete = (tPaquete*) malloc(sizeof(tPaquete));
		//Envio Handshake
		paquete->operationType = HANDSHAKE;
				paquete->type = DAM;
				paquete->length = sizeof(int);
				int enviado = enviarPaquete(socketASAFA, paquete, LOGGER, "Handshake");
				printf("bytes enviado : %d", enviado);

	}
	return EXIT_SUCCESS;

}

