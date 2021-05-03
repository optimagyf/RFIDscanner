#pragma once

#ifndef _WIFI_UTILS_H
#define _WIFI_UTILS_H

#if !(defined(ESP8266) || defined(ESP32))
#error This code is intended to run only on the ESP8266 and ESP32 boards ! Please check your Tools->Board setting.
#endif

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _WIFIMGR_LOGLEVEL_ 3

//For ESP32, To use ESP32 Dev Module, QIO, Flash 4MB/80MHz, Upload 921600

//Ported to ESP32
#ifdef ESP32
#include <esp_wifi.h>
#include <WiFi.h>
#include <WiFiClient.h>

// From v1.1.0
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

// LittleFS has higher priority than SPIFFS
#define USE_LITTLEFS true
#define USE_SPIFFS false

#if USE_LITTLEFS
// Use LittleFS
#include "FS.h"

// The library will be depreciated after being merged to future major Arduino esp32 core release 2.x
// At that time, just remove this library inclusion
#include <LITTLEFS.h> // https://github.com/lorol/LITTLEFS

FS *filesystem = &LITTLEFS;
#define FileFS LITTLEFS
#define FS_Name "LittleFS"
#elif USE_SPIFFS
#include <SPIFFS.h>
FS *filesystem = &SPIFFS;
#define FileFS SPIFFS
#define FS_Name "SPIFFS"
#else
// Use FFat
#include <FFat.h>
FS *filesystem = &FFat;
#define FileFS FFat
#define FS_Name "FFat"
#endif
//////

#define ESP_getChipId() ((uint32_t)ESP.getEfuseMac())

#define LED_BUILTIN 2
#define LED_ON HIGH
#define LED_OFF LOW

#else
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// From v1.1.0
#include <ESP8266WiFiMulti.h>
// ESP8266WiFiMulti wifiMulti;

#define USE_LITTLEFS true

#if USE_LITTLEFS
#include <LittleFS.h>
// FS *filesystem = &LittleFS;
#define FileFS LittleFS
#define FS_Name "LittleFS"
#else
FS *filesystem = &SPIFFS;
#define FileFS SPIFFS
#define FS_Name "SPIFFS"
#endif // USE_LITTLEFS
//////

#define ESP_getChipId() (ESP.getChipId())

// #define LED_ON LOW
// #define LED_OFF HIGH
#define LED_ON HIGH
#define LED_OFF LOW
#endif // ESP32

#ifdef ESP32

//See file .../hardware/espressif/esp32/variants/(esp32|doitESP32devkitV1)/pins_arduino.h
#define LED_BUILTIN 2 // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED
#define PIN_LED 2     // Pin D2 mapped to pin GPIO2/ADC12 of ESP32, control on-board LED

#define PIN_D0 0 // Pin D0 mapped to pin GPIO0/BOOT/ADC11/TOUCH1 of ESP32
#define PIN_D1 1 // Pin D1 mapped to pin GPIO1/TX0 of ESP32
#define PIN_D2 2 // Pin D2 mapped to pin GPIO2/ADC12/TOUCH2 of ESP32
#define PIN_D3 3 // Pin D3 mapped to pin GPIO3/RX0 of ESP32
#define PIN_D4 4 // Pin D4 mapped to pin GPIO4/ADC10/TOUCH0 of ESP32
#define PIN_D5 5 // Pin D5 mapped to pin GPIO5/SPISS/VSPI_SS of ESP32
#define PIN_D6 6 // Pin D6 mapped to pin GPIO6/FLASH_SCK of ESP32
#define PIN_D7 7 // Pin D7 mapped to pin GPIO7/FLASH_D0 of ESP32
#define PIN_D8 8 // Pin D8 mapped to pin GPIO8/FLASH_D1 of ESP32
#define PIN_D9 9 // Pin D9 mapped to pin GPIO9/FLASH_D2 of ESP32

#define PIN_D10 10 // Pin D10 mapped to pin GPIO10/FLASH_D3 of ESP32
#define PIN_D11 11 // Pin D11 mapped to pin GPIO11/FLASH_CMD of ESP32
#define PIN_D12 12 // Pin D12 mapped to pin GPIO12/HSPI_MISO/ADC15/TOUCH5/TDI of ESP32
#define PIN_D13 13 // Pin D13 mapped to pin GPIO13/HSPI_MOSI/ADC14/TOUCH4/TCK of ESP32
#define PIN_D14 14 // Pin D14 mapped to pin GPIO14/HSPI_SCK/ADC16/TOUCH6/TMS of ESP32
#define PIN_D15 15 // Pin D15 mapped to pin GPIO15/HSPI_SS/ADC13/TOUCH3/TDO of ESP32
#define PIN_D16 16 // Pin D16 mapped to pin GPIO16/TX2 of ESP32
#define PIN_D17 17 // Pin D17 mapped to pin GPIO17/RX2 of ESP32
#define PIN_D18 18 // Pin D18 mapped to pin GPIO18/VSPI_SCK of ESP32
#define PIN_D19 19 // Pin D19 mapped to pin GPIO19/VSPI_MISO of ESP32

