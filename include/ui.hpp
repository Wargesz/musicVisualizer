#ifndef ARDUINOUI
#define ARDUINOUI
#include <stdint.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void button(int32_t x, int32_t y, uint32_t clr, const char* content);
void drawJpegFromRequest(const char* url);
void drawJpegFromId(const char* url);
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap);

#endif