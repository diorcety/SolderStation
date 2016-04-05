#include "config.h"
#include "lcd.h"
#include "utils.h"
#include "lang.h"

#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "solder_station.h"

#ifdef LCD_ST7735_MODULE

#define FONT_WIDTH 6
#define FONT_HEIGHT 8
#define MENU_ITEM_BG ST7735_WHITE 
#define MENU_ITEM_FG ST7735_BLACK
#define MENU_ITEM_SELECTED_BG ST7735_BLACK
#define MENU_ITEM_SELECTED_FG ST7735_WHITE

#ifndef LCD_ST7735_DC
#error Missing configuration of LCD_ST7735_DC
#endif //LCD_ST7735_DC

#ifndef LCD_ST7735_CS
#error Missing configuration of LCD_ST7735_CS
#endif //LCD_ST7735_CS

#ifndef LCD_ST7735_RESET
#error Missing configuration of LCDST7735_RESET
#endif //LCD_ST7735_RESET

#ifndef LCD_ST7735_BL
#error Missing configuration of LCD_ST7735_BL
#endif //LCD_ST7735_BL

static Adafruit_ST7735 display = Adafruit_ST7735(LCD_ST7735_CS, LCD_ST7735_DC, LCD_ST7735_RESET);
static uint16_t MENU_HEADER_BG = display.Color565(80,80,230);
static uint16_t MENU_HEADER_FG = display.Color565(255,255,255);

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
  DEBUG_LOG_LN(DEBUG_STR("Init LCD ST7735"));
  display.initR(INITR_BLACKTAB);
  display.setRotation(3);
  display.fillScreen(ST7735_WHITE);
  display.setTextWrap(false);
  
  // Switch off the Backlight
  digitalWrite(LCD_ST7735_BL, LOW); 
  pinMode(LCD_ST7735_BL, OUTPUT);
}

/*
 * Enable/Disable backlight
 */
void lcd_set_backlight(boolean enable) {
  digitalWrite(LCD_ST7735_BL, enable); 
}

/*
 * Clear lcd
 */
void lcd_clear() {
  display.fillScreen(ST7735_WHITE);
}

/*
 * Print heat signal
 */
void lcd_print_heat(byte pwm) {
#define LCD_FONT_SIZE 2
  display.setTextSize(LCD_FONT_SIZE);
  display.setTextColor(ST7735_BLACK, ST7735_WHITE);
  display.setCursor(1, 1);
  const char* str = my_sprintf("%3d%%", (byte)(((float)pwm) * 100.0f / 255.0f));
  display.print(str);
#undef LCD_FONT_SIZE
}

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature) {
#define LCD_FONT_SIZE 8
  display.setTextSize(LCD_FONT_SIZE);
  center_for_text(30, 3, LCD_FONT_SIZE);
  display.setTextColor(ST7735_BLACK, ST7735_WHITE);
  __lcd_print_temperature(temperature);
#undef LCD_FONT_SIZE
}

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature) {
#define LCD_FONT_SIZE 2
  display.setTextSize(LCD_FONT_SIZE);
  right_for_text(1, 3, LCD_FONT_SIZE);
  display.setTextColor(ST7735_BLACK, ST7735_WHITE);
  __lcd_print_temperature(temperature);
#undef LCD_FONT_SIZE
}

/*
 * Print standby temperature
 */
void lcd_print_standby_temperature(int temperature) {
#define LCD_FONT_SIZE 2
  display.setTextSize(LCD_FONT_SIZE);
  right_for_text(1, 3, LCD_FONT_SIZE);
  display.setTextColor(ST7735_WHITE, ST7735_BLACK);
  __lcd_print_temperature(temperature);
#undef LCD_FONT_SIZE
}

/*
 * Print temperature unit
 */
void lcd_print_temperature_unit() {
#define LCD_FONT_SIZE 2
  display.setTextSize(LCD_FONT_SIZE);
  center_for_text(1, 2, LCD_FONT_SIZE);
  __lcd_print_temperature_unit();
#undef LCD_FONT_SIZE
}

/*
 * Print fault
 */
void lcd_print_fault() {
#define LCD_FONT_SIZE 4
  const char *msg = GET_TEXT(TT(T_FAULT));
  display.setTextSize(LCD_FONT_SIZE);
  center_for_text((display.height()-FONT_HEIGHT*LCD_FONT_SIZE)/2, strlen(msg), LCD_FONT_SIZE);
  display.print(msg);
#undef LCD_FONT_SIZE
}

/*
 * Print title
 */
void lcd_print_title(const char *title) {
#define LCD_FONT_SIZE 2
    display.setTextSize(LCD_FONT_SIZE);
    display.fillRect(0, 0, display.width(), (FONT_HEIGHT * LCD_FONT_SIZE), MENU_HEADER_BG);
    display.setTextColor(MENU_HEADER_FG, MENU_HEADER_BG);
    center_for_text(1, strlen(title), LCD_FONT_SIZE);
    display.print(title);
    display.drawLine(0, FONT_HEIGHT * LCD_FONT_SIZE, display.width(), FONT_HEIGHT * LCD_FONT_SIZE, ST7735_BLACK);
#undef LCD_FONT_SIZE
}

/*
 * Print item
 */
void lcd_print_item(byte line, const char *item, const char *value, item_state state) {
#define LCD_FONT_SIZE 2
    int y = ((FONT_HEIGHT * LCD_FONT_SIZE + 2) * line);
    int c;
    int bg;
    if(state == ITEM_SELECTED) {
      c = MENU_ITEM_SELECTED_FG;
      bg = MENU_ITEM_SELECTED_BG;
    } else {
      c = MENU_ITEM_FG;
      bg = MENU_ITEM_BG;
    }
    display.fillRect(0, (FONT_HEIGHT * LCD_FONT_SIZE + 1) + y, display.width(), (FONT_HEIGHT * LCD_FONT_SIZE + 2), bg);
    if(item != NULL) {
      display.setTextSize(1);
      display.setTextColor(c, bg);
      display.setCursor(0, (FONT_HEIGHT * LCD_FONT_SIZE + 2) + FONT_HEIGHT / 2 + y);
      display.print(item);
    }

    if(value != NULL) {
      if(state == ITEM_EDITION || state == ITEM_SELECTED) {
         c = ST7735_WHITE;
         bg = ST7735_BLACK;
      } else {
         c = ST7735_BLACK;
        bg = ST7735_WHITE;
      }
      display.setTextSize(LCD_FONT_SIZE);
      display.setTextColor(c, bg);
      right_for_text((FONT_HEIGHT * LCD_FONT_SIZE + 2) + y, strlen(value), LCD_FONT_SIZE);
      display.print(value);
    }
#undef LCD_FONT_SIZE
}

byte lcd_item_count() {
  return 6;
}

/*
 * Display on the lcd
 */
void lcd_display() {
    //display.display();
}

#endif //LCD_ST7735_MODULE

