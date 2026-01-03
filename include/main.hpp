#ifndef ARDUINOUTILS
#define ARDUINOUTILS

#include <WString.h>

#define LCD_BACKLIGHT GPIO_NUM_27
#define TOUCH_INTERRUPT GPIO_NUM_36
#define TOUCH_MISO GPIO_NUM_12
#define TOUCH_MOSI GPIO_NUM_13
#define TOUCH_CLK GPIO_NUM_14
#define BAUD_RATE 115200
#define BACKGROUND TFT_BLACK
#define TEXT_OFFSET 25

class Track {
    public:
        String title;
        String artist;
        String album;
        String id;
        int length;
        int progress;
};

extern Track t;
extern bool isReady;

void coords();
void draw();
void clear();
void updateTrack();
void drawString(String);
void drawTime(int value, int x, int y);
String leadingZero(int);
void tick();

#endif