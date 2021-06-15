#include <Arduino.h>
#include "menu.h"
#include "display.h"

static int cursor = -1;
static int menuState[2] = {0, 0};
static bool isReset = true;

static ulong menuDuration = 10000;

int getMenuWidth(int menuState[2], int cursor)
{
  int res = 0;
  if (cursor == 0)
  {
    res = 3;
  }
  if (cursor == 1)
  {
    switch (menuState[0])
    {
    case 0:
      res = 3;
      break;
    default:
      res = 0;
      break;
    }
  }

  return res;
}

void displayMenu()
{
  if (cursor == 0)
  {
    switch (menuState[cursor])
    {
    case 0:
      pushMessage(menuDuration, "Status ->");
      break;
    case 1:
      pushMessage(menuDuration, "Reconnecter au reseau");
      break;
    case 2:
      pushMessage(menuDuration, "Ouvrir portail configuration reseau");
      break;
    }
  }
  if (cursor == 1)
  {
    if (menuState[0] == 0)
    {
      switch (menuState[cursor])
      {
      case 0:
        pushMessage(menuDuration, "Connexion?");
        break;
      case 1:
        pushMessage(menuDuration, "Adresse serveur?");
        break;
      case 2:
        pushMessage(menuDuration, "<- Retour");
        break;
      }
    }
  }
}

static ulong menuInit = 0;

void nextMenu()
{
  menuInit = millis();
  isReset = false;
  if (cursor == -1)
  {
    cursor = 0;
  }
  else
  {
    int menuWidth = getMenuWidth(menuState, cursor);
    menuState[cursor] = (menuState[cursor] + 1) % menuWidth;
  }
  displayMenu();
}

void validate()
{
  menuInit = millis();
  isReset = false;
  if (cursor == 0)
  {
    switch (menuState[cursor])
    {
    case 0:
      ++cursor;
      menuState[cursor] = 0;
      break;
    }
  }
  if (cursor == 1)
  {
    if (menuState[0] == 0)
    {
      switch (menuState[cursor])
      {
      case 2:
        --cursor;
        menuState[cursor] = 0;
        break;
      }
    }
  }
  displayMenu();
}

static ulong currentMillis;

void loopMenu()
{
  currentMillis = millis();

  if ((menuInit + menuDuration < currentMillis) && !isReset)
  {
    cursor = -1;
    menuState[0] = 0;
    menuState[1] = 0;
    isReset = true;
  }
}