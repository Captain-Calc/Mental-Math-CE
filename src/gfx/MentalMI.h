// convpng v7.2
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __MentalMI__
#define __MentalMI__
#include <stdint.h>

#include <stdbool.h>

#define MentalMI_num 17

extern uint8_t *MentalMI[17];
#define home_icon_width 16
#define home_icon_height 16
#define home_icon ((gfx_sprite_t*)MentalMI[0])
#define exit_icon_width 16
#define exit_icon_height 16
#define exit_icon ((gfx_sprite_t*)MentalMI[1])
#define settings_icon_width 16
#define settings_icon_height 16
#define settings_icon ((gfx_sprite_t*)MentalMI[2])
#define back_icon_width 16
#define back_icon_height 16
#define back_icon ((gfx_sprite_t*)MentalMI[3])
#define start_icon_width 16
#define start_icon_height 16
#define start_icon ((gfx_sprite_t*)MentalMI[4])
#define dithering_width 16
#define dithering_height 16
#define dithering ((gfx_sprite_t*)MentalMI[5])
#define problems_worked_icon_width 16
#define problems_worked_icon_height 16
#define problems_worked_icon ((gfx_sprite_t*)MentalMI[6])
#define problems_correct_icon_width 16
#define problems_correct_icon_height 16
#define problems_correct_icon ((gfx_sprite_t*)MentalMI[7])
#define timer_icon_width 16
#define timer_icon_height 16
#define timer_icon ((gfx_sprite_t*)MentalMI[8])
#define addition_symbol_width 16
#define addition_symbol_height 16
#define addition_symbol ((gfx_sprite_t*)MentalMI[9])
#define subtraction_symbol_width 16
#define subtraction_symbol_height 16
#define subtraction_symbol ((gfx_sprite_t*)MentalMI[10])
#define multiplication_symbol_width 16
#define multiplication_symbol_height 16
#define multiplication_symbol ((gfx_sprite_t*)MentalMI[11])
#define division_symbol_width 16
#define division_symbol_height 16
#define division_symbol ((gfx_sprite_t*)MentalMI[12])
#define roots_icon_width 16
#define roots_icon_height 16
#define roots_icon ((gfx_sprite_t*)MentalMI[13])
#define squares_icon_width 16
#define squares_icon_height 16
#define squares_icon ((gfx_sprite_t*)MentalMI[14])
#define complements_icon_width 16
#define complements_icon_height 16
#define complements_icon ((gfx_sprite_t*)MentalMI[15])
#define dates_icon_width 16
#define dates_icon_height 16
#define dates_icon ((gfx_sprite_t*)MentalMI[16])
bool MentalMI_init(void);

#endif
