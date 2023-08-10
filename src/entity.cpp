#include "entity.h"
#include "global.h"

/* This is the recursive function i use to render the plants
 * I don't think this is efficent enough, and i will have to
 * change it! */
void render_node(branch_node &node){
	if (node.con.empty()) { 
		// Recursion end
		glVertex3f(node.pos[0], node.pos[1], node.pos[2]);
	} else { 
		// Recursion
		glVertex3f(node.pos[0], node.pos[1], node.pos[2]);

		for (int i = 0; i < (int)node.con.size(); i++) {
			render_node(*(branch_node*)node.con[i]);
		};

	}
};


/* live object contructor */
live_object::live_object() {
	object_array.push_back(this);
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
	glBegin(GL_LINES);
		render_node(root_node);
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
