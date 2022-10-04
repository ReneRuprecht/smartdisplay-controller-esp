# smartdisplay-controller-esp
Esp8266 Wemos D1 mini controlling a smart display over rs232 with alexa

## Hardware used:
- Wemos D1 Mini
- MAX3232 for RS232 communication
- Smart display
- Alexa

## Wiring
Wemos <-> MAX3232<br/>
3.3v to 3.3V<br/>
TX to RX<br/>
RX to TX<br/>
GND to GND<br/>

## Setup
- Rename the secrets.example.h to secrets.h inside the include folder
- Replace the ssid and the password inside the secrets.h
- Change the source code to your liking
- Compile and upload
