#include "gfx/sprites.h"
#include "gfx/MentalMI.h"
#include "defines.h"
#include "exercise.h"
#include "input.h"
#include "problem_sets.h"
<<<<<<< HEAD
=======
#include "settings.h"
>>>>>>> 71192d1... Release version 2.0.0
#include "user_interface.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <graphx.h>
#include <keypadc.h>

// Temporary
#include <debug.h>
<<<<<<< HEAD

void dump(const char *data_buffer, const int length) {
	char byte;
	unsigned int i, j;

	for (i = 0; i < length; i++) {
		byte = data_buffer[i];
		dbg_sprintf(dbgout, "%02x ", data_buffer[i]);
		if ((i % 16) == 15 || (i == length - 1)) {
			for (j = 0; j < 15 - (i % 16); j++)
				dbg_sprintf(dbgout, "   ");
			dbg_sprintf(dbgout, "| ");
			for (j = (i - (i % 16)); j <= i; j++) {
				byte = data_buffer[j];
				if ((byte > 31) && (byte < 127))
					dbg_sprintf(dbgout, "%c", byte);
				else
					dbg_sprintf(dbgout, ".");
			};
				dbg_sprintf(dbgout, "\n");
		};
	};
}
=======
#include "calcdbg.h"
>>>>>>> 71192d1... Release version 2.0.0


/*	Pass an array containing the appropriate problem sets
	to the draw function so it can draw the buttons */
static uint8_t addition_psets[] = {
	2, 1, 2, 2, 3, 2, 3, 3,
	4, 3, 4, 4, 5, 4, 5, 5
};

static uint8_t subtraction_psets[] = {
	2, 1, 2, 2, 3, 2, 3, 3,
	4, 3, 4, 4, 5, 4, 5, 5
};

static uint8_t multiplication_psets[] = {
	2, 1, 3, 1, 4, 1, 2, 2, 3, 2,
	3, 3, 4, 3, 4, 4, 5, 4, 5, 5
};

static uint8_t division_psets[] = {
	2, 1, 3, 1, 4, 1, 5, 1, 3, 2,
	4, 2, 5, 2, 4, 3, 5, 3, 5, 4
};

<<<<<<< HEAD
=======

>>>>>>> 71192d1... Release version 2.0.0
static uint8_t* get_pset_array(void) {
	
	switch (exercise.type) {
		
		case ADDITION:
		return addition_psets;
		
		case SUBTRACTION:
		return subtraction_psets;
		
		case MULTIPLICATION:
		return multiplication_psets;
		
		case DIVISION:
		return division_psets;
		
		default:
		// Trigger error
		return 0;
	};
}

<<<<<<< HEAD
=======

>>>>>>> 71192d1... Release version 2.0.0
static uint8_t array_len(void) {
	if (exercise.type == ADDITION || exercise.type == SUBTRACTION)
		return 16;
	return 20;
}

<<<<<<< HEAD
=======

>>>>>>> 71192d1... Release version 2.0.0
static void draw_pset_symbol(void) {
	
	gfx_sprite_t *symbol;
	
	switch (exercise.type) {
		case ADDITION:
		symbol = addition_symbol;
		break;
		
		case SUBTRACTION:
		symbol = subtraction_symbol;
		break;
		
		case MULTIPLICATION:
		symbol = multiplication_symbol;
		break;
		
		case DIVISION:
		symbol = division_symbol;
		break;
		
		case ROOTS:
		symbol = roots_icon;
		break;
		
		case SQUARES:
		symbol = squares_icon;
		break;
		
<<<<<<< HEAD
		default:
		symbol = complements_icon;
=======
		case COMPLEMENTS:
		symbol = complements_icon;
		break;
		
		default:
		symbol = dates_icon;
>>>>>>> 71192d1... Release version 2.0.0
	};
	
	gfx_SetColor(BLACK);
	gfx_Rectangle_NoClip(6, 5, 20, 22);
	gfx_Rectangle_NoClip(5, 6, 22, 20);
	gfx_SetPixel(7, 7);
	gfx_SetPixel(24, 7);
	gfx_SetPixel(7, 24);
	gfx_SetPixel(24, 24);
	gfx_TransparentSprite_NoClip(symbol, 8, 8);
	
	gfx_FillRectangle_NoClip(30, 25, 200, 2);
	gfx_SetTextBGColor(BG_COLOR);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BG_COLOR);
	gfx_SetTextScale(2, 2);
	gfx_PrintStringXY("Problem Sets", 30, 10);
	gfx_SetTextScale(1, 1);
	return;
}

