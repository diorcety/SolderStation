#include "lcd.h"
#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define CS 10
#define DC 9
#define RESET 8
#define BL  2
#define DEGREE_SYM "\xF8"

Adafruit_PCD8544 display = Adafruit_PCD8544(DC, CS, RESET);

/*
 * Print a temperature
 */
static void __lcd_print_temperature(int temperature) {
  if(temperature<10) {
    display.print(' ');
  }
  if(temperature<100) {
    display.print(' ');
  }
  display.print(temperature);
  display.print(DEGREE_SYM"C");
}


/*
 * Init LCD stuff
 */
void lcd_init() {
  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  
  // Switch of the Backlight
  digitalWrite(BL, LOW); 
  pinMode(BL, OUTPUT);
}

/*
 * Enable/Disable backlight
 */
void lcd_set_backlight(boolean enable) {
  digitalWrite(BL, enable); 
}

/*
 * Get backlight status
 */
boolean lcd_get_backlight() {
  return digitalRead(BL);
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
  display.setCursor(20, 34);
  display.setTextColor(BLACK, WHITE);
  display.print(show? "****" : "    ");
  display.display();
}

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature) {
  display.setTextSize(2);
  display.setCursor(15, 18);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
  display.display();
}

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature) {
  display.setTextSize(1);
  display.setCursor(54, 0);
  display.setTextColor(BLACK, WHITE);
  __lcd_print_temperature(temperature);
  display.display();
}

/*
 * Print title
 */
void lcd_print_title(String title) {
    display.setTextSize(1);
    display.setCursor(54, 0);
    display.setTextColor(BLACK, WHITE);
    display.print(title);
    display.display();
}

