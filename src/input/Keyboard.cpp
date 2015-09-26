//
// Created by lejonmcgowan on 8/17/15.
//

#include "Keyboard.hpp"
bool Keyboard::keyToggle[GLFW_KEY_LAST] = {0}; //true means the key is pressed
int Keyboard::lastAction = GLFW_RELEASE;
int Keyboard::lastKeyPressed = GLFW_KEY_UNKNOWN;
int Keyboard::lastMods = 0;
int Keyboard::lastScancode = 0;