#define PIN_D21 21 // Pin D21 mapped to pin GPIO21/SDA of ESP32
#define PIN_D22 22 // Pin D22 mapped to pin GPIO22/SCL of ESP32
#define PIN_D23 23 // Pin D23 mapped to pin GPIO23/VSPI_MOSI of ESP32
#define PIN_D24 24 // Pin D24 mapped to pin GPIO24 of ESP32
#define PIN_D25 25 // Pin D25 mapped to pin GPIO25/ADC18/DAC1 of ESP32
#define PIN_D26 26 // Pin D26 mapped to pin GPIO26/ADC19/DAC2 of ESP32
#define PIN_D27 27 // Pin D27 mapped to pin GPIO27/ADC17/TOUCH7 of ESP32

#define PIN_D32 32 // Pin D32 mapped to pin GPIO32/ADC4/TOUCH9 of ESP32
#define PIN_D33 33 // Pin D33 mapped to pin GPIO33/ADC5/TOUCH8 of ESP32
#define PIN_D34 34 // Pin D34 mapped to pin GPIO34/ADC6 of ESP32

//Only GPIO pin < 34 can be used as output. Pins >= 34 can be only inputs
//See .../cores/esp32/esp32-hal-gpio.h/c
//#define digitalPinIsValid(pin)          ((pin) < 40 && esp32_gpioMux[(pin)].reg)
//#define digitalPinCanOutput(pin)        ((pin) < 34 && esp32_gpioMux[(pin)].reg)
//#define digitalPinToRtcPin(pin)         (((pin) < 40)?esp32_gpioMux[(pin)].rtc:-1)
//#define digitalPinToAnalogChannel(pin)  (((pin) < 40)?esp32_gpioMux[(pin)].adc:-1)
//#define digitalPinToTouchChannel(pin)   (((pin) < 40)?esp32_gpioMux[(pin)].touch:-1)
//#define digitalPinToDacChannel(pin)     (((pin) == 25)?0:((pin) == 26)?1:-1)

#define PIN_D35 35 // Pin D35 mapped to pin GPIO35/ADC7 of ESP32
#define PIN_D36 36 // Pin D36 mapped to pin GPIO36/ADC0/SVP of ESP32
#define PIN_D39 39 // Pin D39 mapped to pin GPIO39/ADC3/SVN of ESP32

#define PIN_RX0 3 // Pin RX0 mapped to pin GPIO3/RX0 of ESP32
#define PIN_TX0 1 // Pin TX0 mapped to pin GPIO1/TX0 of ESP32

#define PIN_SCL 22 // Pin SCL mapped to pin GPIO22/SCL of ESP32
#define PIN_SDA 21 // Pin SDA mapped to pin GPIO21/SDA of ESP32
#else
//PIN_D0 can't be used for PWM/I2C
#define PIN_D0 16  // Pin D0 mapped to pin GPIO16/USER/WAKE of ESP8266. \
                   // This pin is also used for Onboard-Blue LED.       \
                   // PIN_D0 = 0 => LED ON
#define PIN_D1 5   // Pin D1 mapped to pin GPIO5 of ESP8266
#define PIN_D2 4   // Pin D2 mapped to pin GPIO4 of ESP8266
#define PIN_D3 0   // Pin D3 mapped to pin GPIO0/FLASH of ESP8266
#define PIN_D4 2   // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, \
                   // NodeMCU and WeMoS, control on-board LED
#define PIN_D5 14  // Pin D5 mapped to pin GPIO14/HSCLK of ESP8266
#define PIN_D6 12  // Pin D6 mapped to pin GPIO12/HMISO of ESP8266
#define PIN_D7 13  // Pin D7 mapped to pin GPIO13/RXD2/HMOSI of ESP8266
#define PIN_D8 15  // Pin D8 mapped to pin GPIO15/TXD2/HCS of ESP8266

