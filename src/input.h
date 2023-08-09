#include "global.h"

#ifndef KEYBOARD
#define KEYBOARD

void key_pressed(camera_object* cam, float dt_c, sf::Window* window);

void event_check(sf::Window* window);

#endif //KEYBOARD
