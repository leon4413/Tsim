//#define DEBUG

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

//self made libs - 
#include "global.h"
#include "model.h"
#include "ground.h"
#include "entity.h"
#include "input.h"
// ---

/* ## MAIN FUNCTION ## */
int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Vector Graphics");
	sf::Clock clock;
	sf::Time dt = sf::microseconds(0);

	if (FPS_LIMIT > 0){
		window.setFramerateLimit(FPS_LIMIT);
	}

	srand(seed);
	self_camera cam;

	live_object stuff; 


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
        sf::Event event;
        while (window.pollEvent(event)) {
			switch(event.type){

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if( event.key.code == sf::Keyboard::Escape ) window.close();
					break;

				default:
					break;
			}
        }


		/* -- Physiscs Engine -- */
		sf::Time dt_c = clock.restart();
		
		#ifdef DEBUG
		std::cout << dt_c.asMicroseconds() << " :: " << (1000000/dt_c.asMicroseconds()) << "\n";
		#endif

		dt += dt_c; //gen. time
		while (dt > sf::microseconds(0)) {

			dt = dt - sf::microseconds(1000); //eat time
		};

		/* Handle Keyboard */
		key_pressed(&cam, dt_c.asMicroseconds(), &window);

		/* -- Update Window content -- */
        //window.clear(sf::Color::Black);

		// Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// TODO : call every object render function
		/*for (int i = 0; i < live_array.size(); i++){
			live_array[i]->render();
		}*/

        // Set up the model-view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		float h_angle_d = -(cam.h_angle * 180)/PI;
		float v_angle_d = -(cam.v_angle * 180)/PI;
		glRotatef(h_angle_d, 0.f, 1.f, 0.f);
        glTranslatef(cam.pos[0], cam.pos[1], cam.pos[2]); 

        window.display();
    }

    return 0;
}