<<<<<<< HEAD
=======

>>>>>>> 71192d1... Release version 2.0.0
static const char* build_pset_button_str(uint8_t *pset_array, uint8_t offset) {
	
	char *str = malloc(6);
	memset(str, '\0', 6);
	
	sprintf(str, "%d - %d", *(pset_array + offset), *(pset_array + offset + 1));
	
	return (const char*)str;
}

<<<<<<< HEAD
=======

>>>>>>> 71192d1... Release version 2.0.0
static void draw_basic_pset(uint8_t *pset_array, uint8_t selection_col, uint8_t selection_row) {
	
	uint8_t array_length;
	uint8_t i, j;
	const char *str;
	
	bool highlight;
	
	gfx_FillScreen(BG_COLOR);
	
	draw_pset_symbol();
	
	// Draw the button array
	array_length = array_len();
	for (i = 0; i < 2; i++) {
		for (j = 0; j < array_length / 4; j++) {
			highlight = false;
			if (selection_col == i && selection_row == j)
				highlight = true;
			str = build_pset_button_str(pset_array, 2 * j + ((array_length / 2) * i));
<<<<<<< HEAD
			dump(str, 5);
=======
			calcdbg_dump(str, 5);
>>>>>>> 71192d1... Release version 2.0.0
			text_button(str, highlight, 50 + 110 * i, 70 + 30 * j, 100, 24);
			free(str);
		};
	};
	
	icon_button(back_icon, 283, 203);
	gfx_BlitBuffer();
	return;	
}

<<<<<<< HEAD
=======

static void get_bounds(uint8_t *pset_array, uint8_t sel_col, uint8_t sel_row) {
	
	uint8_t array_length = array_len();
	
	exercise.lower_bound_1 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row) - 1);
	exercise.upper_bound_1 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row)) - 1;
	exercise.lower_bound_2 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row + 1) - 1);
	exercise.upper_bound_2 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row + 1)) - 1;
	return;
}


>>>>>>> 71192d1... Release version 2.0.0
static void draw_input_box_centered(const char *label, uint8_t yPos) {
	
	uint24_t width;
	
	width = gfx_GetStringWidth(label);
	gfx_PrintStringXY(label, (160 - (width + 54) / 2), yPos + 3);
	
	gfx_SetColor(BLACK);
	gfx_FillRectangle_NoClip((160 - 24 + width / 2), yPos, 52, 13);
	gfx_SetColor(WHITE);
	gfx_FillRectangle_NoClip((161 - 24 + width / 2), yPos + 1, 50, 11);
	return;
}

<<<<<<< HEAD
static void setup_small_font_input(void) {
	textio_SetInputColorConfig(BLACK, BLACK);
	textio_SetInitialKeymap(1);
	gfx_SetTextScale(1, 1);
	set_cursor_dimensions(1, 9);
	return;
}

static void get_bounds(uint8_t *pset_array, uint8_t sel_col, uint8_t sel_row) {
	
	uint8_t array_length = array_len();
	
	exercise.lower_bound_1 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row) - 1);
	exercise.upper_bound_1 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row)) - 1;
	exercise.lower_bound_2 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row + 1) - 1);
	exercise.upper_bound_2 = (uint24_t)pow(10, *(pset_array + ((array_length / 2) * sel_col) + 2 * sel_row + 1)) - 1;
	return;
}

