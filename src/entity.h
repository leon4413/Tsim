#ifndef ENTITY
#define ENTITY

#include "global.h"

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

		//keep tracks of the position of the various nodes
		float branch_nodes[3][3] = {{0.f, 0.f, 0.f} , {0.f, 10.f, 0.f}, {0.f, 20.f, 10.f}};
		;

		//constructor
		live_object();

		void update_status(float dt);
		void render();
};

#endif //ENTITY
