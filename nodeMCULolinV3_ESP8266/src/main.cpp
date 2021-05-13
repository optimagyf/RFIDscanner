// /**************************************************************************
//  This is an example for our Monochrome OLEDs based on SSD1306 drivers

//  Pick one up today in the adafruit shop!
//  ------> http://www.adafruit.com/category/63_98

//  This example is for a 128x64 pixel display using I2C to communicate
//  3 pins are required to interface (two I2C and one reset).

//  Adafruit invests time and resources providing this open
//  source code, please support Adafruit and open-source
//  hardware by purchasing products from Adafruit!

//  Written by Limor Fried/Ladyada for Adafruit Industries,
//  with contributions from the open source community.
//  BSD license, check license.txt for more information
//  All text above, and the splash screen below must be
//  included in any redistribution.
//  **************************************************************************/

// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <Adafruit_I2CDevice.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// // The pins for I2C are defined by the Wire-library.
// // On an arduino UNO:       A4(SDA), A5(SCL)
// // On an arduino MEGA 2560: 20(SDA), 21(SCL)
// // On an arduino LEONARDO:   2(SDA),  3(SCL), ...
// #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// #define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// #define NUMFLAKES 10 // Number of snowflakes in the animation example

// #define LOGO_HEIGHT 16
// #define LOGO_WIDTH 16
// static const unsigned char PROGMEM logo_bmp[] =
//     {B00000000, B11000000,
//      B00000001, B11000000,
//      B00000001, B11000000,
//      B00000011, B11100000,
//      B11110011, B11100000,
//      B11111110, B11111000,
//      B01111110, B11111111,
//      B00110011, B10011111,
//      B00011111, B11111100,
//      B00001101, B01110000,
//      B00011011, B10100000,
//      B00111111, B11100000,
//      B00111111, B11110000,
//      B01111100, B11110000,
//      B01110000, B01110000,
//      B00000000, B00110000};

// void testdrawline()
// {
//   int16_t i;

//   display.clearDisplay(); // Clear display buffer

//   for (i = 0; i < display.width(); i += 4)
//   {
//     display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
//     display.display(); // Update screen with each newly-drawn line
//     delay(1);
//   }
//   for (i = 0; i < display.height(); i += 4)
//   {
//     display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for (i = 0; i < display.width(); i += 4)
//   {
//     display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for (i = display.height() - 1; i >= 0; i -= 4)
//   {
//     display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for (i = display.width() - 1; i >= 0; i -= 4)
//   {
//     display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for (i = display.height() - 1; i >= 0; i -= 4)
//   {
//     display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for (i = 0; i < display.height(); i += 4)
//   {
//     display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for (i = 0; i < display.width(); i += 4)
//   {
//     display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }

//   delay(2000); // Pause for 2 seconds
// }

// void testdrawrect(void)
// {
//   display.clearDisplay();

//   for (int16_t i = 0; i < display.height() / 2; i += 2)
//   {
//     display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
//     display.display(); // Update screen with each newly-drawn rectangle
//     delay(1);
//   }

//   delay(2000);
// }

// void testfillrect(void)
// {
//   display.clearDisplay();

//   for (int16_t i = 0; i < display.height() / 2; i += 3)
//   {
//     // The INVERSE color is used so rectangles alternate white/black
//     display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, SSD1306_INVERSE);
//     display.display(); // Update screen with each newly-drawn rectangle
//     delay(1);
//   }

//   delay(2000);
// }

// void testdrawcircle(void)
// {
//   display.clearDisplay();

//   for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2)
//   {
//     display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }

//   delay(2000);
// }

// void testfillcircle(void)
// {
//   display.clearDisplay();

//   for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3)
//   {
//     // The INVERSE color is used so circles alternate white/black
//     display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
//     display.display(); // Update screen with each newly-drawn circle
//     delay(1);
//   }

//   delay(2000);
// }

// void testdrawroundrect(void)
// {
//   display.clearDisplay();

//   for (int16_t i = 0; i < display.height() / 2 - 2; i += 2)
//   {
//     display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
//                           display.height() / 4, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }

//   delay(2000);
// }

// void testfillroundrect(void)
// {
//   display.clearDisplay();

//   for (int16_t i = 0; i < display.height() / 2 - 2; i += 2)
//   {
//     // The INVERSE color is used so round-rects alternate white/black
//     display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
//                           display.height() / 4, SSD1306_INVERSE);
//     display.display();
//     delay(1);
//   }

//   delay(2000);
// }

// void testdrawtriangle(void)
// {
//   display.clearDisplay();

