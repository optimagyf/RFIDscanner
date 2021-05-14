#pragma once

#ifndef _WIFI_UTILS_H
#define _WIFI_UTILS_H

#include "pinLayout.h"

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
                                 // #define USE_DHCP_IP false
#endif

// #define USE_CONFIGURABLE_DNS true
#define USE_CONFIGURABLE_DNS false

// #include <ESP_WiFiManager.h> //https://github.com/khoih-prog/ESP_WiFiManager

// Userland prototype
void setupWifi();
void requestPortalConfiguration();
void checkWifiStatus();

#endif // _WIFI_UTILS_H
