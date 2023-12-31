#include "entity.h"
#include "global.h"

#include <math.h>
#include <vector>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>


/* live object contructor */
live_object::live_object(std::vector<live_object*> live_array) {
	
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
	
	/*glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, lines);
	glDrawArrays(GL_LINES, 0 ,2);

	glDisableClientState(GL_VERTEX_ARRAY);
*/
	glBegin(GL_LINES);
		//glVertex3f();
	glEnd();
	
}

void live_object::remesh() {
	
}

node::node(float x, float y, float z) {
	pos[0] = x;
	pos[0] = y;
	pos[0] = z;
}

void node::add_pos(float x, float y, float z) {
	//n_node = new node(x,y,z);
	node n_node(x,y,z);
	this->con.push_back(n_node*);
}

void node::add_node(node a) {
	this->con.push_back(a*);
}
