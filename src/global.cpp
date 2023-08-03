#include "global.h"
#include "entity.h"

#include <vector>

float PI = 3.1415926f;

/* GLOBAL VARIABLES 
 * MAP is for defining the map dimensions
 * MAP_Z is the max height of the ground
 * FILTER_PASS is the number of passess made by the ground filter
 * FPS_LIMIT limits window fps, (-1 to disable)
 * seed is for the rand() function
 * alpha is for rotating the ground
 * scale is the scale
 * cam_speed is the movement speed of the camera*/

int MAP_X_MAX = 10;
int MAP_Y_MAX = 10;
int MAP_Z_MAX = 10;
int MAP_Z_MIN = 7; // ( [< 0] == disabled)
int MAP_Z_CUTOFF = 1; // ( [< 0] == disabled)

int FILTER_PASS = 2;
int FPS_LIMIT = 15;

int seed = 123456789;

double alpha = 0.0f; //0.25 * 3.1415;
double scale = 5.0;

float cam_speed = 100.0f;
float cam_depth = 1000.0f; //500.0f;
float cam_sensitivity = 0.001f;

/* -- -- */
