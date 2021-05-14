#pragma once

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

void initScreen();
void displayMessage();

// Externalised variable
extern Adafruit_SSD1306 *display;
extern TwoWire *wire;

extern ulong displayTimeout;
extern ulong displayDuration;
extern String messageToPrint;
extern bool hasPrintMessage;
// <----- Externalised variable

#endif // _DISPLAY_H