#ifndef ENTITY
#define ENTITY

#include <vector>

#include "global.h"

/* ground object, not alive */
class g_object {
	public:
		float pos;
		float h_angle;
		float v_angle;
		float *model;
};

class node {
public:
	float pos[3] = {0.0f, 0.0f, 0.0f};
	std::vector<node*> con = {};

	node(float x, float y, float z);

	void add_pos(float x, float y, float z);
	void add_node(node a);
};

/* live object, to be updated every cycle */
class live_object {
	public:
		float pos;
		float h_angle;
		float v_angle;
		std::vector<node*> nodes;

		float energy;
		float food;
		float water; //TODO : find use for water
		float temp;

		/* DNA is an array witch contains info about the object
		 * refer to DNA.txt*/
		float DNA[8];

		//constructor
		live_object(std::vector<live_object*> live_array);

		// update energy, food and water every *dt* microseconds
		void update_status(float dt);

		// try reproduction
		void reproduce();

		/* render object */
		void render();

		// remesh based on nodes
		void remesh();
};




#endif //ENTITY
