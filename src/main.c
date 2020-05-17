/*======================================
 * Program Name: Mental Math CE
<<<<<<< HEAD
 * Version: 1.2.6 (alpha)
 * Author: Captain Calc
 * License: Open Source
 * Last edited: 2/06/2020
=======
 * Version: 2.0.0 (alpha)
 * Author: Captain Calc
 * Last edited: 5/14/2020
>>>>>>> 71192d1... Release version 2.0.0
 *======================================
*/

#include "gfx/sprites.h"
#include "gfx/MentalMI.h"
#include "defines.h"
#include "error_handler.h"
#include "exercise.h"
#include "problem_sets.h"
#include "settings.h"
#include "user_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

// Temporary
#include <debug.h>

<<<<<<< HEAD


static void setup_graphics(void);
static bool find_sprite_appvar(void);
static bool find_save_appvar(void);
static void draw_main_menu(uint8_t exercise_set, uint8_t selection);
void close_program(void);

void main(void) {
    
	uint8_t exercise_set;
	uint8_t selection;
	
	kb_key_t arrows, escape_keys_1, escape_keys_2;
	bool key_left, key_right, key_up, key_down;
	bool key_2nd, key_Yequ, key_Graph;
	bool key_Enter, key_Clear;
	
	setup_graphics();
	
	
	if (!find_sprite_appvar()) {
		//error("The program could not find the sprite appvar. \
		Please sent MentalMS.8xv to your calculator.");
	};
	
	if (find_save_appvar()) {
=======
const char save_name[] = "MentalMS";


static void setup_graphics(void) {
	MentalMI_init();
	gfx_Begin();
	gfx_SetPalette(sprites_pal, sizeof_sprites_pal, 0);
	gfx_SetDrawBuffer();
}


static bool find_sprite_appvar(void) {
	
	ti_CloseAll();
	if (ti_Open("MentalMI", "r") == NULL) {
		error();
		gfx_SetTextBGColor(BROWN);
		gfx_SetTextFGColor(BLACK);
		gfx_SetTextTransparentColor(BROWN);
		gfx_SetTextScale(1, 1);
		print_centered("The program could not", 115);
		print_centered("find the sprite appvar,", 125);
		print_centered("MentalMS.8xv.", 135);
		print_centered("Please send this file", 145);
		print_centered("to your calculator", 155);
		gfx_BlitBuffer();
		while(!os_GetCSC());
		close_program();
	};
	
	ti_CloseAll();
	return true;
}


static void reset_save_appvar(void) {
	
	ti_var_t save_file;
	
	if ((save_file = ti_Open("MentalMS", "w")) == NULL) {
>>>>>>> 71192d1... Release version 2.0.0
		error();
		gfx_SetTextBGColor(BROWN);
		gfx_SetTextFGColor(BLACK);
		gfx_SetTextTransparentColor(BROWN);
		gfx_SetTextScale(1, 1);
<<<<<<< HEAD
		print_centered("The program could not", 105);
		print_centered("find the save appvar", 115);
		print_centered("MentalMS.8xv.", 125);
		print_centered("All settings have been", 135);
		print_centered("reset and any saved", 145);
		print_centered("exercise times have been", 155);
		print_centered("lost", 165);
		gfx_BlitBuffer();
		while(!os_GetCSC());
		//reset_save_appvar();
	};
=======
		print_centered("The program could not", 120);
		print_centered("reset the save appvar.", 130);
		print_centered("The program will", 140);
		print_centered("automatically close", 150);
		gfx_BlitBuffer();
		while(!os_GetCSC());
		close_program();
	};
	
	settings.byte = 0;
	ti_Write(save_name, sizeof(save_name), 1, save_file);
	ti_Write(&settings, sizeof(settings_t), 1, save_file);
	ti_CloseAll();
	return;
}


static void load_settings(void) {
	
	ti_var_t save_file;
	
	ti_CloseAll();
	if (save_file = ti_Open("MentalMS", "r")) {
		ti_Seek(sizeof(save_name), 0, save_file);
		ti_Read(&settings, sizeof(settings_t), 1, save_file);
	};
	ti_CloseAll();
	return;
}


static void find_save_appvar(void) {
	
	char *appvar_name;
	
	ti_CloseAll();
	
	while ((appvar_name = ti_Detect(0, save_name)) != NULL) {
		load_settings();
		return;
	};
	
	error();
	gfx_SetTextBGColor(BROWN);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BROWN);
	gfx_SetTextScale(1, 1);
	print_centered("The program could not", 105);
	print_centered("find the save appvar", 115);
	print_centered("MentalMS.8xv.", 125);
	print_centered("All settings have been", 135);
	print_centered("reset and any saved", 145);
	print_centered("exercise times have been", 155);
	print_centered("lost", 165);
	gfx_BlitBuffer();
	while(!os_GetCSC());
	reset_save_appvar();
	return;
}