//   for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 5)
//   {
//     display.drawTriangle(
//         display.width() / 2, display.height() / 2 - i,
//         display.width() / 2 - i, display.height() / 2 + i,
//         display.width() / 2 + i, display.height() / 2 + i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }

//   delay(2000);
// }

// void testfilltriangle(void)
// {
//   display.clearDisplay();

//   for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 5)
//   {
//     // The INVERSE color is used so triangles alternate white/black
//     display.fillTriangle(
//         display.width() / 2, display.height() / 2 - i,
//         display.width() / 2 - i, display.height() / 2 + i,
//         display.width() / 2 + i, display.height() / 2 + i, SSD1306_INVERSE);
//     display.display();
//     delay(1);
//   }

//   delay(2000);
// }

// void testdrawchar(void)
// {
//   display.clearDisplay();

//   display.setTextSize(1);              // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE); // Draw white text
//   display.setCursor(0, 0);             // Start at top-left corner
//   display.cp437(true);                 // Use full 256 char 'Code Page 437' font

//   // Not all the characters will fit on the display. This is normal.
//   // Library will draw what it can and the rest will be clipped.
//   for (int16_t i = 0; i < 256; i++)
//   {
//     if (i == '\n')
//       display.write(' ');
//     else
//       display.write(i);
//   }

//   display.display();
//   delay(20000);
// }

// void testdrawstyles(void)
// {
//   display.clearDisplay();

//   display.setTextSize(1);              // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE); // Draw white text
//   display.setCursor(0, 0);             // Start at top-left corner
//   display.println(F("Hello, world!"));

//   display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
//   display.println(3.141592);

//   display.setTextSize(2); // Draw 2X-scale text
//   display.setTextColor(SSD1306_WHITE);
//   display.print(F("0x"));
//   display.println(0xDEADBEEF, HEX);

//   display.display();
//   delay(20000);
// }

// void testscrolltext(void)
// {
//   display.clearDisplay();

//   display.setTextSize(2); // Draw 2X-scale text
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(10, 0);
//   display.println(F("scroll"));
//   display.display(); // Show initial text
//   delay(100);

//   // Scroll in various directions, pausing in-between:
//   display.startscrollright(0x00, 0x0F);
//   delay(2000);
//   display.stopscroll();
//   delay(1000);
//   display.startscrollleft(0x00, 0x0F);
//   delay(2000);
//   display.stopscroll();
//   delay(1000);
//   display.startscrolldiagright(0x00, 0x07);
//   delay(2000);
//   display.startscrolldiagleft(0x00, 0x07);
//   delay(2000);
//   display.stopscroll();
//   delay(10000);
// }

// void testdrawbitmap(void)
// {
//   display.clearDisplay();

//   display.drawBitmap(
//       (display.width() - LOGO_WIDTH) / 2,
//       (display.height() - LOGO_HEIGHT) / 2,
//       logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
//   display.display();
//   delay(10000);
// }

// #define XPOS 0 // Indexes into the 'icons' array in function below
// #define YPOS 1
// #define DELTAY 2

// void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h)
// {
//   int8_t f, icons[NUMFLAKES][3];

//   // Initialize 'snowflake' positions
//   for (f = 0; f < NUMFLAKES; f++)
//   {
//     icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
//     icons[f][YPOS] = -LOGO_HEIGHT;
//     icons[f][DELTAY] = random(1, 6);
//     Serial.print(F("x: "));
//     Serial.print(icons[f][XPOS], DEC);
//     Serial.print(F(" y: "));
//     Serial.print(icons[f][YPOS], DEC);
//     Serial.print(F(" dy: "));
//     Serial.println(icons[f][DELTAY], DEC);
//   }

//   for (;;)
//   {                         // Loop forever...
//     display.clearDisplay(); // Clear the display buffer

//     // Draw each snowflake:
//     for (f = 0; f < NUMFLAKES; f++)
//     {
//       display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
//     }

//     display.display(); // Show the display buffer on the screen
//     delay(200);        // Pause for 1/10 second

//     // Then update coordinates of each flake...
//     for (f = 0; f < NUMFLAKES; f++)
//     {
//       icons[f][YPOS] += icons[f][DELTAY];
//       // If snowflake is off the bottom of the screen...
//       if (icons[f][YPOS] >= display.height())
//       {
//         // Reinitialize to a random position, just off the top
//         icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
//         icons[f][YPOS] = -LOGO_HEIGHT;
//         icons[f][DELTAY] = random(1, 6);
//       }
//     }
//   }
// }

// void setup()
// {
//   Serial.begin(9600);

