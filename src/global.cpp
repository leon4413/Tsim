#include "global.h"

/* if you are using this file you are doing something wrong
 * nonetheless it's still here
 * use with precaution */


float PI = 3.1415926f;

int FPS_LIMIT = 30;
//float PHY_TICK = 1000.0f;
float PHY_TICK = 100000.0f;
bool PHY_RUNNING = true;
float time_speed = 1.0f;


int DNA_max = 18; //THIS IS NOT DIRECTLY CORRELATED WITH THE DIM. OF DNA[]

int seed = 123456789;

double scale = 5.0;

float cam_speed = 100.0f;
float cam_depth = 1000.0f; //500.0f;
float cam_sensitivity = 0.001f;

std::vector<void*> object_array;
