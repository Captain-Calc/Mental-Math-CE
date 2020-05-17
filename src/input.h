#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <keypadc.h>

/* This functions in this file were taken directly from
TEXTIOC v3.5.0 and modified to fit Mental Math CE */


#define INPUT_TIMER_EXPIRED_RET_VAL 0
#define CHRONOMETER_MAX_VAL 16777216

typedef struct {
	uint8_t text_scale;

	uint8_t text_FG_color;
	uint8_t cursor_color;
	uint8_t cursor_width;
	uint8_t cursor_height;
	bool timed_input;
	uint24_t timer_limit;
	bool prgm_name_flag;
	uint8_t curr_keymap_num;
	char *curr_char;
	char *visible_buffer;
} input_config_t;

extern input_config_t input_config;

static void textio_SetInputColorConfig(uint8_t text_FG_color, uint8_t cursor_color);
static void textio_SetPrgmNameFlag(bool prgm_name_flag);
static void textio_SetInitialKeymap(uint8_t keymap);
static void set_cursor_dimensions(uint8_t width, uint8_t height);
void setup_input(bool large_font);
void toggle_input_timer(bool state);

static uint8_t textio_Input(char *buffer, uint8_t buffer_size, uint24_t view_width, uint24_t xPos, uint8_t yPos, uint8_t total_keymap_num, ...);
uint8_t textio_NumericalInput(char *buffer, uint8_t buffer_size, uint24_t visible_input_width, uint24_t xPos, uint8_t yPos);


#endif