//   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//   if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
//   {
//     Serial.println(F("SSD1306 allocation failed"));
//     for (;;)
//       ; // Don't proceed, loop forever
//   }

//   // Show initial display buffer contents on the screen --
//   // the library initializes this with an Adafruit splash screen.
//   display.display();
//   delay(20000); // Pause for 2 seconds

//   // Clear the buffer
//   display.clearDisplay();

//   // // Draw a single pixel in white
//   // display.drawPixel(10, 10, SSD1306_WHITE);

//   // // Show the display buffer on the screen. You MUST call display() after
//   // // drawing commands to make them visible on screen!
//   // display.display();
//   // delay(2000);
//   // // display.display() is NOT necessary after every single drawing command,
//   // // unless that's what you want...rather, you can batch up a bunch of
//   // // drawing operations and then update the screen all at once by calling
//   // // display.display(). These examples demonstrate both approaches...

//   // testdrawline(); // Draw many lines

//   // testdrawrect(); // Draw rectangles (outlines)

//   // testfillrect(); // Draw rectangles (filled)

//   // testdrawcircle(); // Draw circles (outlines)

//   // testfillcircle(); // Draw circles (filled)

//   // testdrawroundrect(); // Draw rounded rectangles (outlines)

//   // testfillroundrect(); // Draw rounded rectangles (filled)

//   // testdrawtriangle(); // Draw triangles (outlines)

//   // testfilltriangle(); // Draw triangles (filled)

//   for (;;)
//   {
//     testdrawchar(); // Draw characters of the default font

//     testdrawstyles(); // Draw 'stylized' characters

//     testscrolltext(); // Draw scrolling text

//     delay(1000);
//   }

//   testdrawbitmap(); // Draw a small bitmap image

//   // Invert and restore display, pausing in-between
//   display.invertDisplay(true);
//   delay(1000);
//   display.invertDisplay(false);
//   delay(1000);

//   testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
// }

// void loop()
// {
// }

/****************************************************************************************************************************
  ConfigOnSwitch.ino
  For ESP8266 / ESP32 boards

  ESP_WiFiManager is a library for the ESP8266/ESP32 platform (https://github.com/esp8266/Arduino) to enable easy
  configuration and reconfiguration of WiFi credentials using a Captive Portal. Inspired by:
  http://www.esp8266.com/viewtopic.php?f=29&t=2520
  https://github.com/chriscook8/esp-arduino-apboot
  https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/

  Modified from Tzapu https://github.com/tzapu/WiFiManager
  and from Ken Taylor https://github.com/kentaylor

  Built by Khoi Hoang https://github.com/khoih-prog/ESP_WiFiManager
  Licensed under MIT license
  Version: 1.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      07/10/2019 Initial coding
  1.0.1   K Hoang      13/12/2019 Fix bug. Add features. Add support for ESP32
  1.0.2   K Hoang      19/12/2019 Fix bug thatkeeps ConfigPortal in endless loop if Portal/Router SSID or Password is NULL.
  1.0.3   K Hoang      05/01/2020 Option not displaying AvailablePages in Info page. Enhance README.md. Modify examples
  1.0.4   K Hoang      07/01/2020 Add RFC952 setHostname feature.
  1.0.5   K Hoang      15/01/2020 Add configurable DNS feature. Thanks to @Amorphous of https://community.blynk.cc
  1.0.6   K Hoang      03/02/2020 Add support for ArduinoJson version 6.0.0+ ( tested with v6.14.1 )
  1.0.7   K Hoang      13/04/2020 Reduce start time, fix SPIFFS bug in examples, update README.md
  1.0.8   K Hoang      10/06/2020 Fix STAstaticIP issue. Restructure code. Add LittleFS support for ESP8266 core 2.7.1+
  1.0.9   K Hoang      29/07/2020 Fix ESP32 STAstaticIP bug. Permit changing from DHCP <-> static IP using Config Portal.
                                  Add, enhance examples (fix MDNS for ESP32)
  1.0.10  K Hoang      08/08/2020 Add more features to Config Portal. Use random WiFi AP channel to avoid conflict.
  1.0.11  K Hoang      17/08/2020 Add CORS feature. Fix bug in softAP, autoConnect, resetSettings.
  1.1.0   K Hoang      28/08/2020 Add MultiWiFi feature to autoconnect to best WiFi at runtime
  1.1.1   K Hoang      30/08/2020 Add setCORSHeader function to allow flexible CORS. Fix typo and minor improvement.
  1.1.2   K Hoang      17/08/2020 Fix bug. Add example.
  1.2.0   K Hoang      09/10/2020 Restore cpp code besides Impl.h code to use if linker error. Fix bug.
  1.3.0   K Hoang      04/12/2020 Add LittleFS support to ESP32 using LITTLEFS Library
 *****************************************************************************************************************************/
