#ifndef GLOBAL
#define GLOBAL

#include "entity.h"
#include <vector>

extern float PI;

class self_camera {
public:
	double pos[3] = {0.0f, 0.0f, 0.0f};
	double vel[3] = {0.0f, 0.0f, 0.0f};

	float h_angle = 0.0f;
	float v_angle = 0.0f;
};

/*
class node {
	float pos[3];
	std::vector<node*> con;
};
*/


/* GLOBAL VARIABLES 
 * MAP is for defining the map dimensions
 * MAP_Z is the max height of the ground
 * FILTER_PASS is the number of passess made by the ground filter
 * FPS_LIMIT limits window fps, (-1 to disable)
 * seed is for the rand() function
 * alpha is for rotating the ground
 * scale is the scale
 * cam_speed is the movement speed of the camera*/

extern int MAP_X_MAX;
extern int MAP_Y_MAX;
extern int MAP_Z_MAX;
extern int MAP_Z_MIN;
extern int MAP_Z_CUTOFF;

extern int FILTER_PASS;
extern int FPS_LIMIT;

extern int seed;

extern double alpha;
extern double scale;

extern float cam_speed;
extern float cam_depth;
extern float cam_sensitivity;

/* -- -- */

#endif //GLOBAL
