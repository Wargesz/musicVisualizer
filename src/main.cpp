#include "main.hpp"
#include "secrets.hpp"
#include "ui.hpp"
#include "wifi.hpp"
#include "websocket.hpp"
#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WString.h>
#include <TJpg_Decoder.h>

XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_INTERRUPT);
uint16_t x = 0;
uint16_t y = 0;
int stringPos;
Track t;
unsigned long previousMillis = 0;
const long interval = 1000;
bool isReady = false;

void setup() {
  SPI.begin(TOUCH_CLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS);
  Serial.begin(BAUD_RATE);
  Serial.println("Ready");
  ts.begin();
  ts.setRotation(1);
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.setFreeFont(&FreeMono9pt7b);
  tft.setTextSize(1);
  clear();
  TJpgDec.setCallback(tft_output);
  TJpgDec.setJpgScale(1);
  connectToWifi(MYSSID, MYPASS);
  setupWebSocket();
  webSocket.loop();
}

void loop() {
  webSocket.loop();
  unsigned long currentMillis = millis();
  if (isReady && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    tick();
  }
}

void coords() {
  TS_Point p = ts.getPoint();
  x = p.x >> 3;
  y = p.y >> 3;
}

void draw() {
  tft.fillRect(0, 0, 10, 200, BACKGROUND);
  tft.fillRect(190, 0, 100, 200, BACKGROUND);
  tft.fillRoundRect(70, tft.height() - 40, tft.width()- 2*70, 10, 3, TFT_DARKGREY);
  stringPos = 2;
  drawString(t.title);
  drawString(t.album);
  drawString(t.artist);
  drawTime(t.progress, 10, 40);
  drawTime(t.length, tft.width() - 60, 40);
}

void clear() {
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, BACKGROUND);
}

void updateTrack() {
  //request(trackinfo)
}

void drawString(String s) {
  if (s.length() > 24) {
    s[s.lastIndexOf(' ')] = '\n';
    String pre = s.substring(0, s.indexOf('\n'));
    String after = s.substring(s.indexOf('\n') + 1);
    tft.drawString(pre, 350 - tft.textWidth(pre)/2, TEXT_OFFSET*stringPos++);
    tft.drawString(after, 350 - tft.textWidth(after)/2, TEXT_OFFSET*stringPos++);
  } else {
    tft.drawString(s, 350 - tft.textWidth(s)/2, TEXT_OFFSET*stringPos++);
  }
}

void drawTime(int value, int x, int y) {
  int m = value/60;
  int s = value%60;
  tft.drawString(leadingZero(m) + ":" + leadingZero(s), x, tft.height() - y);
}

String leadingZero(int i) {
  String s = "0";
  s += i;
  return i < 10 ? s : String(i);
}

void tick() {
  t.progress++;
  drawTime(t.progress, 10, 40);
  int width = tft.width() - 2*70;
  float progress = (float) t.progress / t.length;
  int32_t w = progress * width;
  tft.fillRoundRect(70, tft.height() - 40, w, 10, 3, TFT_RED);
}