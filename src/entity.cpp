#include "entity.h"
#include "global.h"

/* METHOD
 * name : add_node_pos
 * input : x,y,z - pos of new node
 * function : to add a new node to an existing one by giving it's position*/
void branch_node::add_node_pos(float x, float y, float z) {
	branch_node* node = new branch_node;
	node->pos[0] = x;
	node->pos[1] = y;
	node->pos[2] = z;
	con.push_back((void*)node);
};

/* This is the recursive function i use to render the plants
 * I don't think this is efficent enough, and i will have to
 * change it! */
void render_node(branch_node &node){
	if (!node.con.empty()) { 
		// Recursion

		for (int i = 0; i < (int)node.con.size(); i++) {
			//std::cout << i << " - "<< node.con[i] << "\n"; //without this debug line it goes in segmentation fault WTF ... not anymore lmao
			
			glVertex3f(node.pos[0], node.pos[1], node.pos[2]);
			glVertex3f(((branch_node*)node.con[i])->pos[0], ((branch_node*)node.con[i])->pos[1], ((branch_node*)node.con[i])->pos[2]);

			render_node(*(branch_node*)node.con[i]);
		};

	}
};


/* live object contructor */
live_object::live_object() {
	object_array.push_back(this);
	color[0] = 1.f;
	color[1] = 1.f;
	color[2] = 1.f;
}

/* live object update status
 * Input : - delta time (in microseconds) 
 * Exec : update energy, food and water based on status 
 * problem :the rand function is not random enough, and can give rise to a growth sprint of up to 5 or 6 nodes*/
void live_object::update_status(float dt_c) {
	float dt = dt_c * pow(10,-6);

	energy -= DNA[4] * dt;
	temp += DNA[4] * dt;

	if (food > 0) {
		food -= DNA[5] * dt;
		energy += DNA[5] * dt;
	}

	if (water > 0) {
		water -= DNA[6] * dt;
		temp -= DNA[6] * dt;
	}
	if ( (float)(rand()%10000)/100 < DNA[8] ) { //grow plant
		this->grow(root_node);
		node_count = this->count_nodes(root_node, 1);
	}

	std::cout << "status update on : " << this << "  -- dt : " << dt << "\n";
	std::cout << "energy : " << energy << "\n food : " << food << "\n water : " << water << "\n temp : " << temp << "\n nodes : " << node_count << "\n";

}

/* METHOD
 * name : render
 * function : to render a plant
 * problem : it's a recursive function, i don't like it!*/
void live_object::render() {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINES);
		render_node(root_node);
	glEnd();
	
}

/* recursive function that grow a branch of the plant 
 * this only add one node, then stops! 
 * input : node - the current node
 *		   depth - the current depth in the tree
 * problem : the random direction and offspring gives a terrible look after the 10nth or so node*/
void live_object::grow(branch_node &node, int depth){

	if (!node.con.empty()) { //if this is not an end branch
		for (int i = 0; i < (int)node.con.size(); i++) {
			if ( (rand() % 20) < depth ) { //roll a dice based on depth. the deeper the easier to grow a branch there

				float offset[3] = { 
					(float)(rand() % 10 - 5), 
					(float)(rand() % 10), 
					(float)(rand() % 10 - 5)
				};

				node.add_node_pos(node.pos[0] + offset[0], node.pos[1] + offset[1], node.pos[2] + offset[2]);
				break;
			} else { //recursion
				int next_node_index = rand() % node.con.size(); //pick a random direction to follow
				this->grow(*((branch_node*)node.con[next_node_index]), (depth + 1)); //call function
				break;
			}
		}
	} else { //if this is a end of branch, add node here
		float offset[3] = { 
			(float)(rand() % 10 - 5), 
			(float)(rand() % 10), 
			(float)(rand() % 10 - 5)
		};

		node.add_node_pos(node.pos[0] + offset[0], node.pos[1] + offset[1], node.pos[2] + offset[2]);
	}
}

/* METHOD
 * name : update_status
 * function : place holder for the real_object function, in case i have to add some check every phy tick
 * input :dt_c current delta time*/
void real_object::update_status(float dt_c){
	//nothig for now
	dt_c = dt_c;
}

/* METHOD
 * name : render
 * function : to render a real, static object
 * problem : still not implemented*/
void real_object::render() {
	//nothing
	std::cout << "rendering stuff \n";	
}; 

/* METHOD
 * name : count_nodes
 * function : count nodes of a plant recursively
 * input : node - current node to count
 *		   count - current count*/
int live_object::count_nodes(branch_node& node, int count){
	int c_count = count;
	for (int i = 0; i < (int)node.con.size(); i++) {
		c_count += this->count_nodes(*(branch_node*)node.con[i], count);
	}

	return c_count;
};
