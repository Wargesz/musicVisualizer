#include <WiFi.h>
#include <HTTPClient.h>

void connectToWifi(const char* ssid, const char* pass) {
  Serial.print("Connecting to Wifi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

String request(const char *url) {
  if (WiFi.status() != WL_CONNECTED) {
    return "not connected";
  }
  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.begin(url);
  int code = http.GET();
  if (code == 0) {
    return "error";
  }
  String response = http.getString();
  http.end();
  return response;
}