// Don't use pins GPIO6 to GPIO11 as already connected to flash, etc.
// Use them can crash the program
// GPIO9(D11/SD2) and GPIO11 can be used only if flash in DIO mode
// (not the default QIO mode)
#define PIN_D11 9  // Pin D11/SD2 mapped to pin GPIO9/SDD2 of ESP8266
#define PIN_D12 10 // Pin D12/SD3 mapped to pin GPIO10/SDD3 of ESP8266
#define PIN_SD2 9  // Pin SD2 mapped to pin GPIO9/SDD2 of ESP8266
#define PIN_SD3 10 // Pin SD3 mapped to pin GPIO10/SDD3 of ESP8266

#define PIN_D9 3  // Pin D9 /RX mapped to pin GPIO3/RXD0 of ESP8266
#define PIN_D10 1 // Pin D10/TX mapped to pin GPIO1/TXD0 of ESP8266
#define PIN_RX 3  // Pin RX mapped to pin GPIO3/RXD0 of ESP8266
#define PIN_TX 1  // Pin RX mapped to pin GPIO1/TXD0 of ESP8266

// #define LED_PIN 16 // Pin D0 mapped to pin GPIO16 of ESP8266. This pin is also used for Onboard-Blue LED. PIN_D0 = 0 => LED ON
#define PIN_LED PIN_D0

#endif // ESP32

#ifdef ESP32
/* Trigger for inititating config mode is Pin D3 and also flash button on NodeMCU
   Flash button is convenient to use but if it is pressed it will stuff up the serial port device driver
   until the computer is rebooted on windows machines.
*/
const int TRIGGER_PIN = PIN_D0; // Pin D0 mapped to pin GPIO0/BOOT/ADC11/TOUCH1 of ESP32
/*
   Alternative trigger pin. Needs to be connected to a button to use this pin. It must be a momentary connection
   not connected permanently to ground. Either trigger pin will work.
*/
const int TRIGGER_PIN2 = PIN_D25; // Pin D25 mapped to pin GPIO25/ADC18/DAC1 of ESP32
#else
/* Trigger for inititating config mode is Pin D3 and also flash button on NodeMCU
   Flash button is convenient to use but if it is pressed it will stuff up the serial port device driver
   until the computer is rebooted on windows machines.
*/
const int TRIGGER_PIN = PIN_D3; // D3 on NodeMCU and WeMos.
/*
   Alternative trigger pin. Needs to be connected to a button to use this pin. It must be a momentary connection
   not connected permanently to ground. Either trigger pin will work.
*/
const int TRIGGER_PIN2 = PIN_D7; // D7 on NodeMCU and WeMos.

#endif // ESP32

// From v1.1.0
// You only need to format the filesystem once
//#define FORMAT_FILESYSTEM       true
#define FORMAT_FILESYSTEM false

#define MIN_AP_PASSWORD_SIZE 8

#define SSID_MAX_LEN 32
//From v1.0.10, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN 64

typedef struct
{
   char wifi_ssid[SSID_MAX_LEN];
   char wifi_pw[PASS_MAX_LEN];
} WiFi_Credentials;

typedef struct
{
   String wifi_ssid;
   String wifi_pw;
} WiFi_Credentials_String;

#define NUM_WIFI_CREDENTIALS 2

typedef struct
{
   WiFi_Credentials WiFi_Creds[NUM_WIFI_CREDENTIALS];
} WM_Config;

// WM_Config WM_config;

#define CONFIG_FILENAME F("/wifi_cred.dat")
//////

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESP_WiFiManager.h>
#define USE_AVAILABLE_PAGES false

// From v1.0.10 to permit disable/enable StaticIP configuration in Config Portal from sketch. Valid only if DHCP is used.
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_WIFIMANAGER_NTP false

// Use true to enable CloudFlare NTP service. System can hang if you don't have Internet access while accessing CloudFlare
// See Issue #21: CloudFlare link in the default portal (https://github.com/khoih-prog/ESP_WiFiManager/issues/21)
#define USE_CLOUDFLARE_NTP false

// New in v1.0.11
#define USING_CORS_FEATURE true
//////

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
// Force DHCP to be true
#if defined(USE_DHCP_IP)
#undef USE_DHCP_IP
#endif
#define USE_DHCP_IP true
#else
                                 // You can select DHCP or Static IP here
#define USE_DHCP_IP true
                                 //#define USE_DHCP_IP     false
#endif

#define USE_CONFIGURABLE_DNS true

// #include <ESP_WiFiManager.h> //https://github.com/khoih-prog/ESP_WiFiManager

// Userland prototype
void setupWifi();
void requestPortalConfiguration();
void checkWifiStatus();

#endif // _WIFI_UTILS_H
