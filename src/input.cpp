#include "global.h"
#include "input.h"

void key_pressed(camera_object* cam, float dt_c, sf::Window* window){
	float dt = dt_c * pow(10, -6);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {cam->pos[0] += cam_speed * (dt) * cos(cam->h_angle); cam->pos[2] += cam_speed * (dt) * sin(-cam->h_angle);};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {cam->pos[0] -= cam_speed * (dt) * cos(cam->h_angle); cam->pos[2] -= cam_speed * (dt) * sin(-cam->h_angle);};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {cam->pos[1] += cam_speed * (dt);};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {cam->pos[1] -= cam_speed * (dt);};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {cam->pos[0] -= cam_speed * (dt) * sin(cam->h_angle); cam->pos[2] -= cam_speed * (dt) * cos(cam->h_angle);};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {cam->pos[0] += cam_speed * (dt) * sin(cam->h_angle); cam->pos[2] += cam_speed * (dt) * cos(cam->h_angle);};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {cam->vel[1] += cam_speed * (dt);};


	/* Da fixare! devo integrare il movimento del mouse per ottenere lo spostamento desiderato
	 * su tutto lo schermo !*/
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	sf::Mouse::setPosition(sf::Vector2i(50,50), *window);

	cam->h_angle += -(mouse_pos.x - 50) * cam_sensitivity;
	cam->v_angle += -(mouse_pos.y - 50) * cam_sensitivity;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {cam->h_angle -= cam_sensitivity * 100.0;};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  {cam->h_angle += cam_sensitivity * 100.0;};


}

void event_check(sf::Window* window) {
	sf::Event event;
	while (window->pollEvent(event)) {
		switch(event.type){

		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyPressed:
			//check if esc is pressed
			if( event.key.code == sf::Keyboard::Escape ) window->close();
			break;

		default:
			break;
		}
	}
};
