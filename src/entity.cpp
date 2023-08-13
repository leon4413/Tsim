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
	array_index = object_array.size();
	color[0] = 1.f;
	color[1] = 1.f;
	color[2] = 1.f;
}

/* live object deconstructor */
live_object::~live_object() {
	//vector magic
	std::vector<void*>::iterator pos = object_array.begin() + array_index;
	object_array.erase(pos)	;
}

/* live object update status
 * Input : - delta time (in microseconds) 
 * Exec : update energy, food and water based on status 
 * problem :the rand function is not random enough, and can give rise to a growth sprint of up to 5 or 6 nodes*/
void live_object::update_status(float dt_c) {
	float dt = dt_c * pow(10,-6);

	color[0] = DNA[15];
	color[1] = DNA[16];
	color[2] = DNA[17];

	energy -= DNA[4] * dt * node_count;
	temp += DNA[4] * dt * node_count;

	if (food > 0) {
		food -= DNA[5] * dt * node_count;
		energy += DNA[5] * dt * node_count;
	}

	if (water > 0) {
		water -= DNA[6] * dt * node_count;
		temp -= DNA[6] * dt * node_count;
	}

	if ( (float)(rand()%10000)*node_count/100 < DNA[9] && (energy > DNA[10]) ) { //grow plant
		this->grow(root_node);
		node_count = this->count_nodes(root_node, 1);
		energy -= 20.f;
	}

	if ( (float)(rand()%10000)/100 < DNA[7] * node_count && (energy > DNA[11]) ) { //reproduce
		this->reproduce();
	}

	//std::cout << "status update on : " << this << "  -- dt : " << dt << "\n";
	//std::cout << "  energy : " << energy << "\n  food : " << food << "\n  water : " << water << "\n  temp : " << temp << "\n nodes : " << node_count << "\n";

	//extract stuff from ground
	//TODO make this not random (or at least some kind of perlin noise)
	if(food < DNA[2])
		food  += (float)(rand() % 100 /10)*DNA[5] * dt ;
	if(water < DNA[3])
		water += (float)(rand() % 100 /10)*DNA[6] * dt ; 

	//eat branches when in need of energy, or die
	while (energy < 0){
		this->eat_branch();
		break;	
	}
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

/* METHOD
 * name : eat_branch
 * function : when in lack of energy the plant can eat one branch to regain some energy 
 * */
void live_object::eat_branch() {
	branch_node* node = &root_node;
	branch_node* last = &root_node;
	
	int next_node_index = 0;

	//TODO recount nodes
	node_count--; //this might break

	while (!node->con.empty()) {
		next_node_index = rand() % node->con.size(); //pick a random direction to follow
		last = node;
		node = (branch_node*)node->con[next_node_index];
	}

	//vector magic
	std::vector<void*>::iterator pos = last->con.begin() + next_node_index;

	last->con.erase(pos);
	if (node_count == 0) {
		this->~live_object(); //kill the plant
	} else {
		delete node;
	}
	energy += 15.0f;
	return;
}

/* METHOD
 * name : reproduce()
 * function : reproduce the plant, and create a new one
 * */
void live_object::reproduce() {
	live_object* offspring = new live_object;

	float offset[3] = { 
		(float)(rand() % 100 - 50), 
		0.f,
		(float)(rand() % 100 - 50)
	};

	offspring->root_node.pos[0] = this->root_node.pos[0] + offset[0];
	offspring->root_node.pos[1] = this->root_node.pos[1] + offset[1];
	offspring->root_node.pos[2] = this->root_node.pos[2] + offset[2];

	//add random color idk
	offspring->color[0] = (float)(rand() % 100) / 100;
	offspring->color[1] = (float)(rand() % 100) / 100;
	offspring->color[2] = (float)(rand() % 100) / 100;

	//share energy, food and water TODO
	offspring->energy = energy * DNA[12];
	energy = energy * (1.f - DNA[12]);
	offspring->food = food * DNA[13];
	food = food * (1.f - DNA[13]);
	offspring->water = water * DNA[14];
	water = water * (1.f - DNA[14]); 

	//TODO modify genetics
	for (int i = 0; i < DNA_max; i++){
		offspring->DNA[i] += ((float)(rand() % 100)/100 - 0.5) * DNA[0];
	}

}