static void draw_main_menu(uint8_t exercise_set, uint8_t selection) {
	
	char *exercise[8] = {"Addition", "Subtraction", "Multiplication", "Division", "Roots", "Squares", "Complements", "Dates"};
	
	uint8_t i;
	bool highlight;
	
	gfx_FillScreen(BG_COLOR);
	gfx_SetTextBGColor(BG_COLOR);
	gfx_SetTextFGColor(BG_SHADOW_COLOR);
	gfx_SetTextTransparentColor(BG_COLOR);
	gfx_SetTextScale(2, 2);
	print_centered("Mental Math CE", 30);
	gfx_SetTextFGColor(BLACK);
	print_centered("Mental Math CE", 28);
	
	// Draw exercise set and highlighted button	
	for (i = 0; i < 4; i++) {
		highlight = false;
		if (selection == i)
			highlight = true;
		text_button(exercise[4 * exercise_set + i], highlight, 90, 75 + (30 * i), 140, 24);
	};
	
	icon_button(settings_icon, 5, 203);
	icon_button(exit_icon, 283, 203);
	
	// Draw page indicator
	page_indicator(2, exercise_set + 1);
	
	gfx_BlitBuffer();
	return;
}


void main(void) {
    
	uint8_t exercise_set;
	uint8_t selection;
	
	kb_key_t arrows, escape_keys_1, escape_keys_2;
	bool key_left, key_right, key_up, key_down;
	bool key_2nd, key_Yequ, key_Graph;
	bool key_Enter, key_Clear;
	
	setup_graphics();
	gfx_FillScreen(BG_COLOR);
	
	find_sprite_appvar();
	find_save_appvar();
>>>>>>> 71192d1... Release version 2.0.0

	/*	exercise_set 0 is the basic math operations
		exercise_set 1 is the special math operations */
	exercise_set = 0;
	selection = 0;
	
	for (;;) {
		
		do {
			draw_main_menu(exercise_set, selection);
			
			delay(200);
			
			do {
				kb_Scan();
			} while (!kb_AnyKey());
			
			arrows = kb_Data[7];
			key_right = arrows & kb_Right;
			key_left = arrows & kb_Left;
			key_up = arrows & kb_Up;
			key_down = arrows & kb_Down;
			
			escape_keys_1 = kb_Data[1];
			escape_keys_2 = kb_Data[6];
			
			key_2nd = escape_keys_1 & kb_2nd;
			key_Yequ = escape_keys_1 & kb_Yequ;
			key_Graph = escape_keys_1 & kb_Graph;
			key_Enter = escape_keys_2 & kb_Enter;
			key_Clear = escape_keys_2 & kb_Clear;
			
			if (key_right && exercise_set < 1)
				exercise_set++;
			if (key_left && exercise_set > 0)
				exercise_set--;
			if (key_down && selection < 3)
				selection++;
			if (key_up && selection > 0)
				selection--;
			
		} while (!(key_2nd || key_Yequ || key_Graph || key_Enter || key_Clear));
		
		if (key_Graph || key_Clear)
			break;
		
		if (key_Yequ) {
			dbg_sprintf(dbgout, "Inside settings if() statement\n");
<<<<<<< HEAD
			settings();
=======
			settings_menu();
>>>>>>> 71192d1... Release version 2.0.0
			dbg_sprintf(dbgout, "Executed settings()\n");
		};
		
		if (key_Enter || key_2nd) {
			if (exercise_set == 0) {
				exercise.type = selection;
				basic_problem_set();
			} else {
				switch (selection) {
					case 0:
					exercise.type = ROOTS;
<<<<<<< HEAD
					special_ops_pset();
=======
					roots_squares_pset();
>>>>>>> 71192d1... Release version 2.0.0
					break;
					
					case 1:
					exercise.type = SQUARES;
<<<<<<< HEAD
					special_ops_pset();
=======
					roots_squares_pset();
>>>>>>> 71192d1... Release version 2.0.0
					break;
					
					case 2:
					exercise.type = COMPLEMENTS;
<<<<<<< HEAD
					exercise.lower_bound_1 = 0;
					exercise.upper_bound_1 = 100;
					exercise.num_problems = 2;
					special_ops_pset();
					break;
					
					case 3:
					//datesProblemSet();
=======
					complements_pset();
					break;
					
					case 3:
					exercise.type = DATES;
					dates_pset();
>>>>>>> 71192d1... Release version 2.0.0
					break;
					
					default:
					break;
				};
			};
		};
	};
	
	close_program();
<<<<<<< HEAD
	exit(0);
}

