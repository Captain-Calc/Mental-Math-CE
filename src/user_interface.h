#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdint.h>
#include <string.h>

#include <graphx.h>

void print_centered(const char* text, uint8_t yPos);
void draw_title(const char *title);
void button(bool highlight, uint24_t xPos, uint8_t yPos, uint24_t width, uint8_t height);
void text_button(const char *text, bool highlight, uint24_t xPos, uint8_t yPos, uint24_t width, uint8_t height);
void icon_button(gfx_sprite_t *icon, uint24_t xPos, uint24_t yPos);


void status_message(const char *text, uint8_t yPos, uint24_t width);
void dialog(uint24_t xPos, uint8_t yPos, uint24_t width, uint8_t height);


void page_indicator(uint8_t num_pages, uint8_t curr_page);
void dither_screen(void);


#endif