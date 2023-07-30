#include "entity.h"
#include "global.h"

#include <math.h>
#include <vector>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>


/* live object contructor */
live_object::live_object() {
	
	live_array.push_back(this);

}

/* live object update status
 * Input : - delta time (in microseconds) 
 * Exec : update energy, food and water based on status */
void live_object::update_status(float dt_c) {
	float dt = dt_c * pow(10,6);

	energy -= DNA[4] * dt;
	temp += DNA[4] * dt;

	food -= DNA[5] * dt;
	energy += DNA[5] * dt;

	water -= DNA[6] * dt;

}

/* live object reproduction */
void live_object::reproduce() {

}

void live_object::render() {
	//render stuff
	
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, lines);
	glDrawArrays(GL_LINES, 0 ,2);

	glDisableClientState(GL_VERTEX_ARRAY);

}

void live_object::remesh() {
	
}
