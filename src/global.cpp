#include "global.h"

/* if you are using this file you are doing something wrong
 * nonetheless it's still here
 * use with precaution */


float PI = 3.1415926f;

int FPS_LIMIT = 15;

int seed = 123456789;

double scale = 5.0;

float cam_speed = 100.0f;
float cam_depth = 1000.0f; //500.0f;
float cam_sensitivity = 0.001f;

std::vector<void*> object_array;