/****************************************************************************************************************************
   This example will open a configuration portal when no WiFi configuration has been previously entered or when a button is pushed.
   It is the easiest scenario for configuration but requires a pin and a button on the ESP8266 device.
   The Flash button is convenient for this on NodeMCU devices.

   Also in this example a password is required to connect to the configuration portal
   network. This is inconvenient but means that only those who know the password or those
   already connected to the target WiFi network can access the configuration portal and
   the WiFi network credentials will be sent from the browser over an encrypted connection and
   can not be read by observers.
 *****************************************************************************************************************************/

/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 *
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 *
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 *
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 *
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * ------------------------------------------------------------------------------------------------------------
 *             MFRC522      NodeMCU Lolin      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   V3 Module          Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          ESP8266 (ESP-12F)  Pin           Pin       Pin        Pin              Pin
 * ------------------------------------------------------------------------------------------------------------
 * RST/Reset   RST          D3                 9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      D4                 10            53        D10        10               10
 * SPI MOSI    MOSI         D7                 11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         D6                 12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          D5                 13 / ICSP-3   52        D13        ICSP-3           15
 */

// RST/Reset   RST          D8
// SPI SS      SDA(SS)      RX

// #define NO_GLOBAL_TWOWIRE 1

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266HTTPClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#include "wifiUtils.h"

// #define RST_PIN PIN_D3
// #define SS_PIN PIN_D4

#define SS_PIN PIN_D8
#define RST_PIN PIN_RX

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);
// MFRC522 mfrc522(SS_PIN);
// MFRC522 mfrc522 = MFRC522();

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

// #define SDA_PIN PIN_SD2
// #define SCL_PIN PIN_SD3
#define SDA_PIN PIN_D4
#define SCL_PIN PIN_D3
#define INTERRUPTION0_PIN PIN_D2
#define INTERRUPTION1_PIN PIN_D1

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool hasInterruption0 = false;
bool hasInterruption1 = false;

void ICACHE_RAM_ATTR handleInterrupt0()
{
  printf("In handleInterrupt0\n");
  hasInterruption0 = true;
}

void ICACHE_RAM_ATTR handleInterrupt1()
{
  printf("In handleInterrupt1\n");
  hasInterruption1 = true;
}

Adafruit_SSD1306 *display = NULL;

TwoWire *wire = NULL;
// Set pins for I2C communication
// wire.begin(SDA_PIN, SCL_PIN);

void setup()
{
  // put your setup code here, to run once:
  // initialize the LED digital pin as an output.
  pinMode(PIN_LED, OUTPUT);
  pinMode(INTERRUPTION0_PIN, INPUT_PULLUP);

  // TwoWire wire;
  // // Set pins for I2C communication
  // wire.begin(SDA_PIN, SCL_PIN);
  // Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &wire, OLED_RESET);
  wire = new TwoWire();
  wire->begin(SDA_PIN, SCL_PIN);
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, wire, OLED_RESET);

  Serial.begin(115200);
  while (!Serial)
    ;

  delay(200);

  Serial.println("");
  Serial.println("");
  Serial.println(" *** ");
  Serial.println("Begin setup");
  Serial.println(" *** ");

  // *** Initialisation of the screen
  if (!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display->display();

  // *** Initialisation of RFID reader
  // Init SPI bus
  SPI.begin();
  // Init MFRC522
  mfrc522.PCD_Init();
  // Optional delay. Some board do need more time after init to be ready, see Readme
  delay(4);
  // Show details of PCD - MFRC522 Card Reader details
  mfrc522.PCD_DumpVersionToSerial();
  // Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  // *** Initialisation of wifi connexion
  setupWifi();

  // *** Setup interaction button
  attachInterrupt(digitalPinToInterrupt(INTERRUPTION0_PIN), handleInterrupt0, FALLING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPTION1_PIN), handleInterrupt1, FALLING);

  // Clean the screen display
  display->clearDisplay();
  display->display();

  Serial.println(" *** ");
  Serial.println("End setup");
  Serial.println(" *** ");
}

String getUID(MFRC522::Uid *uid)
{
  String res = "";

  for (byte i = 0; i < uid->size; i++)
  {
    res += String(uid->uidByte[i], HEX);
  }
  return res;
}

const String SERVER_IP("192.168.8.100:3000");

