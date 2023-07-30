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


/* live object, to be updated every cycle */
class live_object {
	public:
		float pos;
		float h_angle;
		float v_angle;
		float* lines;
		std::vector<point3f> nodes;

		float energy;
		float food;
		float water; //TODO : find use for water
		float temp;

		/* DNA is an array witch contains info about the object
		 * refer to DNA.txt*/
		float DNA[8];

		//constructor
		live_object();

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
