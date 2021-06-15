#include <Arduino.h>
#include "menu.h"
#include "display.h"

static int menuLevel0 = 2;
static int menuLevel1 = 0;
static bool isReset = true;

static ulong menuDuration = 30000;

void displayMenu()
{
  switch (menuLevel0)
  {
  case 0:
    pushMessage(menuDuration, "Status");
    break;
  case 1:
    pushMessage(menuDuration, "Reconnecter au reseau");
    break;
  case 2:
    pushMessage(menuDuration, "Ouvrir portail configuration reseau");
    break;
  }
}

static ulong menuInit = 0;

void nextMenu()
{
  menuInit = millis();
  isReset = false;
  menuLevel0 = (menuLevel0 + 1) % 3;
  displayMenu();
}

void enter()
{
  pushMessage(1000, "Enter");
  isReset = false;
}

static ulong currentMillis;

void loopMenu()
{
  currentMillis = millis();

  if ((menuInit + menuDuration < currentMillis) && !isReset)
  {
    menuLevel0 = 2;
    menuLevel1 = 0;
    isReset = true;
  }
}