// Gets the number of problems for the basic operations problem set
=======

/*	Gets the number of problems for the basic operations problem set
	Also gets timer if active */
>>>>>>> 71192d1... Release version 2.0.0
static int get_num_problems(void) {
	
	uint8_t key;
	
	uint8_t width = 220;
	uint8_t height = 50;
	
<<<<<<< HEAD
	char *num_problems_str;
	
	gfx_FillScreen(BG_COLOR);
	dialog((320 - width) / 2, (240 - height) / 2, width, height);
	draw_input_box_centered("# of problems:", (240 - height) / 2 + 18);
=======
	char buffer[4];
	
	if (SETTINGS_TIMER)
		height = 70;
	
	gfx_FillScreen(BG_COLOR);
	dialog((320 - width) / 2, (240 - height) / 2, width, height);
	draw_input_box_centered("# of problems:", 138 - height / 2);
	if (SETTINGS_TIMER)
		draw_input_box_centered("Time/problem:", 160 - height / 2);
>>>>>>> 71192d1... Release version 2.0.0
	icon_button(back_icon, 5, 203);
	icon_button(start_icon, 283, 203);
	gfx_BlitBuffer();
	
<<<<<<< HEAD
	// Number of problems max: 99 (2 digits)
	num_problems_str = malloc(3);
	memset(num_problems_str, '\0', 3);
	input_config.curr_char = num_problems_str;
	input_config.visible_buffer = num_problems_str;
	setup_small_font_input();
	
	delay(100);										// Catch the last keypress
	
	do {
		do {
			key = textio_NumericalInput(num_problems_str, 2, 46, 185, 115);
			gfx_BlitRectangle(1, 185, 115, 46, 11);
		} while (key != sk_Enter && key != sk_Yequ && key != sk_Graph);
		
		if (key == sk_Yequ)
			return -1;
	
	} while (atoi((const char*)num_problems_str) == 0);
	
	exercise.num_problems = atoi((const char*)num_problems_str);
	
	// Free allocated memory
	free(num_problems_str);
=======
	delay(100);					// Catch the last keypress
	
	// Number of problems max: 99 (2 digits)
	toggle_input_timer(false);
	setup_input(false);
	do {
		memset(&buffer, '\0', 4);
		input_config.curr_char = &buffer;
		input_config.visible_buffer = &buffer;
		for (;;) {
			key = textio_NumericalInput(&buffer, 2, 46, 185, 140 - height / 2);
			if (key == sk_Yequ)
				return -1;
			exercise.num_problems = atoi((const char*)buffer);
			if (key == sk_Enter || key == sk_2nd || ((key == sk_Graph || key == sk_Down) && SETTINGS_TIMER))
				break;
		};
	} while (exercise.num_problems == 0);
	
	if (SETTINGS_TIMER) {
		do {
			memset(&buffer, '\0', 4);
			input_config.curr_char = &buffer;
			input_config.visible_buffer = &buffer;
			do {
				key = textio_NumericalInput(&buffer, 3, 46, 184, 162 - height / 2);
				if (key == sk_Yequ)
					return -1;
				exercise.timer = atoi((const char*)buffer);
			} while (key != sk_Enter  && key != sk_2nd && key != sk_Graph);
		} while (exercise.timer == 0);
	};
>>>>>>> 71192d1... Release version 2.0.0
	
	return exercise.num_problems;
}

<<<<<<< HEAD
=======

