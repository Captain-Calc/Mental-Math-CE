#include "gfx/sprites.h"
#include "gfx/MentalMI.h"
#include "error_handler.h"
#include "exercise.h"
#include "defines.h"
#include "input.h"
#include "settings.h"
#include "user_interface.h"

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

// Temporary
#include <debug.h>
#include "calcdbg.h"


exercise_t exercise;

typedef struct {
	uint24_t number_1;
	uint24_t number_2;
} numbers_t;

numbers_t numbers;

typedef struct {
	uint8_t month;
	uint8_t day;
	uint24_t year;
} date_t;

date_t date;

typedef struct {
	long unsigned int solution;
	uint24_t remainder;
} answer_t;

answer_t answer;


static void draw_input_bar(void) {
	gfx_SetColor(BLACK);
	gfx_FillRectangle_NoClip(5, 220, 310, 2);
	gfx_PrintStringXY("ANSWER", 5, 224);
	
	if (exercise.type == DIVISION) {
		gfx_SetColor(BG_COLOR);
		gfx_FillRectangle_NoClip(196, 220, 4, 2);
		gfx_PrintStringXY("REMAINDER", 200, 224);
	};
	
	return;
}


static void draw_counter_dialog(gfx_sprite_t *icon, uint24_t xPos, uint8_t yPos, uint8_t width) {
	
	uint8_t i, j;
	uint8_t height = 18;
	
	gfx_SetColor(BG_SHADOW_COLOR);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++){
			gfx_FillCircle_NoClip(xPos + 6 + i * (width - 13), yPos + 6 + j * (height - 13), 6);
		};
	};
	gfx_FillRectangle_NoClip(xPos + 6, yPos, width - 12, height);
	gfx_FillRectangle_NoClip(xPos, yPos + 6, width, height - 12);
	
	gfx_TransparentSprite_NoClip(icon, xPos + 2, yPos + 1);
	return;
}

void print_int(uint24_t integer, uint24_t xPos, uint8_t yPos) {
	
	gfx_SetTextXY(xPos, yPos);
	gfx_PrintUInt(integer, log10((integer + 1)) + 1);
}

static void update_counters(bool redraw) {
	
	uint8_t i;
	
	draw_counter_dialog(problems_worked_icon, 5, 5, 56);
	draw_counter_dialog(problems_correct_icon, 65, 5, 56);
	
	gfx_SetTextBGColor(BG_SHADOW_COLOR);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BG_SHADOW_COLOR);
	gfx_SetTextScale(1, 1);
	
	for (i = 0; i < 2; i++) {
		gfx_SetTextFGColor(WHITE);
		if (i == 1)
			gfx_SetTextFGColor(BLACK);
		
		print_int(exercise.problems_worked, 32, 10);
		print_int(exercise.problems_correct, 92, 10);
		if (redraw) {
			delay(100);
			gfx_BlitRectangle(1, 5, 5, 121, 18);
		};
	};
}

uint24_t get_int_width(uint24_t integer) {
	
	char int_str[6] = {'\0'};
	uint24_t width;
	int i;
	
	sprintf(int_str, "%d", integer);
	
	dbg_sprintf(dbgout, "\n");
	
	for (i = 0; i < 11; i++)
		dbg_sprintf(dbgout, "%c", int_str[i]);
	width = gfx_GetStringWidth(int_str);
	dbg_sprintf(dbgout, "\nwidth = %d\n", width);
	return width;
}


static bool isleapyear(uint24_t year) {
	if ((year % 4) == 0 && (year % 100) != 0)
		return true;
	else if ((year % 400) == 0)
		return true;
	else
		return false;
}


