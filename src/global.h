#ifndef GLOBAL
#define GLOBAL

/* Used Libraries */
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

class camera_object {
public:
	double pos[3] = {0.0f, 0.0f, 0.0f};
	double vel[3] = {0.0f, 0.0f, 0.0f};

	float h_angle = 0.0f;
	float v_angle = 0.0f;
};

/* GLOBAL VARIABLES 
 * PI set the value for pi
 * FPS_LIMIT limits window fps, (-1 to disable)
 * seed is for the rand() function
 * scale is the scale
 * cam_speed is the movement speed of the camera*/

extern float PI ;

extern int FPS_LIMIT ;

extern int seed ;

extern double scale ;

extern float cam_speed ;
extern float cam_depth ; 
extern float cam_sensitivity ;

extern std::vector<void*> object_array;

/* -- -- */

#endif //GLOBAL