>>>>>>> 71192d1... Release version 2.0.0
void basic_problem_set(void) {
	
	uint8_t *pset_array;
	uint8_t array_length;
	uint8_t sel_col, sel_row;
	
	uint8_t num_problems;
	
	kb_key_t arrows, escape_keys_1, escape_keys_2;
	bool key_left, key_right, key_up, key_down;
	bool key_2nd, key_Yequ, key_Graph;
	bool key_Enter, key_Clear;
	
	
	sel_col = 0;
	sel_row = 0;
	
	// Get the proper array and its length
	pset_array = get_pset_array();
	array_length = array_len();
	
	for (;;) {
		
		draw_basic_pset(pset_array, sel_col, sel_row);
		
		delay(200);				// Prevent slow key release from triggering fall-through
				
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
		key_Graph = escape_keys_1 & kb_Graph;
		key_Enter = escape_keys_2 & kb_Enter;
		key_Clear = escape_keys_2 & kb_Clear;
	
		if (key_right && sel_col < 1) 
			sel_col++;
		if (key_left && sel_col > 0)
			sel_col--;
		if (key_down && sel_row < ((array_length / 4) - 1))
			sel_row++;
		if (key_up && sel_row > 0)
			sel_row--;
		
		if (key_Graph || key_Clear)
			return;
		
		if (key_Enter || key_2nd) {
			get_bounds(pset_array, sel_col, sel_row);
			if (get_num_problems() != -1) {
				do_exercise();
				return;
			};
		};
	};
}