static uint8_t day_of_week(uint8_t month, uint8_t day, uint24_t year) {

	uint8_t year_code, month_code, century_code;
	bool leap_year;
	int leap_year_code;


	uint8_t months[] = {6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	uint8_t centuries[] = {5, 3, 1, 0};
	/*
	1700s = 5
	1800s = 3
	1900s = 1
	2000s = 0
	
	*/

	year_code = (year % 100) + (((year % 100) / 4) % 7);
	month_code = months[month];
	century_code = centuries[(year / 100) - 17];

	leap_year_code = 0;
	if (isleapyear(year) && month <= 1)
		leap_year_code = -1;

	return (year_code + month_code + century_code + day + leap_year_code) % 7;
}


static void generate_random_numbers(void) {
	
	uint8_t num_days;
	
	srand(rtc_Time());
	
	if (exercise.type < 4) {
		numbers.number_1 = randInt(exercise.lower_bound_1, exercise.upper_bound_1);
		numbers.number_2 = randInt(exercise.lower_bound_2, exercise.upper_bound_2);
	};
	
	// For the roots, squares, and complements exercises, there is only one set of bounds
	if (exercise.type != DATES)
		numbers.number_1 = randInt(exercise.lower_bound_1, exercise.upper_bound_1);
	
	/*	In the complements exercise, the number entered by the user in the problem set menu
		is stored in numbers.upper_bound_1   The generated number can be any number between 0
		and the entered number, so numbers.lower_bound_1 is set to 0 by default in the problem
		set menu */
		
	
	dbg_sprintf(dbgout, "number_1 = %d\n", numbers.number_1);
	
	if (exercise.type == DATES) {
		date.month = randInt(0, 11);
		date.year = randInt(exercise.lower_bound_1, exercise.upper_bound_1);
		
		num_days = 31;
		if (((date.month - (date.month < 7)) % 2) == 0)
			num_days = 30;
		
		if (date.month == 1) {
			num_days = 28;
			if (isleapyear(date.year))
				num_days = 29;
		};
		date.day = randInt(1, num_days);
	};
	return;
}


static void get_solution(void) {
	
	uint24_t temp_num;
	
	switch (exercise.type) {
		
		case ADDITION:
		answer.solution = numbers.number_1 + numbers.number_2;
		break;
		
		case SUBTRACTION:
		if (numbers.number_1 < numbers.number_2) {		// Swap the numbers if necessary to avoid negative solutions
			dbg_sprintf(dbgout, "Swapped numbers\n");
			temp_num = numbers.number_1;
			numbers.number_1 = numbers.number_2;
			numbers.number_2 = temp_num;
		};
		answer.solution = numbers.number_1 - numbers.number_2;
		break;
		
		case MULTIPLICATION:
		answer.solution = numbers.number_1 * numbers.number_2;
		break;
		
		case DIVISION:
		answer.solution = numbers.number_1 / numbers.number_2;
		answer.remainder = numbers.number_1 % numbers.number_2;
		break;
		
		case ROOTS:			// In this case, the number generated is the solution and the problem is the number's square
		answer.solution = numbers.number_1;
		break;
		
		case SQUARES:
		answer.solution = numbers.number_1 * numbers.number_1;
		break;
		
		case COMPLEMENTS:	// The solution is the difference between the number the user entered and the generated number
		answer.solution = exercise.upper_bound_1 - numbers.number_1;
		break;
		
		case DATES:
		answer.solution = day_of_week(date.month, date.day, date.year);
		break;
		
		default:
		error();
		print_centered("The program encountered",110);
		print_centered("a fatal error.",120);
		print_centered("All settings and saved",130);
		print_centered("times will be preserved.",140);
		print_centered("Press [Graph] or [Clear]",150);
		print_centered("to exit",160);
		close_program();
	}
	
	return;
}

static void draw_problem(void) {
	
	gfx_sprite_t *symbol;
	uint8_t num_1_magnitude, num_2_magnitude;
	uint24_t int_width, temp_num;
	
	num_1_magnitude = log10((double)(numbers.number_1 + 1)) + 1;
	num_2_magnitude = log10((double)(numbers.number_2 + 1)) + 1;
	
	// Erase previous problem
	gfx_SetColor(BG_COLOR);
	gfx_FillRectangle_NoClip(0, 60, 320, 160);
	
	gfx_SetTextBGColor(BG_COLOR);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BG_COLOR);
	gfx_SetTextScale(3, 3);
	
	if (exercise.type < 4) {
		
		print_int(numbers.number_1, 132 - get_int_width(numbers.number_1), 100);
		
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
			
			default:
			symbol = division_symbol;
		};
		
		gfx_TransparentSprite_NoClip(symbol, 152, 103);

		gfx_SetTextXY(188, 100);
		gfx_PrintUInt(numbers.number_2, num_2_magnitude);
	};
	
	if (exercise.type == ROOTS) {
		temp_num = numbers.number_1 * numbers.number_1;
		numbers.number_1 = temp_num;
		int_width = get_int_width(numbers.number_1);
		print_int(numbers.number_1, 160 - int_width / 2, 100);
		gfx_SetColor(BLACK);
		gfx_FillRectangle_NoClip(156 - int_width / 2, 96, int_width + 6, 2);
		gfx_Line_NoClip(156 - int_width / 2, 96, 148 - int_width / 2, 122);
		gfx_Line_NoClip(157 - int_width / 2, 96, 149 - int_width / 2, 122);
		gfx_Line_NoClip(148 - int_width / 2, 122, 143 - int_width / 2, 104);
		gfx_Line_NoClip(147 - int_width / 2, 122, 142 - int_width / 2, 104);
		gfx_Line_NoClip(143 - int_width / 2, 104, 138 - int_width / 2, 109);
		gfx_Line_NoClip(142 - int_width / 2, 104, 137 - int_width / 2, 109);
	};
	
	if (exercise.type == SQUARES) {
		int_width = get_int_width(numbers.number_1);
		print_int(numbers.number_1, 160 - int_width / 2, 100);
		gfx_SetTextScale(1, 1);
		gfx_PrintStringXY("2", 162 + int_width / 2, 98);
	};
	
	if (exercise.type == COMPLEMENTS) {
		
		print_int(numbers.number_1, 160 - get_int_width(numbers.number_1) / 2, 100);
		draw_counter_dialog(complements_icon, 126, 5, get_int_width(exercise.upper_bound_1) + 10);
		gfx_SetTextScale(1, 1);
		print_int(exercise.upper_bound_1, 153, 10);		// Print the sum of the complements for reference
	};
	
	if (exercise.type == DATES) {
		
		char date_str[19] = {'\0'};
		char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
		
		sprintf(date_str, "%s %d, %d", months[date.month], date.day, date.year);
		gfx_SetTextScale(2, 2);
		print_centered(date_str, 100);
		
		calcdbg_dump(date_str, 19);
		dbg_sprintf(dbgout, "date.month = %d\ndate.day = %d\ndate.year = %d\nanswer = %d\n", date.month, date.day, date.year, answer.solution);
	};
	
	return;
}

