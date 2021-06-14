#pragma once

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

void initScreen();
void pushMessage(ulong displayDuration_, String messageToDisplay_);
void loopMessage();

// Externalised variable
extern Adafruit_SSD1306 *display;
extern TwoWire *wire;
// <----- Externalised variable

#endif // _DISPLAY_H