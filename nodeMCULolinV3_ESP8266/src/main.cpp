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

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266HTTPClient.h>

#include "display.h"
#include "pinLayout.h"
#include "wifiUtils.h"
#include "menu.h"

#define SS_PIN PIN_D8
#define RST_PIN PIN_RX

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define INTERRUPTION0_PIN PIN_D2
#define INTERRUPTION1_PIN PIN_D1

bool hasInterruption0 = false;
bool hasInterruption1 = false;

void ICACHE_RAM_ATTR handleInterrupt0()
{
  hasInterruption0 = true;
}

void ICACHE_RAM_ATTR handleInterrupt1()
{
  hasInterruption1 = true;
}

void setup()
{
  // initialize the LED digital pin as an output.
  pinMode(PIN_LED, OUTPUT);
  pinMode(INTERRUPTION0_PIN, INPUT_PULLUP);

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
  initScreen();

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

const String SERVER_IP("192.168.1.19:3000");
// const String SERVER_IP("192.168.43.172:3000");

void doGetnSendUID()
{
  WiFiClient client;
  HTTPClient http;

  Serial.printf("[HTTP] begin...\n");
  // configure traged server and url
  String serverEndPoint = "http://" + SERVER_IP + "/postplain/";
  Serial.print("[HTTP] serverEndPoint: " + serverEndPoint + "\n");
  http.setReuse(true);
  http.begin(client, serverEndPoint);
  http.addHeader("Content-Type", "application/json");

  // start connection and send HTTP header and body
  String message = "{\"uid\":\"" + getUID(&(mfrc522.uid)) + "\"}";
  printf("[HTTP] message: %s\n", message.c_str());
  int httpCode = http.POST(message);

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    String payload = http.getString();
    printf("[HTTP] payload: %s\n", payload.c_str());
    Serial.printf("[HTTP] POST succeeded\n");
    pushMessage(3000, "Successfully scan\n" + getUID(&(mfrc522.uid)));
  }
  else
  {
    // HTTP header has been send and Server response header has been handled
    String payload = http.getString();
    printf("[POST FAILED] payload: %s\n", payload.c_str());
    printf("[POST FAILED] httpCode: %d\n", httpCode);
    printf("[POST FAILED] error: %s\n", http.errorToString(httpCode).c_str());
    pushMessage(3000, "Fail to scan\n" + getUID(&(mfrc522.uid)));
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

void triggerInterruption0()
{
  // pushMessage(1000, "Interru. 0");
  nextMenu();
}

void triggerInterruption1()
{
  // pushMessage(3000, "Interru. 1\n  AGAIN");
  enter();
}

void loop()
{
  loopMessage();
  loopMenu();

  if (hasInterruption0)
  {
    hasInterruption0 = false;
    triggerInterruption0();
  }

  if (hasInterruption1)
  {
    hasInterruption1 = false;
    triggerInterruption1();
  }

  checkWifiStatus();

  if (WiFi.status() == WL_CONNECTED)
  {
    getnSendUID();
  }
}