static void setup_graphics(void) {
	MentalMI_init();
	// There should be error-checking here
	gfx_Begin();
	gfx_SetPalette(sprites_pal, sizeof_sprites_pal, 0);
	gfx_SetDrawBuffer();
	gfx_FillScreen(BG_COLOR);
}

static bool find_sprite_appvar(void) {
	
	ti_var_t slot;
	bool found = false;
	
	ti_CloseAll();
	slot = ti_Open("MentalMI", "r");
	
	if (slot != NULL)
		found = true;
	
	ti_CloseAll();
	return found;
}

static bool find_save_appvar(void) {
	
	ti_var_t slot;
	uint8_t *search_pos = NULL;
	bool found;
	
	ti_CloseAll();
	
	if (ti_Detect(&search_pos, "MentalMS") == NULL)
		found = false;
		
	// Verify the signature and set settings according to saved structure
	ti_CloseAll();
	found = true;
	return found;
}

static void draw_main_menu(uint8_t exercise_set, uint8_t selection) {
	
	char *exercise[8] = {"Addition", "Subtraction", "Multiplication", "Division", "Roots", "Squares", "Complements", "Dates"};
	
	uint8_t i;
	bool highlight;
	
	gfx_FillScreen(BG_COLOR);
	gfx_SetTextBGColor(BG_COLOR);
	gfx_SetTextFGColor(BG_SHADOW_COLOR);
	gfx_SetTextTransparentColor(BG_COLOR);
	gfx_SetTextScale(2, 2);
	print_centered("Mental Math CE", 30);
	gfx_SetTextFGColor(BLACK);
	print_centered("Mental Math CE", 28);
	
	// Draw exercise set and highlighted button	
	for (i = 0; i < 4; i++) {
		highlight = false;
		if (selection == i)
			highlight = true;
		text_button(exercise[4 * exercise_set + i], highlight, 90, 75 + (30 * i), 140, 24);
	};
	
	icon_button(settings_icon, 5, 203);
	icon_button(exit_icon, 283, 203);
	
	// Draw page indicator
	page_indicator(2, exercise_set + 1);
	
	gfx_BlitBuffer();
	return;
}

void close_program(void) {
	// If the program uses appvars, this function
	// will perform file operations checks and throw
	// an error if an error occurs.
	
	// Save record times to appvar
	// Close graphics
	// Free any allocated memory and verify that the
	// program exits safely.
	ti_CloseAll();
	gfx_End();
	
=======
>>>>>>> 71192d1... Release version 2.0.0
}