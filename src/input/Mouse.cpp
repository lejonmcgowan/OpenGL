//
// Created by lejonmcgowan on 8/22/15.
//

#include "Mouse.h"
bool Mouse::mouseToggles[GLFW_MOUSE_BUTTON_LAST] = {0};
glm::vec2 Mouse::currentScrollPosition = glm::vec2(), Mouse::lastScrollPosition = glm::vec2();

glm::vec2 Mouse::currentCursorPosition = glm::vec2(), Mouse::lastCursorPosition = glm::vec2();

glm::vec2 Mouse::cursorOffset = glm::vec2(), Mouse::scrollOffset = glm::vec2();
bool Mouse::initialized = false;

int Mouse::lastButton = 0;
int Mouse::lastAction = 0;
int Mouse::lastMods = 0;
