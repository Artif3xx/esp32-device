/**
 * @author  Castox
 * @file    oled096.cpp
 * @brief   functions to display the collected contend
 */ 

#include "Screen.h"


/**
 * @brief Construct a new Screen::Screen object
 * 
 */
Screen::Screen() {
  // start with clear display
  // 180 degree rotation of the display
  Adafruit_SSD1306 init_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  this->display = &init_display;
  this->display->setRotation(2);
  this->display->clearDisplay();
  this->display->setTextSize(1);
  this->display->setTextColor(WHITE);
  this->display->setCursor(0, 0);
}

/**
 * @brief Destroy the Screen:: Screen object
 * 
 */
Screen::~Screen() {
  this->display->clearDisplay();
  this->display->display();
}

bool Screen::begin(void) {
  return this->display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

/**
 * @brief   set title of the displaied page and cursor to (0,10)
 * @param   const char[]
 */
void Screen::set_Title(const char title[]) {
  this->display->setCursor(0, 0);
  this->display->println(title);
  // draw a Line under the heading. One Pixel high
  this->display->drawFastHLine(0, 8, 128, SSD1306_WHITE);
  this->display->display();
}

void Screen::set_Title_Icon() {
  // content space 9x9 pixels at the top right corner 
}

void Screen::print_Content(const char content[]) {
  this->display->println(content);
  this->display->display();
}

void Screen::clear_Screen() {
  this->display->clearDisplay();
  
}

void Screen::draw_vertical_Line(int16_t x, int16_t y, int16_t h, uint16_t color) {
  this->display->drawFastVLine(x, y, h, color);
  this->display->display();
}

void Screen::draw_horizontal_Line(int16_t x, int16_t y, int16_t h, uint16_t color) {
  this->display->drawFastHLine(x, y, h, color);
}