void doGetnSendUID()
{
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  String serverEndPoint = "http://" + SERVER_IP + "/postplain/";
  Serial.print("[HTTP] serverEndPoint: " + serverEndPoint + "\n");
  http.setReuse(true);
  http.begin(client, serverEndPoint);
  http.addHeader("Content-Type", "application/json");

  // start connection and send HTTP header and body
  String message = "{\"uid\":" + getUID(&(mfrc522.uid)) + "}";
  Serial.print("[HTTP] message: " + message + "\n");
  int httpCode = http.POST(message);
  String payload = http.getString();
  Serial.print("[HTTP] payload: " + payload + "\n");

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST succeeded\n");
  }
  else
  {
    Serial.printf("[POST FAILED] httpCode: %d\n", httpCode);
    Serial.printf("[POST FAILED] error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void getnSendUID()
{
  static ulong checkgetuid_timeout = 0;

  static ulong currentMillis;

#define GETUID_INTERVAL 1000L

  currentMillis = millis();

  // Reset the loop if no new card present on the sensor/reader.
  // This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  // Check RFID every GETUID_INTERVAL (1) seconds.
  if ((currentMillis > checkgetuid_timeout) || (checkgetuid_timeout == 0))
  {
    doGetnSendUID();
    checkgetuid_timeout = currentMillis + GETUID_INTERVAL;
  }
}

// void displayInterruption0()
// {
//   static ulong displayTimeout = 0;

//   static ulong currentMillis;

//   static const ulong displayDuration = 3000;

//   currentMillis = millis();

//   if (hasInterruption0)
//   {
//     displayTimeout = millis();
//     hasInterruption0 = false;
//   }

//   static bool hasPrintMessage = false;
//   static bool isClean = false;

//   if ((displayTimeout <= currentMillis) && (currentMillis < displayTimeout + displayDuration))
//   {
//     if (!hasPrintMessage)
//     {
//       display->clearDisplay();

//       display->setTextSize(2);              // Draw 2X-scale
//       display->setTextColor(SSD1306_WHITE); // Draw white text
//       display->setCursor(0, 0);             // Start at top-left corner
//       display->println(F("Interrupt 0"));
//       display->display();
//       isClean = false;
//       hasPrintMessage = true;
//     }
//   }
//   else
//   {
//     if (!isClean)
//     {
//       display->clearDisplay();
//       display->display();
//       isClean = true;
//       hasPrintMessage = false;
//     }
//   }
// }

// void displayInterruption1()
// {
//   static ulong displayTimeout = 0;

//   static ulong currentMillis;

//   static const ulong displayDuration = 3000;

//   currentMillis = millis();

//   if (hasInterruption1)
//   {
//     displayTimeout = millis();
//     hasInterruption1 = false;
//   }

//   static bool hasPrintMessage = false;
//   static bool isClean = false;

//   if ((displayTimeout <= currentMillis) && (currentMillis < displayTimeout + displayDuration))
//   {
//     if (!hasPrintMessage)
//     {
//       display->clearDisplay();

//       display->setTextSize(2);              // Draw 2X-scale
//       display->setTextColor(SSD1306_WHITE); // Draw white text
//       display->setCursor(0, 0);             // Start at top-left corner
//       display->println(F("Interrupt 1"));
//       display->display();
//       isClean = false;
//       hasPrintMessage = true;
//     }
//   }
//   else
//   {
//     if (!isClean)
//     {
//       display->clearDisplay();
//       display->display();
//       isClean = true;
//       hasPrintMessage = false;
//     }
//   }
// }

ulong displayTimeout = 0;
ulong currentMillis;
ulong displayDuration = 3000;
String messageToPrint;

bool hasPrintMessage = false;
bool isClean = false;

void displayMessage()
{
  currentMillis = millis();

  // if (hasInterruption1)
  // {
  //   displayTimeout = millis();
  //   hasInterruption1 = false;
  // }

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

void loop()
{
  if (hasInterruption0)
  {
    hasInterruption0 = false;

    displayTimeout = millis();
    displayDuration = 3000;
    messageToPrint = "Interru. 0";
    hasPrintMessage = false;
    // requestPortalConfiguration();
  }

  if (hasInterruption1)
  {
    hasInterruption1 = false;

    displayTimeout = millis();
    displayDuration = 1000;
    messageToPrint = "Interru. 1\n  AGAIN";
    hasPrintMessage = false;
  }

  displayMessage();

  // put your main code here, to run repeatedly
  checkWifiStatus();

  if (WiFi.status() == WL_CONNECTED)
  {
    getnSendUID();
  }
}