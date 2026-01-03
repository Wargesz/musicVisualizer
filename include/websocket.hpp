#ifndef ARDUINOWEBSOCKET
#define ARDUINOWEBSOCKET

#include <WiFi.h>
#include <WebSocketsClient.h>

extern WebSocketsClient webSocket;

void setupWebSocket();
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
void handleMsg(char*);
void handleMsgTrack(char*);
bool startsWith(char*, char*);

#endif