#include "gfx/sprites.h"
#include "gfx/MentalMI.h"
#include "user_interface.h"

#include <stdint.h>

#include <graphx.h>


void print_centered(char* text, uint8_t yPos) {
	gfx_PrintStringXY(text, 160 - gfx_GetStringWidth(text) / 2, yPos);
}

void draw_title(const char *title) {
	gfx_SetTextBGColor(BG_COLOR);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BG_COLOR);
	gfx_SetTextScale(2, 2);
	print_centered(title, 10);
	gfx_SetColor(BLACK);
	gfx_FillRectangle_NoClip(40, 30, 240, 2);
	gfx_SetTextScale(1, 1);							// Reset the text scale before it returns
	return;
}

void button(bool highlight, uint24_t xPos, uint8_t yPos, uint24_t width, uint8_t height) {
	
	uint8_t i, j;
	
	gfx_SetColor(BG_SHADOW_COLOR);
	gfx_FillRectangle_NoClip(xPos + 5, yPos + 5, width - 10, height - 4);
	gfx_FillRectangle_NoClip(xPos + 5, yPos + 5, width - 4, height - 10);
	gfx_FillCircle_NoClip(xPos + width - 6, yPos + height - 6, 6);
	
	gfx_SetColor(BLACK);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++){
			gfx_FillCircle_NoClip(xPos + 6 + i * (width - 13), yPos + 6 + j * (height - 13), 6);
		};
	};
	gfx_FillRectangle_NoClip(xPos + 6, yPos, width - 12, height);
	gfx_FillRectangle_NoClip(xPos, yPos + 6, width, height - 12);
	
	gfx_SetColor(BROWN);
	if (highlight == true)
		gfx_SetColor(HIGHLIGHT_YELLOW);
	gfx_FillRectangle_NoClip(xPos + 5, yPos + 2, width - 10, height - 4);
	gfx_FillRectangle_NoClip(xPos + 3, yPos + 3, width - 6, height - 6);
	gfx_FillRectangle_NoClip(xPos + 2, yPos + 5, width - 4, height - 10);	
}

void text_button(char *text, bool highlight, uint24_t xPos, uint8_t yPos, uint24_t width, uint8_t height) {
	button(highlight, xPos, yPos, width, height);
	gfx_SetTextBGColor(BROWN);
	if (highlight == true)
		gfx_SetTextBGColor(HIGHLIGHT_YELLOW);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BROWN);
	if (highlight == true)
		gfx_SetTextTransparentColor(HIGHLIGHT_YELLOW);
	gfx_SetTextScale(1, 1);
	gfx_PrintStringXY(text, xPos + width/2 - gfx_GetStringWidth(text)/2, yPos + height/2 - 4);
}

void icon_button(gfx_sprite_t *icon, uint24_t xPos, uint24_t yPos) {
	button(false, xPos, yPos, 32, 32);
	gfx_TransparentSprite_NoClip(icon, xPos + 8, yPos + 8);
}


// This is used for the "Paused" and "Error" messages
void status_message(const char *text, uint8_t yPos, uint24_t width) {
	
	int height = 32;
	int xPos = 160 - width / 2;
	
	gfx_SetTextBGColor(BROWN);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BROWN);
	gfx_SetTextScale(2, 2);
	
	gfx_SetColor(BLACK);
	gfx_FillCircle_NoClip(xPos + height/2, yPos + height/2, height/2);
	gfx_FillRectangle_NoClip(xPos + height/2, yPos, width - height, height + 1);
	gfx_FillCircle_NoClip(xPos + width - height / 2, yPos + height/2, height/2);
	gfx_SetColor(BROWN);
	gfx_FillCircle_NoClip(xPos + height/2, yPos + height/2, height/2 - 2);
	gfx_FillRectangle_NoClip(xPos + height/2 + 4, yPos + 2, width - height - 4, height - 3);
	gfx_FillCircle_NoClip(xPos + width - height / 2, yPos + height/2, height/2 - 2);
	print_centered(text, yPos + height/2 - 7);
}


void dialog(uint24_t xPos, uint8_t yPos, uint24_t width, uint8_t height) {

	uint8_t i, j;
	uint8_t radius = 16;
	uint8_t offset = 2;

	gfx_SetColor(BLACK);

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			gfx_FillCircle_NoClip(xPos + radius + (width - 2 * radius) * j, yPos + radius + (height - 2 * radius) * i, radius);
		};
	};

	gfx_FillRectangle_NoClip(xPos + radius, yPos, width - 2 * radius, height + 1);
	gfx_FillRectangle_NoClip(xPos, yPos + radius, width + 1, height - 2 * radius);

	gfx_SetColor(BROWN);

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			gfx_FillCircle_NoClip(xPos + offset + radius + (width - 2 * offset - 2 * radius)  * j, yPos + offset + radius + (height - 2 * offset - 2 * radius) * i, radius);
		};
	};

	gfx_FillRectangle_NoClip(xPos + offset + radius, yPos + offset, width - 2 * radius - (2 * offset), height - (2 * offset) + 1);
	gfx_FillRectangle_NoClip(xPos + offset, yPos + offset + radius, width - (2 * offset) + 1, height - 2 * radius - (2 * offset));
	
	return;
}

void page_indicator(uint8_t num_pages, uint8_t curr_page) {
	
	uint8_t i;
	
	for (i = 0; i < num_pages; i++) {
		gfx_SetColor(BLACK);
		gfx_FillCircle_NoClip(160 - 10 * (num_pages - 1) + 20*i, 220, 6);
		gfx_SetColor(BG_COLOR);
		gfx_FillCircle_NoClip(160 - 10 * (num_pages - 1) + 20*i, 220, 4);
	};
	
	gfx_SetColor(BROWN);
	gfx_FillCircle_NoClip(160 - 10 * (num_pages - 1) + 20*(curr_page - 1), 220, 4);
	return;
}

void dither_screen(void) {
	
	uint8_t i, j;
	
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 20; j++) {
			gfx_TransparentSprite_NoClip(dithering, 16 * j, 16 * i);
		};
	};
	return;	
}