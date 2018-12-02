#include "globales.h"
#include "configuracion.h"
#include <string.h>
#include <assert.h>

t_config* getConfiguration(char* path) {
	t_config* diccionario_configuracion = config_create(path);
	if(checkIntegrity(diccionario_configuracion)) {
		config_destroy(diccionario_configuracion);
		return NULL;
	}
	return diccionario_configuracion;
}

int checkIntegrity(t_config* diccionario) {
	if(		!config_has_property(diccionario,"PUERTO") ||
			!config_has_property(diccionario,"IP_SAFA") ||
			!config_has_property(diccionario,"PUERTO_SAFA") ||
			!config_has_property(diccionario,"IP_MDJ") ||
			!config_has_property(diccionario,"PUERTO_MDJ") ||
			!config_has_property(diccionario,"IP_FM9") ||
			!config_has_property(diccionario,"PUERTO_FM9") ||
			!config_has_property(diccionario,"TRANSFER_SIZE")
	) {
		return -1;
	}
	return 0;
}

int iniciarDAM(t_log *logger){
	DAM_CONFIG = config_create(DIR_CONFIG);
	log_info(logger,"config creado\n");
	if(checkIntegrity(DAM_CONFIG) == 0){

		log_info(logger, "PUERTO = %s\n", config_get_string_value(DAM_CONFIG, "PUERTO"));
		log_info(logger, "IP_SAFA = %s\n", config_get_string_value(DAM_CONFIG, "IP_SAFA"));
		log_info(logger, "PUERTO_SAFA = %s\n", config_get_string_value(DAM_CONFIG, "PUERTO_SAFA"));
		log_info(logger, "IP_MDJ = %s\n", config_get_string_value(DAM_CONFIG, "IP_MDJ"));
		log_info(logger, "PUERTO_MDJ = %s\n", config_get_string_value(DAM_CONFIG, "PUERTO_MDJ"));
		log_info(logger, "IP_FM9 = %s\n", config_get_string_value(DAM_CONFIG, "IP_FM9"));
		log_info(logger, "PUERTO_FM9 = %s\n", config_get_string_value(DAM_CONFIG, "PUERTO_FM9"));
		log_info(logger, "TRANSFER_SIZE = %s\n", config_get_string_value(DAM_CONFIG, "TRANSFER_SIZE"));

		return 0;
		}
	else{
		log_error(logger, "No se puede inicializar correctamente");
		return -1;
	}
}

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}
