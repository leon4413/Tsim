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


/* CLASS 
 * name : camera_object
 * porpuse : store info about camera orientation and position.
 *			 it also stores the last known position of the mouse, to integrate the camera movement
 * */
class camera_object {
public:
	double pos[3] = {0.0f, 0.0f, 0.0f};
	double vel[3] = {0.0f, 0.0f, 0.0f};

	float h_angle = 0.0f;
	float v_angle = 0.0f;

	sf::Vector2i mouse_pos_int;
};

/* CLASS
 * name : debug
 * porpuse : stupid. Just to use console.log()
 * */
class debug {
public:

	void log(std::string message){
		std::cout << message << "\n";
	};
};

/* GLOBAL VARIABLES 
 * PI set the value for pi
 * FPS_LIMIT limits window fps, (-1 to disable)
 * PHY_TICK is the number of microseconds between every physics tick (it's a period, not frequency)
 * seed is for the rand() function
 * scale is the scale
 * cam_speed is the movement speed of the camera*/

extern float PI ;

extern int FPS_LIMIT ;
extern float PHY_TICK ; //in microseconds!
extern bool PHY_RUNNING ;
extern float time_speed ;

extern int DNA_max ;

extern int seed ;

extern double scale ;

extern float cam_speed ;
extern float cam_depth ; 
extern float cam_sensitivity ;

extern std::vector<void*> object_array;

/* -- -- */

#endif //GLOBAL
