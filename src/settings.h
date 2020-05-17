#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>

#include <keypadc.h>

#define SETTINGS_AUTO_CHECK (settings.byte & 1)
#define SETTINGS_TIMER (settings.byte & 2)

/* Structure of settings.byte:

+-----+-----+-----+-----+-----+-----+-------+------------+
| ??? | ??? | ??? | ??? | ??? | ??? | timer | auto_check |
+-----+-----+-----+-----+-----+-----+-------+------------+
*/

typedef struct {
	uint8_t byte;
} settings_t;

extern settings_t settings;

void print_control(const char *key, const char *action, uint8_t yPos);
bool chkbit(uint8_t byte, uint8_t pos);
uint8_t setbit(uint8_t byte, uint8_t pos);
void toggle(bool state, uint24_t xPos, uint8_t yPos, uint24_t width);
void draw_settings_button(char *title, bool button_state, bool toggle_state, uint8_t yPos);
uint8_t settings_page(void);
uint8_t help_page(void);
uint8_t about_page(void);

void settings_menu(void);

#endif