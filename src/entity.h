#ifndef ENTITY
#define ENTITY

#include "global.h"

struct branch_node {
	float pos[3];
	std::vector<void*> con;

	void add_node_pos(float x, float y, float z) {
		branch_node node;
		node.pos[0] = x;
		node.pos[1] = y;
		node.pos[2] = z;
		con.push_back((void*)&node);
	}
};

class real_object {
	public:
		float pos;
		float h_angle;
		float v_angle;

		virtual void update_status(float dt);
		virtual void render();

		//physics update
		//virtual void update_status(float dt);

		// render object 
		//virtual void render();
		
		/* -- how tf do you use virtual functions? */
		

};

/* live object, to be updated every cycle */
class live_object : public real_object {
	public:
		float energy = 100.f;
		float food = 100.f;
		float water = 100.f; //TODO : find use for water
		float temp = 25.f;

		/* DNA is an array witch contains info about the object
		 * refer to DNA.txt*/
		float DNA[8] = {100.f, 100.f, 100.f, 0.1, 0.1, 0.1, 0.f};

		//this is the core node for the plant, every node is connected to this
		branch_node root_node;

		//constructor
		live_object();

		void update_status(float dt);
		void render();
};

#endif //ENTITY