static bool check_user_solution(char *user_solution) {
	
	uint24_t user_solution_int;
	
	user_solution_int = atoi((const char*)user_solution);
	
	/*	Sunday can be either 7 or 0; the day_of_week routine returns 0 for it
		So if user enters 7, convert it to zero so that it will be correct */
	if (exercise.type == DATES && user_solution_int == 7)
		user_solution_int = 0;
	
	if ((user_solution_int == answer.solution) && user_solution[0] != '\0')
		return true;
	
	return false;
}

static void draw_user_solution_result(bool correct) {
	
	uint24_t xPos;
	uint8_t solution_magnitude;
	
	solution_magnitude = log10((double)(answer.solution + 1)) + 1;
	
	/*  Variable for horizontal solution/icon placement */
	xPos = 315;
	if (exercise.type == DIVISION)
		xPos = 191;
	
	if (correct) {
		gfx_TransparentSprite_NoClip(problems_correct_icon, xPos - 16, 202);
	} else {
		gfx_SetTextBGColor(BG_COLOR);
		gfx_SetTextFGColor(BLACK);
		gfx_SetTextTransparentColor(BG_COLOR);
		gfx_SetTextScale(1, 1);
		gfx_SetTextXY(xPos - 8 * solution_magnitude, 211);
		
		if (exercise.type == DIVISION) {
			gfx_PrintUInt(answer.solution, solution_magnitude);
			return;
		};
		
		if (exercise.type == DATES && answer.solution == 0) {
			gfx_PrintStringXY("7 or 0", 315 - 38, 211);
			return;
		};
		
		/* Default for basic operations and some date solutions */
		gfx_PrintUInt(answer.solution, solution_magnitude);
	};

	return;
}


static bool check_user_remainder(char *user_remainder) {
	
	if ((atoi((const char*)user_remainder) == answer.remainder) && user_remainder[0] != '\0')
		return true;
	
	return false;
}

static void draw_user_remainder_result(bool correct) {
	
	uint8_t remainder_magnitude;
	
	remainder_magnitude = log10((double)(answer.remainder + 1)) + 1;
	
	if (correct) {
		gfx_TransparentSprite_NoClip(problems_correct_icon, 299, 202);
	} else {
		gfx_SetTextBGColor(BG_COLOR);
		gfx_SetTextFGColor(BLACK);
		gfx_SetTextTransparentColor(BG_COLOR);
		gfx_SetTextScale(1, 1);
		gfx_SetTextXY(315 - 8 * remainder_magnitude, 211);
		gfx_PrintUInt(answer.remainder, remainder_magnitude);
	};
	return;
}

static bool pause_exercise(void) {
	
	uint8_t key;
	
	dither_screen();
	status_message("PAUSED", 54, 200);
	icon_button(start_icon, 5, 203);
	icon_button(exit_icon, 283, 203);
	gfx_SwapDraw();
	
	do {
		key = os_GetCSC();
	} while (!key);
	
	if (key == sk_Graph)
		return true;
	return false;
}


