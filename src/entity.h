#ifndef ENTITY
#define ENTITY

#include "global.h"


/* CLASS
 * name : branch_node
 * porpuse : base block for the tree structure of plants. Store its position and a vector with reference to all it's connections
 * */
class branch_node {
public:
	float pos[3];
	std::vector<void*> con;

	void add_node_pos(float x, float y, float z);
};

/* CLASS
 * name : real_object
 * porpuse : parent class for all object in the simulation. Hold basic data about position and orientation
 * problem : I still have to understand how to use virtuall methods
 * */
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
/* CLASS
 * name : live_object
 * porpuse : rapresent plants and their function, holds data about the stateof the plant
 * problem : wrong name, this class should be an intermediate between plants and animals!
 * */
class live_object : public real_object {
	public:
		float energy = 100.f;
		float food = 100.f;
		float water = 100.f; //TODO : find use for water
		float temp = 25.f;
		float color[3];

		/* DNA is an array witch contains info about the object
		 * refer to DNA.txt*/
		float DNA[9] = {0.f, 100.f, 100.f, 100.f, 0.1, 0.1, 0.1, 0.f, 5.0f};

		//this is the core node for the plant, every node is connected to this
		branch_node root_node;

		//constructor
		live_object();

		//mehtod called every physics tick
		void update_status(float dt);
		//method called to render the plant (secretly recursive function)
		void render();
		//method called to grow one node (recursive function)
		void grow(branch_node& node, int depth = 0);

		int node_count = 1;
		//method called to count the number of nodes (recursive function)
		int count_nodes(branch_node& node, int count = 1);
};

#endif //ENTITY