<<<<<<< HEAD
void special_ops_pset(void) {
	
	uint8_t width;
	uint8_t height;
	uint8_t key;
	
	char *lower_bound_str, *upper_bound_str;
	char *num_problems_str;
	
	/*
	Roots:
	lower bound = 4 digits
	upper bound = 5 digits
	
	Squares:
	lower bound = 4 digits
	upper bound = 5 digits
	
	Complements = 5 digits
	
	Dates:
	lower bound = 4 digits
	upper bound = 5 digits
	These probably should be changed
	*/
	
	
=======
void roots_squares_pset(void) {
	
	uint8_t key;
	uint8_t yPos;
	uint8_t width = 220;
	uint8_t height = 90;
	char buffer[6];
	
	if (SETTINGS_TIMER)
		height = 100;
	
	yPos = 120 - height / 2;
	
	gfx_FillScreen(BG_COLOR);
	draw_pset_symbol();
	icon_button(back_icon, 5, 203);
	icon_button(start_icon, 283, 203);
	dialog(160 - width / 2, yPos, width, height);
	draw_input_box_centered("Lower bound:", yPos + 15);
	draw_input_box_centered("Upper bound:", yPos + 30);
	draw_input_box_centered("# of problems:", yPos + 55);
	if (SETTINGS_TIMER)
		draw_input_box_centered("Time/problem:", yPos + 70);
	gfx_BlitBuffer();
	
	// Get lower bound (4 digits)
	toggle_input_timer(false);
	setup_input(false);
	do {
		memset(buffer, '\0', 6);
		input_config.curr_char = &buffer;
		input_config.visible_buffer = &buffer;
		do {
			key = textio_NumericalInput(&buffer, 4, 46, 181, yPos + 17);
			if (key == sk_Yequ)
				return;
			exercise.lower_bound_1 = atoi((const char*)buffer);
		} while (key != sk_Enter && key != sk_2nd);
	} while (exercise.lower_bound_1 == 0);
	
	// Get upper bound (5 digits)
	do {
		memset(buffer, '\0', 6);
		input_config.curr_char = &buffer;
		input_config.visible_buffer = &buffer;
		do {
			key = textio_NumericalInput(&buffer, 5, 46, 181, yPos + 32);
			if (key == sk_Yequ)
				return;
			exercise.upper_bound_1 = atoi((const char*)buffer);
		} while (key != sk_Enter && key != sk_2nd && key != sk_Down);
	} while (exercise.upper_bound_1 < exercise.lower_bound_1);
	
	// Get number of problems (2 digits)
	do {
		memset(buffer, '\0', 6);
		input_config.curr_char = &buffer;
		input_config.visible_buffer = &buffer;
		for (;;) {
			key = textio_NumericalInput(&buffer, 2, 46, 185, yPos + 57);
			if (key == sk_Yequ)
				return;
			exercise.num_problems = atoi((const char*)buffer);
			if (key == sk_Enter || key == sk_2nd || ((key == sk_Graph || key == sk_Down) && !SETTINGS_TIMER))
				break;
		};
	} while (exercise.num_problems == 0);
	
	if (SETTINGS_TIMER) {
		do {
			memset(&buffer, '\0', 4);
			input_config.curr_char = &buffer;
			input_config.visible_buffer = &buffer;
			do {
				key = textio_NumericalInput(&buffer, 3, 46, 184, yPos + 72);
				if (key == sk_Yequ)
					return;
				exercise.timer = atoi((const char*)buffer);
			} while (key != sk_Enter && key != sk_2nd && key != sk_Graph);
		} while (exercise.timer == 0);
	};
	
	do_exercise();
	return;
}

void complements_pset(void) {
	
	uint8_t key;
	uint8_t yPos;
	uint8_t width = 220;
	uint8_t height = 80;
	char buffer[6];
	
	if (SETTINGS_TIMER)
		height = 100;
	
	yPos = 120 - height / 2;
>>>>>>> 71192d1... Release version 2.0.0
	
	gfx_FillScreen(BG_COLOR);
	draw_pset_symbol();
	icon_button(back_icon, 5, 203);
	icon_button(start_icon, 283, 203);
<<<<<<< HEAD
	
	
	if (exercise.type == ROOTS || exercise.type == SQUARES) {
		
		dialog(50, 70, 220, 100);
		draw_input_box_centered("Lower bound:", 90);
		draw_input_box_centered("Upper bound:", 105);
		draw_input_box_centered("# of problems:", 130);
		gfx_BlitBuffer();
		
		// Get lower bound (4 digits)
		lower_bound_str = malloc(5);
		memset(lower_bound_str, '\0', 5);
		input_config.curr_char = lower_bound_str;
		input_config.visible_buffer = lower_bound_str;
		setup_small_font_input();
		
		do {
			do {
				key = textio_NumericalInput(lower_bound_str, 4, 46, 181, 92);
				gfx_BlitRectangle(1, 181, 92, 46, 11);
			} while (key != sk_Enter && key != sk_Yequ && key != sk_Graph);
			
			if (key == sk_Yequ) {
				free(lower_bound_str);
				goto EXIT_MENU;
			};
			
		} while (atoi((const char*)lower_bound_str) == 0);
		
		exercise.lower_bound_1 = atoi((const char*)lower_bound_str);
		free(lower_bound_str);
		
		// Get upper bound (5 digits)
		upper_bound_str = malloc(6);
		memset(upper_bound_str, '\0', 6);
		input_config.curr_char = upper_bound_str;
		input_config.visible_buffer = upper_bound_str;
		
		do {
			do {
				key = textio_NumericalInput(upper_bound_str, 5, 46, 181, 107);
				gfx_BlitRectangle(1, 181, 107, 46, 11);
			} while (key != sk_Enter && key != sk_Yequ && key != sk_Graph);
			
			if (key == sk_Yequ) {
				free(upper_bound_str);
				goto EXIT_MENU;
			};
			
		} while (atoi((const char*)upper_bound_str) == 0);
		
		exercise.upper_bound_1 = atoi((const char*)upper_bound_str);
		free(upper_bound_str);
		
		// Get number of problems (2 digits)
		num_problems_str = malloc(3);
		memset(num_problems_str, '\0', 3);
		input_config.curr_char = num_problems_str;
		input_config.visible_buffer = num_problems_str;
		
		do {
			do {
				key = textio_NumericalInput(num_problems_str, 2, 46, 185, 132);
				gfx_BlitRectangle(1, 185, 132, 46, 11);
			} while (key != sk_Enter && key != sk_Yequ && key != sk_Graph);
			
			if (key == sk_Yequ) {
				free(num_problems_str);
				goto EXIT_MENU;
			};
		
		} while (atoi((const char*)num_problems_str) == 0);
		
		exercise.num_problems = atoi((const char*)num_problems_str);
		free(num_problems_str);
	};
	
	if (exercise.type == COMPLEMENTS) {
		
		width = 220;
		height = 80;
		
		dialog((320 - width) / 2, (240 - height) / 2, width, height);
		draw_input_box_centered("Complements of", (240 - height) / 2 + 20);
		draw_input_box_centered("# of problems:", (240 - height) / 2 + 45);
		gfx_BlitBuffer();
		
		// Get upper bound (5 digits)
		upper_bound_str = malloc(6);
		memset(upper_bound_str, '\0', 6);
		input_config.curr_char = upper_bound_str;
		input_config.visible_buffer = upper_bound_str;
		
		do {
			do {
				key = textio_NumericalInput(upper_bound_str, 5, 46, 188, 107);
				gfx_BlitRectangle(1, 188, 107, 46, 11);
			} while (key != sk_Enter && key != sk_Yequ && key != sk_Graph);
			
			if (key == sk_Yequ) {
				free(upper_bound_str);
				goto EXIT_MENU;
			};
			
		} while (atoi((const char*)upper_bound_str) == 0);
		
		exercise.upper_bound_1 = atoi((const char*)upper_bound_str);
		free(upper_bound_str);
		
		// Get number of problems (2 digits)
		num_problems_str = malloc(3);
		memset(num_problems_str, '\0', 3);
		input_config.curr_char = num_problems_str;
		input_config.visible_buffer = num_problems_str;
		
		do {
			do {
				key = textio_NumericalInput(num_problems_str, 2, 46, 185, 132);
				gfx_BlitRectangle(1, 185, 132, 46, 11);
			} while (key != sk_Enter && key != sk_Yequ && key != sk_Graph);
			
			if (key == sk_Yequ) {
				free(num_problems_str);
				goto EXIT_MENU;
			};
		
		} while (atoi((const char*)num_problems_str) == 0);
		
		exercise.num_problems = atoi((const char*)num_problems_str);
		free(num_problems_str);
		
		
		// For this exercise, the range is from the entered number (upper_bound_1) to zero.
		exercise.lower_bound_1 = 0;
	};

	do_exercise();
	
	EXIT_MENU:
=======
	dialog(50, yPos, width, height);
	draw_input_box_centered("Complements of", yPos + 20);
	draw_input_box_centered("# of problems:", yPos + 50);
	if (SETTINGS_TIMER)
		draw_input_box_centered("Time/problem:", yPos + 65);
	gfx_BlitBuffer();
	
	
	// Get upper bound (5 digits)
	toggle_input_timer(false);
	setup_input(false);
	do {
		memset(buffer, '\0', 6);
		input_config.curr_char = &buffer;
		input_config.visible_buffer = &buffer;
		do {
			key = textio_NumericalInput(&buffer, 5, 46, 189, yPos + 22);
			if (key == sk_Yequ)
				return;
			exercise.upper_bound_1 = atoi((const char*)buffer);
		} while (key != sk_Enter && key != sk_2nd && key != sk_Down);
	} while (exercise.upper_bound_1 == 0);
	
	// Get number of problems (2 digits)
	memset(buffer, '\0', 6);
	input_config.curr_char = &buffer;
	input_config.visible_buffer = &buffer;
	do {
		for (;;) {
			key = textio_NumericalInput(&buffer, 2, 46, 185, yPos + 52);
			if (key == sk_Yequ)
				return;
			exercise.num_problems = atoi((const char*)buffer);
			if (key == sk_Enter || key == sk_2nd || (key == sk_Graph && !SETTINGS_TIMER) || (key == sk_Down && SETTINGS_TIMER))
				break;
		};
	} while (exercise.num_problems == 0);
	
	
	// For this exercise, the range is from the entered number (upper_bound_1) to zero.
	exercise.lower_bound_1 = 0;
	
	if (SETTINGS_TIMER) {
		do {
			memset(&buffer, '\0', 4);
			input_config.curr_char = &buffer;
			input_config.visible_buffer = &buffer;
			do {
				key = textio_NumericalInput(&buffer, 3, 46, 184, yPos + 67);
				if (key == sk_Yequ)
					return;
				exercise.timer = atoi((const char*)buffer);
			} while (key != sk_Enter && key != sk_2nd && key != sk_Graph);
		} while (exercise.timer == 0);
	};
	
	do_exercise();
	return;
}

void dates_pset(void) {

	uint8_t key;
	uint8_t yPos;
	uint8_t width = 220;
	uint8_t height = 100;
	char buffer[6];
	
	if (SETTINGS_TIMER)
		height = 115;
	
	yPos = 120 - height / 2;
	
	gfx_FillScreen(BG_COLOR);
	draw_pset_symbol();
	icon_button(back_icon, 5, 203);
	icon_button(start_icon, 283, 203);
	dialog(50, yPos, width, height);
	print_centered("Dates", yPos + 10);
	draw_input_box_centered("from", yPos + 25);
	draw_input_box_centered("to", yPos + 40);
	draw_input_box_centered("# of problems:", yPos + 70);
	if (SETTINGS_TIMER)
		draw_input_box_centered("Time/problem:", yPos + 85);
	gfx_BlitBuffer();
	
	/*	Get lower bound (4 digits). Cannot be lower than 1753 because the US and
		Britian accepted the Gregorian calendar in 1752. Don't want to give
		users any misinformation */
	setup_input(false);
	toggle_input_timer(false);
	do {
		memset(buffer, '\0', 6);
		input_config.curr_char = &buffer;
		input_config.visible_buffer = &buffer;
		do {
			key = textio_NumericalInput(&buffer, 4, 46, 154, yPos + 27);
			if (key == sk_Yequ)
				return;
			exercise.lower_bound_1 = atoi((const char*)buffer);
		} while (key != sk_Enter && key != sk_2nd && key != sk_Down);
	} while (exercise.lower_bound_1 < 1735 || exercise.lower_bound_1 > 2099);
	
	// Get upper bound (4 digits). Must not exceed 2099.
	do {
		memset(buffer, '\0', 6);
		input_config.curr_char = &buffer;
		input_config.visible_buffer = &buffer;
		do {
			key = textio_NumericalInput(&buffer, 4, 46, 145, yPos + 42);
			if (key == sk_Yequ)
				return;
			exercise.upper_bound_1 = atoi((const char*)buffer);
		} while (key != sk_Enter && key != sk_2nd && key != sk_Down);
	} while (exercise.upper_bound_1 > 2099 || exercise.upper_bound_1 < exercise.lower_bound_1);
	
	// Get number of problems (2 digits)
	memset(buffer, '\0', 6);
	input_config.curr_char = &buffer;
	input_config.visible_buffer = &buffer;
	do {
		for (;;) {
			key = textio_NumericalInput(&buffer, 2, 46, 185, yPos + 72);
			if (key == sk_Yequ)
				return;
			exercise.num_problems = atoi((const char*)buffer);
			if (key == sk_Enter || key == sk_2nd || (key == sk_Graph && !SETTINGS_TIMER) || (key == sk_Down && SETTINGS_TIMER))
				break;
		};
	} while (exercise.num_problems == 0);

	if (SETTINGS_TIMER) {
		do {
			memset(&buffer, '\0', 4);
			input_config.curr_char = &buffer;
			input_config.visible_buffer = &buffer;
			do {
				key = textio_NumericalInput(&buffer, 3, 46, 184, yPos + 87);
				if (key == sk_Yequ)
					return;
				exercise.timer = atoi((const char*)buffer);
			} while (key != sk_Enter && key != sk_2nd && key != sk_Graph);
		} while (exercise.timer == 0);
	};

	do_exercise();
>>>>>>> 71192d1... Release version 2.0.0
	return;
}