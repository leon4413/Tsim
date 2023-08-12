//self made libs - 
#include "global.h"
#include "input.h"
#include "entity.h"
// ---

debug console; //cheecky stuff eheheh (defindef in global.h)

/* ## MAIN FUNCTION ## */
int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Vector Graphics");
	sf::Clock clock;
	sf::Time dt = sf::microseconds(0);

	if (FPS_LIMIT > 0){
		window.setFramerateLimit(FPS_LIMIT);
	}

	srand(seed);
    camera_object cam;

	/* test plant */
	live_object test;
	test.root_node.pos[0] = 0.f;
	test.root_node.pos[1] = 0.f;
	test.root_node.pos[2] = -100.f;

	test.root_node.add_node_pos(0.0f, 10.f, -100.0f);

	test.color[0] = 0.f;
	test.color[2] = 0.f;
	/* -- test plant -- */


    // Set up OpenGL states
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, cam_depth);

	/* +++ MAIN LOOP +++ */
    while (window.isOpen()) {

		/* -- Event Loop -- */
		event_check(&window);

		/* -- Physiscs Engine -- */
		sf::Time dt_c = clock.restart();
		
		dt += dt_c; //gen. time
		//physics cycle
		while (dt > sf::microseconds(0)) {

			dt = dt - sf::microseconds(PHY_TICK); //eat time

			console.log("physics cycle");

			for (int i = 0; i < (int)object_array.size(); i++){
				((real_object*)object_array[i])->update_status(PHY_TICK);
			}

		};

		/* Handle Keyboard */
		key_pressed(&cam, dt_c.asMicroseconds(), &window);

		/* -- Update Window content -- */
        window.clear(sf::Color::Black);

		// Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set up the model-view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		float h_angle_d = -(cam.h_angle * 180)/PI;
		//float v_angle_d = -(cam.v_angle * 180)/PI;
		glRotatef(h_angle_d, 0.f, 1.f, 0.f);
        glTranslatef(cam.pos[0], cam.pos[1], cam.pos[2]); 

		// TODO : call every object render function
		for (int i = 0; i < (int)object_array.size(); i++){
			((real_object*)object_array[i])->render();
		}

        window.display();
    }

    return 0;
}
