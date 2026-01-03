#ifndef ARDUINOWIFI
#define ARDUINOWIFI

#include <WString.h>
#include <HTTPClient.h>

String request(const char *url);
void connectToWifi(const char* ssid, const char* pass);

#endif