static void show_stats(void) {
	
	gfx_FillScreen(BG_COLOR);
	draw_title("Statistics");
	gfx_PrintStringXY("Problems worked:", 40, 50);
	print_int(exercise.problems_worked, 280 - get_int_width(exercise.problems_worked), 50);
	gfx_PrintStringXY("Problems correct:", 40, 60);
	print_int(exercise.problems_correct, 280 - get_int_width(exercise.problems_correct), 60);
	gfx_PrintStringXY("Total Time (seconds):", 40, 70);
	print_int(exercise.chronometer, 280 - get_int_width(exercise.chronometer), 70);
	gfx_PrintStringXY("Time/Problem (seconds):", 40, 80);
	exercise.time_per_problem = exercise.chronometer / exercise.problems_worked;
	print_int(exercise.time_per_problem, 280 - get_int_width(exercise.time_per_problem), 80);
	
	
	icon_button(exit_icon, 283, 203);
	
	gfx_BlitBuffer();
	
	do {
		kb_Scan();
	} while(!((kb_Data[1] & kb_Graph) || (kb_Data[6] & kb_Clear)));
	
	return;
}

void do_exercise(void) {
	
	uint8_t key;
	
	char user_solution[11];		/* Cannot exceed 10 digits (99,999 * 99,999). The type for the integer value must be uint24_t */
	char user_remainder[5];		/* Cannot exceed 4 digits. The check function does not have a declared type for this value */
	
	gfx_FillScreen(BG_COLOR);
	
	if (SETTINGS_TIMER)
		draw_counter_dialog(timer_icon, 259, 5, 56);
	
	draw_input_bar();
	
	exercise.problems_worked = 0;
	exercise.problems_correct = 0;
	update_counters(false);
	
	/* Setup the chronometer */
	timer_Control = TIMER1_DISABLE;
	timer_1_ReloadValue = timer_1_Counter = 32768;
	exercise.chronometer = 0;
	
	for (;;) {
		
		generate_random_numbers();
		get_solution();
		draw_problem();
		
		gfx_BlitBuffer();
		
		toggle_input_timer(SETTINGS_TIMER);
		input_config.timer_limit = exercise.chronometer + exercise.timer;
		setup_input(true);
		memset(user_solution, '\0', 11);
		input_config.curr_char = &user_solution;
		input_config.visible_buffer = &user_solution;
		
		delay(200);			// Prevent a slow key release from triggering input escape
		
		EDIT_SOLUTION:
		
		do {
			do {
				key = textio_NumericalInput(user_solution, 10, 191, 5, 202);
				if (key == sk_Mode) {
					if (pause_exercise())
						return;
					gfx_BlitBuffer();
				};
				if ((SETTINGS_AUTO_CHECK && check_user_solution(user_solution)) || (key == INPUT_TIMER_EXPIRED_RET_VAL))
					goto BREAK_LOOP_1;
			} while (key != sk_Enter && key != sk_2nd);
		} while (user_solution[0] == '\0');
		
		BREAK_LOOP_1:
		
		if (exercise.type == DIVISION && answer.remainder > 0) {
			
			memset(user_remainder, '\0', 5);
			input_config.curr_char = &user_remainder;
			input_config.visible_buffer = &user_remainder;
			do {
				do {
					key = textio_NumericalInput(user_remainder, 4, 115, 200, 202);
					if (key == sk_Mode) {
						if (pause_exercise())
							return;
						gfx_BlitBuffer();
					};
					if ((SETTINGS_AUTO_CHECK && check_user_remainder(user_remainder)) || (key == INPUT_TIMER_EXPIRED_RET_VAL) || key == sk_Left)
						goto BREAK_LOOP_2;
				} while (key != sk_Enter && key != sk_2nd);
			} while (user_remainder[0] == '\0');
		};
		
		BREAK_LOOP_2:
		
		if (key == sk_Left)
			goto EDIT_SOLUTION;
		
		if (check_user_solution(user_solution)) {
			draw_user_solution_result(true);
			if (exercise.type == DIVISION) {
				if (check_user_remainder(user_remainder) || answer.remainder == 0) {
					draw_user_remainder_result(true);
					exercise.problems_correct++;
				} else {
					draw_user_remainder_result(false);
				};
			} else {
				exercise.problems_correct++;
			};
		} else {
			draw_user_solution_result(false);
		};
		
		gfx_BlitRectangle(1, 5, 202, 310, 16);											// Copy the results to the screen
		
		exercise.problems_worked++;
		update_counters(true);
	
		do {
			key = os_GetCSC();
		} while (!key);
		
		if (key == sk_Mode) {
			if (pause_exercise() == 1)
				break;
			gfx_BlitBuffer();
		};
		
		if (exercise.problems_worked == exercise.num_problems) {		// If all problems are done, end exercise, generate stats, and
			show_stats();												// save them
			break;
		};
	}
	return;
}