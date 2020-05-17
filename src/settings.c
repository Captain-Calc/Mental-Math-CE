#include "gfx/sprites.h"
#include "gfx/MentalMI.h"
#include "defines.h"
#include "settings.h"
#include "user_interface.h"

#include <graphx.h>
#include <keypadc.h>

// Temporary
#include <debug.h>


void print_control(const char *key, const char *action, uint8_t yPos) {
	gfx_PrintStringXY(key, 40, yPos);
	gfx_PrintStringXY("-", 150, yPos);
	gfx_PrintStringXY(action, 164, yPos);
	return;
}


bool chkbit(uint8_t byte, uint8_t pos) {
	if (byte & (1 << pos))
		return true;
	return false;
}


uint8_t setbit(uint8_t byte, uint8_t pos) {
	if (chkbit(byte, pos)) {
		byte -= (1 << pos);
	} else {
		byte += (1 << pos);
	};
	return byte;
}


void toggle(bool state, uint24_t xPos, uint8_t yPos, uint24_t width) {
	
	gfx_SetColor(BLACK);
	gfx_FillCircle_NoClip(xPos + 5, yPos + 5, 6);
	gfx_FillRectangle_NoClip(xPos + 5, yPos - 1, width, 13);
	gfx_FillCircle_NoClip(xPos + width + 5, yPos + 5, 6);
	gfx_SetColor(LT_GRAY);
	if (state)
		gfx_SetColor(GREEN);
	gfx_FillCircle_NoClip(xPos + 5, yPos + 5, 5);
	gfx_FillRectangle_NoClip(xPos + 5, yPos, width, 11);
	gfx_FillCircle_NoClip(xPos + width + 5, yPos + 5, 5);
	gfx_SetColor(BLACK);
	gfx_FillCircle_NoClip(xPos + 5 + (width * state), yPos + 5, 7);
	gfx_SetColor(LT_GRAY);
	if (state)
		gfx_SetColor(GREEN);
	gfx_FillCircle_NoClip(xPos + 5 + (width * state), yPos + 5, 6);
	return;
}


void draw_settings_button(char *title, bool button_state, bool toggle_state, uint8_t yPos) {
	
	button(button_state, 40, yPos, 240, 32);
	gfx_SetTextBGColor(BROWN);
	gfx_SetTextFGColor(BLACK);
	gfx_SetTextTransparentColor(BROWN);
	gfx_SetTextScale(1, 1);
	gfx_PrintStringXY(title, 50, yPos + 12);
	toggle(toggle_state, 240, yPos + 10, 14);
	return;
}


uint8_t settings_page(void) {
	
	bool button_state, toggle_state;
	bool arrows;
	uint8_t selection;
	uint8_t i;
	
	char *setting_titles[3] = {"AUTO-CHECK", "TIMER", "COMING SOON!"};
	
	selection = 0;
	
	for (;;) {
		
		dbg_sprintf(dbgout, "settings.byte = %d\n", settings.byte);
		
		draw_title("Settings");
		for (i = 0; i < 3; i++) {
			button_state = false;
			toggle_state = false;
			if (selection == i)
				button_state = true;
			if (chkbit(settings.byte, i))
				toggle_state = true;
			dbg_sprintf(dbgout, "chkbit = %d\ntoggle_state = %d\n", chkbit(settings.byte, i), toggle_state);
			draw_settings_button(setting_titles[i], button_state, chkbit(settings.byte, i), 50 + 36 * i);
		};
		
		gfx_BlitBuffer();
		
		delay(200);			// Slow down the button scrolling
		
		do {
			kb_Scan();
		} while (!kb_AnyKey());
		
		arrows = kb_Data[7];
		
		if ((arrows & kb_Down) && selection < 2)
			selection++;
		if ((arrows & kb_Up) && selection > 0)
			selection--;
		
		if ((kb_Data[6] & kb_Enter) || (kb_Data[1] & kb_2nd))
			settings.byte = setbit(settings.byte, selection);
		
		if (arrows & kb_Right)
			return 2;
		
		if ((kb_Data[1] & kb_Graph) || (kb_Data[6] & kb_Clear))
			return 255;
	};
}


uint8_t help_page(void) {
	
	draw_title("Help");
	gfx_PrintStringXY("Controls:", 40, 50);
	print_control("Arrows", "Navigation", 60);
	print_control("[2nd]/[Enter]", "Left-click", 70);
	print_control("[Clear]", "Exit program", 80);
	print_control("[Yequ]/[Graph]", "On-screen buttons", 90);
	print_control("[Mode]", "Pause exercise", 100);
	gfx_PrintStringXY("Input Controls:", 40, 120);
	print_control("[Del]", "Backspace", 130);
	print_control("[Clear]", "Delete input", 140);
	gfx_BlitBuffer();
	delay(200);
	
	for (;;) {
		do {
			kb_Scan();
		} while(!kb_AnyKey());
		
		if (kb_Data[7] & kb_Left)
			return 1;
		
		if (kb_Data[7] & kb_Right)
			return 3;
		
		if ((kb_Data[1] & kb_Graph) || (kb_Data[6] & kb_Clear))
			return 255;
	};

	/*
	Controls:
	
	Arrows			-	Navigation
	[2nd]/[Enter]	-	Left-click
	[Clear]			-	Exit program
	[Yequ]/[Graph]	-	On-screen buttons
	[Mode]			-	Pause exercise
	
	Input Controls:
	
	[Del]			-	Backspace
	[Clear]			-	Delete input
	[Enter]			-	Submit
	*/	
}


uint8_t about_page(void) {
	
	draw_title("About");
	
	print_centered("Mental Math CE", 40);
	gfx_PrintStringXY("Version:", 40, 60);
	gfx_PrintStringXY(PROGRAM_VERSION, 110, 60);
	gfx_PrintStringXY("Author:", 40, 70);
	gfx_PrintStringXY(PROGRAM_AUTHOR, 108, 70);
	
	print_centered("If you have any questions, feature", 90);
	print_centered("recommendations, or bug reports,", 100);
	print_centered("please go to www.cemetech.net and", 110);
	print_centered("make a post in the program's forum", 120);
	print_centered("thread. Any feedback will be very", 130);
	print_centered("much appreciated!", 140);
	
	print_centered("Thank you for downloading Mental", 155);
	print_centered("Math CE!", 165);
	gfx_BlitBuffer();
	delay(200);
	
	for (;;) {
		do {
			kb_Scan();
		} while (!kb_AnyKey());
		
		if (kb_Data[7] & kb_Left)
			return 2;
		
		if ((kb_Data[1] & kb_Graph) || (kb_Data[6] & kb_Clear))
			return 255;
	};
	/*
			Mental Math CE
			
	Version: program.version
	Author:  program.author
	
	If you have any questions, feature recommendations, or bug reports,
	please go to www.cemetech.net and make a post in the program's forum
	thread or PM the author.
	
	Any feedback will be very much appreciated!
	Thank you for downloading Mental Math CE!
	
	*/
}


void settings_menu(void) {
	
	uint8_t curr_page;
	
	kb_key_t key;
	bool key_Left, key_Right, key_Graph;
	
	curr_page = 1;
	
	for (;;) {
		
		dbg_sprintf(dbgout, "About to fill screen\n");
		gfx_FillScreen(BG_COLOR);
		page_indicator(3, curr_page);
		icon_button(back_icon, 283, 203);
		
		switch (curr_page) {
			
			case 1:
			curr_page = settings_page();
			break;
			
			case 2:
			curr_page = help_page();
			break;
			
			case 3:
			curr_page = about_page();
			break;
			
			default:
			return;
		};
	};
}