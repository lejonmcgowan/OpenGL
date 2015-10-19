//
// Created by lejonmcgowan on 8/17/15.
//

#include "Keyboard.h"
bool Keyboard::consumed = false;
int Keyboard::keyToggle[GLFW_KEY_LAST] = {0}; //true means the key is pressed
