#include "user_interface.h"
#include "error_handler.h"
<<<<<<< HEAD
=======
#include "settings.h"
>>>>>>> 71192d1... Release version 2.0.0

#include <stdint.h>
#include <string.h>

#include <tice.h>
#include <graphx.h>
<<<<<<< HEAD

=======
#include <fileioc.h>

settings_t settings;
>>>>>>> 71192d1... Release version 2.0.0

void error(void) {
	
	dither_screen();
	status_message("ERROR", 54, 200);
	dialog(60, 89, 200, 100);
<<<<<<< HEAD
=======
}


static void save_MentalMS(void) {
	
	const char save_name[] = "MentalMS";
	ti_var_t save_file;
	
	ti_CloseAll();
	if (save_file = ti_Open("MentalMS", "r")) {
		ti_Write(save_name, sizeof(save_name), 1, save_file);
		ti_Write(&settings, sizeof(settings_t), 1, save_file);
	};
	ti_CloseAll();
	return;
}


void close_program(void) {
	
	save_MentalMS();
	ti_CloseAll();
	gfx_End();
	exit(0);
>>>>>>> 71192d1... Release version 2.0.0
}