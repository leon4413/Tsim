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

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {cam->vel[1] += cam_speed * (dt);};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { if (PHY_RUNNING) {PHY_RUNNING = false;} else {PHY_RUNNING = true;};};


	/* integro il movimento del mouse per ottenere la direzione corrente della telecamera
	 * Funziona anche per il movimento verticale, anche se la telecamera ancora non lo supporta
	 * Continua a funzionare anche in background, TODO: sistemare */
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);

	cam->h_angle += -(mouse_pos.x - cam->mouse_pos_int.x) * cam_sensitivity;
	cam->v_angle += -(mouse_pos.y - cam->mouse_pos_int.y) * cam_sensitivity;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {cam->h_angle -= cam_sensitivity * 100.0;};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  {cam->h_angle += cam_sensitivity * 100.0;};

	cam->mouse_pos_int = mouse_pos;
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
