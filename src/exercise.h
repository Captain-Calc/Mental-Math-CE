#ifndef EXERCISE_H
#define EXERCISE_H

#include <stdint.h>
#include <stdbool.h>

#include <graphx.h>


/*	The following can be saved to the appvar:
		The exercise type
		The problem set
		The time/problem
		
		
	The structure of a particular save:
	
	---+-----------------+---------------+----------------+---
	...|  exercise type  |  problem set  |  time/problem  |...
	---+-----------------+---------------+----------------+---
	
	   |-----(1 byte)----|---(2 bytes)---|----(3 bytes)---|
	
	With 18 individual problem sets, the total save size will be
	18 * (6 bytes) = 108 bytes of raw data.	This raw data will be
	encrypted before being saved, so the data will minimally be
	108 bytes.
	
	The 2 bytes for the problem set will be the upper and lower bounds
	of the exercise for the basic problem sets and the upper and lower
	bounds for the roots and powers problem sets. The complements will
	have a maximum bound of 10,000, so it will take two bytes. The dates
	have two-byte upper and lower bounds, so they will not fit. However,
	the bounds for this exercise do not impact how well the user does on
	the exercise, so the two bytes can be left unwritten for the dates
	exercise.
*/

typedef struct {
	uint8_t type;
	uint24_t lower_bound_1;
	uint24_t upper_bound_1;
	uint24_t lower_bound_2;
	uint24_t upper_bound_2;
	uint8_t num_problems;
	uint8_t problems_worked;
	uint8_t problems_correct;
	/* This must be bounds-checked to ensure that it
	never exceeds 16,777,216 */
	uint24_t chronometer;
	uint24_t time_per_problem;
	uint24_t timer;
} exercise_t;

extern exercise_t exercise;


static void draw_input_bar(void);
static void draw_counter_dialog(gfx_sprite_t *icon, uint24_t xPos, uint8_t yPos, uint8_t width);
void print_int(uint24_t integer, uint24_t xPos, uint8_t yPos);
static void update_counters(bool redraw);
uint24_t get_int_width(uint24_t integer);
static void generate_random_numbers(void);
static void get_solution(void);
static void draw_problem(void);
<<<<<<< HEAD
static void check_user_solution(char *user_solution);
static void check_user_remainder(char *user_remainder);
=======
static bool check_user_solution(char *user_solution);
static void draw_user_solution_result(bool correct);
static bool check_user_remainder(char *user_remainder);
static void draw_user_remainder_result(bool correct);
static bool pause_exercise(void);
>>>>>>> 71192d1... Release version 2.0.0
static void show_stats(void);

void do_exercise(void);


#endif