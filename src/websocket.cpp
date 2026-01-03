#include <WiFi.h>
#include <WebSocketsClient.h>
#include "websocket.hpp"
#include "main.hpp"
#include "secrets.hpp"
#include "ui.hpp"

WebSocketsClient webSocket;

void setupWebSocket() {
  webSocket.begin(WEBSOCKET_IP, WEBSOCKET_PORT, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("[WSc] Disconnected!");
      break;
    case WStype_CONNECTED:
      Serial.println("[WSc] Connected to url: " + String((char *)payload));
      // Send message to server once connected
      webSocket.sendTXT("!id:Monitor");
      webSocket.sendTXT("?track");
      break;
    case WStype_TEXT:
      handleMsg((char*)payload);
      break;
  }
}

void handleMsg(char* msg) {
  if (startsWith(msg, (char*) "noop")) {
    return;
  }
  if (startsWith(msg, (char*) "!track")) {
    handleMsgTrack(msg);
    return;
  }

  if (startsWith(msg, (char*) "!time")) {
    String m = String(msg);
    t.progress = m.substring(6).toInt();
  }
}

bool startsWith(char* a, char* b) {
  while (*b != '\0') {
    if (*a != *b) {
      return false;
    }
    a++;
    b++;
  }
  return true;
}

void handleMsgTrack(char *msg) {
  msg += 7;
  String s[5];
  Track newTrack;
  char *token = strtok(msg, "|");
  int i = 0;
  while (token != NULL)
  {
    s[i] = String(token);
    token = strtok(NULL, "|");
    i++;
  }
  newTrack.title = s[0];
  newTrack.artist = s[1];
  newTrack.album = s[2];
  newTrack.id = s[3];
  newTrack.length = s[4].toInt();
  newTrack.progress = 0;
  t = newTrack;
  isReady = true;
  webSocket.sendTXT("?time");
  clear();
  drawJpegFromId(t.id.c_str());
  draw();
}