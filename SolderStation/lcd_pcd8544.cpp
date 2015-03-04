#include "config.h"
#include "lcd.h"
#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "solder_station.h"

#ifdef LCD_PCD8544_MODULE

#define FONT_WIDTH 6
#define FONT_HEIGHT 8

#ifndef LCD_PCD8544_DC
#error Missing configuration of LCD_PCD8544_DC
#endif

#ifndef LCD_PCD8544_CS
#error Missing configuration of LCD_PCD8544_CS
#endif

#ifndef LCD_PCD8544_RESET
#error Missing configuration of LCD_PCD8544_RESET
#endif

#ifndef LCD_PCD8544_BL
#error Missing configuration of LCD_PCD8544_BL
#endif

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_PCD8544_DC, LCD_PCD8544_CS, LCD_PCD8544_RESET);

/*
 * Print a temperature
 */
static void __lcd_print_temperature(int temperature) {
  switch(get_temperature_unit()) {
    case TEMP_FAHRENHEIT:
      temperature = (float)temperature * 1.8f + 32.0f;
      break;
  }
  
  if(temperature<10) {
    display.print(' ');
  }
  if(temperature<100) {
    display.print(' ');
  }
  display.print(temperature);
  switch(get_temperature_unit()) {
    case TEMP_FAHRENHEIT:
      display.print(DEGREE_SYM"F");
      break;
    case TEMP_CELSIUS:
    default:
      display.print(DEGREE_SYM"C");
      break;
  }
}


static void center_for_text(uint16_t y, const char *text, byte size) {
  int len = strlen(text);
  display.setCursor((display.width() - (FONT_WIDTH * size * len))/2, y);
}

static void right_for_text(uint16_t y, const char *text, byte size) {
  int len = strlen(text);
  display.setCursor((display.width() - (FONT_WIDTH * size * len)), y);
}

/*
 * Init LCD stuff
 */
void lcd_init() {
  display.begin();
  display.setContrast(30);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  
  // Switch off the Backlight
  digitalWrite(LCD_PCD8544_BL, LOW); 
  pinMode(LCD_PCD8544_BL, OUTPUT);
}

/*
 * Enable/Disable backlight
 */
void lcd_set_backlight(boolean enable) {
  digitalWrite(LCD_PCD8544_BL, enable); 
}

/*
 * Set contrast
 */
void lcd_set_contrast(byte contrast) {
  display.setContrast((byte)(((float)contrast) * 128.0f / 100.0f));
}

/*
 * Clear lcd
 */
void lcd_clear() {
  display.fillScreen(WHITE);
}

/*
 * Print heat signal
 */
void lcd_print_heat(boolean show) {
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);
  const char* str = show? "****" : "    ";
  center_for_text(34, str, 2);
  display.print(str);
}

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature) {
  display.setTextSize(2);
  display.setCursor(15, 18);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
}

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature) {
  display.setTextSize(1);
  display.setCursor(54, 0);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
}

/*
 * Print target temperature
 */
void lcd_print_standby_temperature(int temperature) {
  display.setTextSize(1);
  display.setCursor(54, 0);
  display.setTextColor(WHITE, BLACK);
  __lcd_print_temperature(temperature);
}

/*
 * Print title
 */
void lcd_print_title(const char *title) {
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    center_for_text(0, title, 1);
    display.print(title);
    display.drawLine(0, FONT_HEIGHT, display.width(), FONT_HEIGHT, BLACK);
}

/*
 * Print item
 */
void lcd_print_item(byte line, const char *item, const char *value, item_state state) {
    display.setTextSize(1);
    byte y = ((FONT_HEIGHT + 2) * line);
    byte c;
    byte bg;
    if(state == ITEM_SELECTED) {
      c = WHITE;
      bg = BLACK;
    } else {
      c = BLACK;
      bg = WHITE;
    }
    display.fillRect(0, (FONT_HEIGHT + 1) + y, display.width(), FONT_HEIGHT + 2, bg);
    if(item != NULL) {
      display.setTextColor(c, bg);
      display.setCursor(0, (FONT_HEIGHT + 2) + y);
      display.print(item);
    }
    if(value != NULL) {
      if(state == ITEM_EDITION || state == ITEM_SELECTED) {
         c = WHITE;
         bg = BLACK;
      } else {
         c = BLACK;
        bg = WHITE;
      }
      display.setTextColor(c, bg);
      right_for_text((FONT_HEIGHT + 2) + y, value, 1);
      display.print(value);
    }
}

/*
 * Display on the lcd
 */
void lcd_display() {
    display.display();
}

#endif //LCD_PCD8544_MODULE

