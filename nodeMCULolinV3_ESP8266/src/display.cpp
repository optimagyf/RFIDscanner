#include <Arduino.h>
#include "pinLayout.h"
#include "display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_ADDRESS 0x3C
// Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_RESET -1

#define SDA_PIN PIN_D4
#define SCL_PIN PIN_D3

// Externalised variable
Adafruit_SSD1306 *display = NULL;
TwoWire *wire = NULL;

ulong displayTimeout = 0;
ulong displayDuration = 3000;
String messageToPrint;
bool hasPrintMessage = false;
// <----- Externalised variable

bool isClean = false;

ulong currentMillis;

// *** Initialise the screen
void initScreen()
{
  // TwoWire wire;
  // Set pins for I2C communication
  wire = new TwoWire();
  wire->begin(SDA_PIN, SCL_PIN);
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, wire, OLED_RESET);

  if (!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
}

void displayMessage()
{
  currentMillis = millis();

  if ((displayTimeout <= currentMillis) && (currentMillis < displayTimeout + displayDuration))
  {
    if (!hasPrintMessage)
    {
      display->clearDisplay();

      display->setTextSize(2);              // Draw 2X-scale
      display->setTextColor(SSD1306_WHITE); // Draw white text
      display->setCursor(0, 0);             // Start at top-left corner
      // display->println(F("Interrupt 1"));
      display->println(messageToPrint.c_str());

      display->display();
      isClean = false;
      hasPrintMessage = true;
    }
  }
  else
  {
    if (!isClean)
    {
      display->clearDisplay();
      display->display();
      isClean = true;
      hasPrintMessage = false;
    }
  }
}