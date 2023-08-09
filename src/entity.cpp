#include "entity.h"
#include "global.h"

/* live object contructor */
live_object::live_object() {
	object_array.push_back(this);

	//branch_nodes = {{0.f, 0.f, 0.f} , {0.f, 10.f, 0.f}, {0.f, 20.f, 0.f}};
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

void live_object::render() {
	//render stuff
	
	/*glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, lines);
	glDrawArrays(GL_LINES, 0 ,2);

	glDisableClientState(GL_VERTEX_ARRAY);
*/
	glBegin(GL_LINE_STRIP);
		for(int i = 0; i < (int)(sizeof(branch_nodes) / ( 3 * sizeof(float) ) ); i++ ){
			glVertex3f(branch_nodes[i][0], branch_nodes[i][1], branch_nodes[i][2]);
		};
	glEnd();
	
}

void real_object::update_status(float dt_c){
	//nothig for now
	dt_c = dt_c;
}

void real_object::render() {
	//nothing
	std::cout << "rendering stuff \n";	
}; 
