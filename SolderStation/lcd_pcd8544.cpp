#include "config.h"
#include "lcd.h"
#include "utils.h"
#include "lang.h"

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
#endif //LCD_PCD8544_DC

#ifndef LCD_PCD8544_CS
#error Missing configuration of LCD_PCD8544_CS
#endif //LCD_PCD8544_CS

#ifndef LCD_PCD8544_RESET
#error Missing configuration of LCD_PCD8544_RESET
#endif //LCD_PCD8544_RESET

#ifndef LCD_PCD8544_BL
#error Missing configuration of LCD_PCD8544_BL
#endif //LCD_PCD8544_BL

static Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_PCD8544_DC, LCD_PCD8544_CS, LCD_PCD8544_RESET);

/*
 * Print a temperature
 */
static void __lcd_print_temperature(int temperature) {
  if(get_temperature_unit() == TEMP_FAHRENHEIT) {
      temperature = (float)temperature * 1.8f + 32.0f;
  }
  
  if(temperature<10) {
    display.print(' ');
  }
  if(temperature<100) {
    display.print(' ');
  }

  display.print(temperature);
}

static void __lcd_print_temperature_unit() {
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

static void center_for_text(uint16_t y, int len, byte size) {
  display.setCursor((display.width() - (FONT_WIDTH * size * len))/2, y);
}

static void right_for_text(uint16_t y, int len, byte size) {
  display.setCursor((display.width() - (FONT_WIDTH * size * len)), y);
}

/*
 * Init LCD stuff
 */
void lcd_init() {
  DEBUG_LOG_LN(DEBUG_STR("Init LCD PCD8544"));
  display.begin();
#ifdef LCD_MODULE_CONTRAST
  display.setContrast(30);
#endif //LCD_MODULE_CONTRAST
  display.clearDisplay();
  
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

#ifdef LCD_MODULE_CONTRAST
/*
 * Set contrast
 */
void lcd_set_contrast(byte contrast) {
  display.setContrast((byte)(((float)contrast) * 128.0f / 100.0f));
}
#endif //#ifdef LCD_MODULE_CONTRAST

/*
 * Clear lcd
 */
void lcd_clear() {
  display.fillScreen(WHITE);
}

/*
 * Print heat signal
 */
void lcd_print_heat(byte pwm) {
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0, 0);
  const char* str = my_sprintf("%3d%%", (byte)(((float)pwm) * 100.0f / 255.0f));
  display.print(str);
}

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature) {
  display.setTextSize(4);
  center_for_text(10, 3, 4);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
}

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature) {
  display.setTextSize(1);
  right_for_text(0, 3, 1);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
}

/*
 * Print standby temperature
 */
void lcd_print_standby_temperature(int temperature) {
  display.setTextSize(1);
  right_for_text(0, 3, 1);
  display.setTextColor(WHITE, BLACK);
  __lcd_print_temperature(temperature);
}

/*
 * Print temperature unit
 */
void lcd_print_temperature_unit() {
  display.setTextSize(1);
  center_for_text(0, 2, 1);
  __lcd_print_temperature_unit();
}

/*
 * Print fault
 */
void lcd_print_fault() {
  const char *msg = GET_TEXT(TT(T_FAULT));
  display.setTextSize(2);
  center_for_text((display.height()-FONT_HEIGHT*2)/2, strlen(msg), 2);
  display.print(msg);
}

/*
 * Print title
 */
void lcd_print_title(const char *title) {
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    center_for_text(0, strlen(title), 1);
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
      right_for_text((FONT_HEIGHT + 2) + y, strlen(value), 1);
      display.print(value);
    }
}

byte lcd_item_count() {
  return 4;
}

/*
 * Display on the lcd
 */
void lcd_display() {
    display.display();
}

#endif //LCD_PCD8544_MODULE

