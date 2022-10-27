#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include <SoftwareSerial.h>
// credentials example file inside includes directory
#include "secrets.h"

const char *WIFI_SSID = ssid_name;
const char *WIFI_PASS = ssid_password;

// device name
#define ID_SMART "SmartDisplay"

fauxmoESP fauxmo;

// wemos -> rs232 pins
const int rx = 12;
const int tx = 13;

// smartdisplay rs232 commands
const byte SMART_ON[] = {0x35, 0x62, 0x30, 0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x31, 0x0D};
const byte SMART_OFF[] = {0x35, 0x62, 0x30, 0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0D};

SoftwareSerial rs232(rx, tx);

void wifiSetup()
{
  Serial.println("WIFI Setup started");

  WiFi.mode(WIFI_STA);

  Serial.printf("Connecting: %s ", WIFI_SSID);
  Serial.println("");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("*");
    delay(1000);
  }
  Serial.println("");
  Serial.println("WIFI Setup finished");
  Serial.printf("Connected to: %s\n, IP: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}

void deviceSetup()
{

  Serial.println("Device Setup started");

  fauxmo.addDevice(ID_SMART);

  fauxmo.setPort(80);

  fauxmo.enable(true);

  fauxmo.onSetState([](unsigned char device_id, const char *device_name, bool state, unsigned char value)
                    {
         
                        Serial.printf("State changed\nId: %d\nName: %s\nState: %s\nValue: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

                        // more devices will be added in the future
                        if (state)
                         {
                           if (strcmp(device_name, ID_SMART) == 0)
                           {
                             rs232.write(SMART_ON, sizeof(SMART_ON));
                           }
                         }
                         else
                         {
                           if (strcmp(device_name, ID_SMART) == 0)
                           {
                             rs232.write(SMART_OFF, sizeof(SMART_OFF));
                           }
                         } });

  Serial.println("Device Setup finished");
}

void setup()
{
  // wemos
  Serial.begin(57600);

  // smart board
  rs232.begin(9600);

  delay(10000);

  Serial.println("Configuration started");

  wifiSetup();
  deviceSetup();

  Serial.println("Configuration finished");
}

void loop()
{
  fauxmo.handle();
}