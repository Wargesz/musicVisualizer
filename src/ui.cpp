#include <stdint.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <ui.hpp>
#include "wifi.hpp"
#include <TJpg_Decoder.h>

TFT_eSPI tft;

void button(int32_t x, int32_t y, uint32_t clr, const char* content) {
  auto height = 30;
  auto width = tft.textWidth(content) + 20;
  tft.drawRect(x, y, width, height, clr);
  tft.drawString(content, x, y);
}

void drawJpegFromRequest(const char* url) {
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    WiFiClient* stream = http.getStreamPtr();
    uint8_t* data = (uint8_t*) malloc(sizeof(uint8_t) * http.getSize());
    if (data == nullptr) {
      Serial.println("malloc failed");
      return;
    }
    stream->readBytes(data, http.getSize());
    TJpgDec.drawJpg(-60, 10, data, http.getSize());
    free(data);
  } else {
    Serial.printf("HTTP failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void drawJpegFromId(const char* url) {
  String s = String("https://i3.ytimg.com/vi/");
  s.concat(url);
  s += "/mqdefault.jpg";
  drawJpegFromRequest(s.c_str());
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  if (y >= tft.height()) {
    return 0;
  }
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}