#ifndef PROBLEM_SETS_H
#define PROBLEM_SETS_H

#include <stdint.h>

static uint8_t* get_pset_array(void);
static uint8_t array_len(void);
static void draw_pset_symbol(void);
static const char* build_pset_button_str(uint8_t *pset_array, uint8_t offset);
static void draw_basic_pset(uint8_t *pset_array, uint8_t selection_col, uint8_t selection_row);
static void get_bounds(uint8_t *pset_array, uint8_t sel_col, uint8_t sel_row);
static void draw_input_box_centered(const char *label, uint8_t yPos);
static int get_num_problems(void);

void basic_problem_set(void);
void roots_squares_pset(void);
void complements_pset(void);
void dates_pset(void);

#endif