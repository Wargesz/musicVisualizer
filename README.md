# musicVisualizer

> [!IMPORTANT]
> this projects was made for an esp32 board with a screen with the arduino framework to show currently playing music track

### specs

- board: **ESP32-WROOM-32D**
- screen: **ST7796**
- touchscreen: **XPT2046**

This projects on its own is useless, the server for this projects is
located [here](https://github.com/wargesz/musicTracker).

On startup the device connects to wifi, and to the servers websocket.
requests the track details, and then writes them to the screen,
then draws the track's thumbnail the id of which is sent with the track's
params then requests it from youtube's site and draws it to screen as well.

At the bottom of the screen the current progress and track length is show
along with a progress bar to make it pretty.

On track change the server automatically tells it to update info, then the
board asks for the current progress so if the board was turned on midway it shows roughly accurate progress (~2 seconds).

# Some examples

## Rick Astley - Never Gonna Give You Up

![Rick Astley - Never Gonna Give You Up with white background](examples/rick.jpg)

## Darude - Sandstorm

![Darude - Sandstorm](examples/darude.jpg)
