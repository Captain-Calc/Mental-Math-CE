/* This functions in this file were taken directly from
TEXTIOC v3.5.0 and modified to fit Mental Math CE */

<<<<<<< HEAD
=======
#include "gfx/sprites.h"
#include "gfx/MentalMI.h"
#include "exercise.h"
>>>>>>> 71192d1... Release version 2.0.0
#include "input.h"

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>		// For va_arg, va_list, va_start, va_end
#include <math.h>
#include <string.h>

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

// Debugging
#include <debug.h>

input_config_t input_config;

const char *numerals = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x33\x36\x39\0\0\0\0\0\x32\x35\x38\0\0\0\0\x30\x31\x34\x37\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";


<<<<<<< HEAD
void textio_SetInputColorConfig(uint8_t text_FG_color, uint8_t cursor_color) {
=======
static void textio_SetInputColorConfig(uint8_t text_FG_color, uint8_t cursor_color) {
>>>>>>> 71192d1... Release version 2.0.0
	input_config.text_FG_color = text_FG_color;
	input_config.cursor_color = cursor_color;
}


<<<<<<< HEAD
void textio_SetPrgmNameFlag(bool prgm_name_flag) {
=======
static void textio_SetPrgmNameFlag(bool prgm_name_flag) {
>>>>>>> 71192d1... Release version 2.0.0
	input_config.prgm_name_flag = prgm_name_flag;
}


<<<<<<< HEAD
void textio_SetInitialKeymap(uint8_t keymap_num) {
=======
static void textio_SetInitialKeymap(uint8_t keymap_num) {
>>>>>>> 71192d1... Release version 2.0.0
	input_config.curr_keymap_num = keymap_num;
	input_config.curr_char = NULL;
	input_config.visible_buffer = NULL;
}


<<<<<<< HEAD
/* This function is not part of the TEXTIOC library */
void set_cursor_dimensions(uint8_t width, uint8_t height) {
=======
/* The following two functions are not part of the TEXTIOC library */
static void set_cursor_dimensions(uint8_t width, uint8_t height) {
>>>>>>> 71192d1... Release version 2.0.0
	input_config.cursor_width = width;
	input_config.cursor_height = height;
}

<<<<<<< HEAD

uint8_t textio_Input(char *buffer, uint8_t buffer_size, uint24_t visible_input_width, uint24_t xPos, uint8_t yPos, uint8_t total_keymap_num, ...) {
=======
void setup_input(bool large_font) {
	textio_SetInputColorConfig(BLACK, BLACK);
	textio_SetInitialKeymap(1);
	input_config.text_scale = 1;
	set_cursor_dimensions(1, 9);
	if (large_font) {
		input_config.text_scale = 2;
		set_cursor_dimensions(2, 16);
	};
	return;
}

void toggle_input_timer(bool state) {
	input_config.timed_input = false;
	if (state)
		input_config.timed_input = true;
	return;
}


static uint8_t textio_Input(char *buffer, uint8_t buffer_size, uint24_t visible_input_width, uint24_t xPos, uint8_t yPos, uint8_t total_keymap_num, ...) {
>>>>>>> 71192d1... Release version 2.0.0
	
	char *visible_buffer;
	char *last_visible_char;
	char *curr_char;
	char *temp1;
	char *temp2;
	
	uint8_t text_BG_color;
	uint24_t cursor_xPos = xPos;
	
	uint24_t i;
	bool cursor_active = false;
	uint8_t key = '\0';

	va_list keymap_list;
	const char *curr_keymap;
	const char *curr_indicator;
	uint8_t curr_keymap_num;
	
	// Debugging vars
	uint8_t j;
	char *letter_chk = '\0';
	
	// Setup
	gfx_SetTextFGColor(input_config.text_FG_color);
	
	// curr_char and visible_buffer are saved to input_config to preserve them between function calls
	curr_char = input_config.curr_char;
	if (curr_char < buffer)
		curr_char = buffer;
	
	visible_buffer = input_config.visible_buffer;
	if (visible_buffer < buffer)
		visible_buffer = buffer;
	
	va_start(keymap_list, total_keymap_num);
	curr_keymap = va_arg(keymap_list, const char*);
	curr_indicator = va_arg(keymap_list, const char*);
	curr_keymap_num = 1;
	
	// Search the supplied keymaps for the last one used/set
	while (curr_keymap_num != input_config.curr_keymap_num) {
		curr_keymap = va_arg(keymap_list, const char*);
		curr_indicator = va_arg(keymap_list, const char*);
		curr_keymap_num++;
	};	
		
	cursor_active = false;
	if (curr_char < buffer + buffer_size)
		cursor_active = true;
		
	text_BG_color = gfx_GetPixel(cursor_xPos, yPos);
	gfx_SetTextBGColor(text_BG_color);
	gfx_SetTextTransparentColor(text_BG_color);
<<<<<<< HEAD
=======
	gfx_SetTextScale(input_config.text_scale, input_config.text_scale);
>>>>>>> 71192d1... Release version 2.0.0
		
	// Erase all visible input and redraw it
	gfx_SetColor(text_BG_color);
	gfx_FillRectangle(xPos, yPos, visible_input_width, input_config.cursor_height);
	gfx_SetTextXY(xPos + 1, yPos + 1);
	
	cursor_xPos = xPos;
	temp1 = visible_buffer;
	i = 0;
	while (*temp1 != '\0') {
		i += gfx_GetCharWidth(*temp1);
		if (i > visible_input_width)
			break;
		gfx_PrintChar(*temp1++);
		if (temp1 == curr_char)
			cursor_xPos += i;
	};
	
	if (gfx_GetDraw())
		gfx_BlitRectangle(1, xPos, yPos, visible_input_width, input_config.cursor_height);

	if (curr_char == buffer && *curr_char == '\0'){
		last_visible_char = buffer;
	} else {
		last_visible_char = --temp1;
	};
		
		
	// Debugging code -----------------------------------
	dbg_sprintf(dbgout, "cursor_xPos = %d   | *visible_buffer = %c\n", cursor_xPos, *visible_buffer);
	dbg_sprintf(dbgout, "cursor_active = %d | *curr_char = %c\n", cursor_active, *curr_char);
	dbg_sprintf(dbgout, "*last_visible_char = %c\n", *last_visible_char);
	dbg_sprintf(dbgout, "Buffer:");
	
	letter_chk = buffer;
	for (j = 0; j < buffer_size; j++)
		dbg_sprintf(dbgout, " %x", *letter_chk++);
		
	dbg_sprintf(dbgout, " |");
	
	letter_chk = buffer;
	for (j = 0; j < buffer_size; j++) {
		if (*letter_chk == '\0') {
			dbg_sprintf(dbgout, ".");
		} else {
			dbg_sprintf(dbgout,"%c", *letter_chk++);
		};
	};
		
	dbg_sprintf(dbgout, "|\n");
	// End of debugging code ----------------------------
		
<<<<<<< HEAD
		
	// Wait for input and display cursor
	do {
=======
	/* Start the chronometer */
	if (input_config.timed_input)
		timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_0INT | TIMER1_DOWN;
	gfx_SetTextScale(1, 1);
		
	// Wait for input and display cursor
	do {
		
		if (input_config.timed_input) {
			if (timer_IntStatus & TIMER1_RELOADED) {
				if (exercise.chronometer < CHRONOMETER_MAX_VAL)
					exercise.chronometer++;
				gfx_SetColor(gfx_GetPixel(283, 10));
				gfx_FillRectangle_NoClip(283, 10, 30, 7);
				gfx_SetTextXY(283, 10);
				gfx_PrintUInt(input_config.timer_limit - exercise.chronometer, 3);
				gfx_BlitRectangle(1, 283, 10, 30, 7);
				timer_IntAcknowledge = TIMER1_RELOADED;
			};
			if (exercise.chronometer == input_config.timer_limit)
				return INPUT_TIMER_EXPIRED_RET_VAL;
		};
		
>>>>>>> 71192d1... Release version 2.0.0
		if (cursor_active) {
			gfx_SetColor(input_config.cursor_color);
			gfx_Rectangle_NoClip(cursor_xPos, yPos, input_config.cursor_width, input_config.cursor_height);
			if (gfx_GetDraw())
				gfx_BlitRectangle(1, cursor_xPos, yPos, input_config.cursor_width, input_config.cursor_height);
		};
			
		i = 0;
			
			do {
			key = os_GetCSC();
		} while (!key && i++ < 4000);
	
		if (cursor_active) {
			gfx_SetColor(text_BG_color);
			gfx_Rectangle_NoClip(cursor_xPos, yPos, input_config.cursor_width, input_config.cursor_height);
			if (gfx_GetDraw())
				gfx_BlitRectangle(1, cursor_xPos, yPos, input_config.cursor_width, input_config.cursor_height);
		};
		
		while (!key && i++ < 8000)
			key = os_GetCSC();;
		
	} while (!key);
	
	//dbg_sprintf(dbgout, "key = %d\n", key);
	
	/* Exit if the cursor is at the start of the buffer and there are no chars 
	   in front of the cursor */
	/*
	if (key == sk_Clear && curr_char == buffer && *curr_char == '\0') {
		va_end(keymap_list);
		return;
	};
		if (key == sk_Enter) {
		// Debugging code omitted
		va_end(keymap_list);
		return;
	};
	*/
	
	if (key == sk_Clear) {
		if (curr_char == buffer) {
			temp1 = curr_char;
			while (*temp1 != '\0')
				*temp1++ = '\0';
		} else {
			/* If the cursor is in the middle of a word, shift the chars in front of the cursor back */
			while (curr_char > buffer) {
				temp1 = curr_char;
				curr_char--;
				while (*temp1 != '\0') {
					temp2 = temp1;
					*(temp1 - 1) = *temp2;
					temp1++;
				};
				*--temp1 = '\0';
			};
		};
		visible_buffer = buffer;
	};
	
	if (key == sk_Del && curr_char > buffer) {
		if (visible_buffer != buffer)
			visible_buffer--;
		
		*--curr_char = '\0';
		
		/* If there are any chars in front of the cursor, shift them back */
		if (curr_char < buffer + buffer_size) {
			if (*(curr_char + 1) != '\0') {
				temp1 = curr_char;
				do {
					temp2 = ++temp1;
					*(temp1 - 1) = *temp2;
				} while (*temp1 != '\0');
			};
		};
	} else {
		// Debugging code
		dbg_sprintf(dbgout, "No char deleted\n");
	};
	
	if (key == sk_Left && curr_char > buffer) {
		if (curr_char == visible_buffer)
			visible_buffer--;
		curr_char--;
	};
	
	if (key == sk_Right && *curr_char != '\0') {
		if (*++curr_char != '\0' && (curr_char - 1) == last_visible_char)
			visible_buffer++;
	};
	
	if (key == sk_Alpha) {
		if (curr_keymap_num == total_keymap_num) {
			va_start(keymap_list, total_keymap_num);
			curr_keymap_num = 0;
		};
		
		curr_keymap = va_arg(keymap_list, const char*);
		curr_indicator = va_arg(keymap_list, const char*);
		curr_keymap_num++;
		
		gfx_SetTextBGColor(0x00);
		gfx_SetTextFGColor(0xFF);
		gfx_SetTextTransparentColor(0x00);
		gfx_SetColor(0x00);
		
		gfx_FillRectangle(cursor_xPos, yPos, input_config.cursor_height, input_config.cursor_height);
		gfx_PrintStringXY(curr_indicator, cursor_xPos + 1, yPos + 1);
		if (gfx_GetDraw())
			gfx_BlitRectangle(1, xPos, yPos, visible_input_width, input_config.cursor_height);
		
		delay(400);
		gfx_SetColor(text_BG_color);
		gfx_FillRectangle(cursor_xPos, yPos, input_config.cursor_height, input_config.cursor_height);
		gfx_SetTextBGColor(text_BG_color);
		gfx_SetTextFGColor(input_config.text_FG_color);
		gfx_SetTextTransparentColor(text_BG_color);
	};
	
	// The second arg verifies that there is space in the buffer for another char
	if (cursor_active && *(buffer + buffer_size - 1) == '\0' && curr_keymap[key]) {
		
		dbg_sprintf(dbgout,"number = %c\n", curr_keymap[key]);
		
		/* If there are any chars in front of the cursor, shift them forward */
		if (*curr_char != '\0') {
			temp1 = buffer + buffer_size;
			while (temp1 > curr_char) {
				temp2 = --temp1;
				*(temp1 + 1) = *temp2;
			};
		};
		
		if (!input_config.prgm_name_flag || (input_config.prgm_name_flag && !(curr_keymap == numerals && curr_char == buffer))) {
			*curr_char = curr_keymap[key];
			if (cursor_xPos - xPos + gfx_GetCharWidth(*curr_char++) > visible_input_width)
				visible_buffer++;
		};
	} else {
		// Debugging code
		dbg_sprintf(dbgout, "No char added\n");
	};
	
	input_config.curr_keymap_num = curr_keymap_num;
	input_config.curr_char = curr_char;
	input_config.visible_buffer = visible_buffer;
	va_end(keymap_list);
<<<<<<< HEAD
	return key;
}


uint8_t textio_NumericalInput(char *buffer, uint8_t buffer_size, uint24_t visible_input_width, uint24_t xPos, uint8_t yPos) {
	textio_SetPrgmNameFlag(false);
	return textio_Input(buffer, buffer_size, visible_input_width, xPos, yPos, 2, numerals, "1");
=======
	
	// Erase all visible input and redraw it
	gfx_SetTextScale(input_config.text_scale, input_config.text_scale);
	gfx_SetColor(text_BG_color);
	gfx_FillRectangle(xPos, yPos, visible_input_width, input_config.cursor_height);
	gfx_SetTextXY(xPos + 1, yPos + 1);
	
	cursor_xPos = xPos;
	temp1 = visible_buffer;
	i = 0;
	while (*temp1 != '\0') {
		i += gfx_GetCharWidth(*temp1);
		if (i > visible_input_width)
			break;
		gfx_PrintChar(*temp1++);
		if (temp1 == curr_char)
			cursor_xPos += i;
	};
	
	if (gfx_GetDraw())
		gfx_BlitRectangle(1, xPos, yPos, visible_input_width, input_config.cursor_height);
	
	return key;
}

uint8_t textio_NumericalInput(char *buffer, uint8_t buffer_size, uint24_t visible_input_width, uint24_t xPos, uint8_t yPos) {
	textio_SetPrgmNameFlag(false);
	return textio_Input(buffer, buffer_size, visible_input_width, xPos, yPos, 2, numerals, "1");
}


uint8_t numerical_input(char *buffer, uint8_t magnitude, uint8_t input_height, uint24_t input_width, uint24_t xPos, uint8_t yPos) {
	
	uint8_t key;
	
	textio_SetPrgmNameFlag(false);
	key = textio_NumericalInput(buffer, magnitude, input_width, xPos, yPos);
	gfx_BlitRectangle(1, xPos, yPos, input_width, input_height);

	return key;
>>>>>>> 71192d1... Release version 2.0.0
}