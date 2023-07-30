#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

#include "ground.h"
#include "global.h"


/*
float pos[3];
int phy; // 0 to 2*PI
int theta; // 0 to PI
int max;

float** height_map;

void gen_surface(int phy, int theta, int max);
void print_surface();
void random_fill();
void filter_pass();
void render();
*/

void planet::gen_surface(int p, int t, int f_pass, int cutoff, int z_max, int z_min) {
	pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 0.0f;

	phy = t;
	theta = t;

	height_map = (float**)malloc( p * sizeof(int*));
	for(int i = 0; i < phy; i++){
		height_map[i] = (float*)malloc( t * sizeof(float));
	}

	//this bit fills the array with random numbers
	this->random_fill(z_max, z_min);

	//this bit is the fileter, it makes an average over every position
	for(int p = 1; p <= f_pass; p++){
		filter_pass();
	};

	this->cut_off((float)cutoff);

};

void planet::print_surface(){
	std::cout << " dim : " << phy << " " << theta << "\n";
	for(int i = 0; i < phy; i++){
		for(int j = 0; j < theta; j++){
			std::cout << height_map[i][j] << " ";
		}
		std::cout << "\n";
	}

};

void planet::random_fill(int z_max, int z_min){
	for(int i = 0; i < phy; i++){
		for(int j = 0; j < theta; j++){

			float h = ((float)(rand() % (z_max * 100)) / 100.0 ) + 1.0f;
			if (h < z_min) h = z_min;

			height_map[i][j] = h;
		}
	}
};

void planet::filter_pass(){
	std::cout << "starting filter pass\n";

	for(int i = 0; i < phy; i++){
		for(int j = 0; j < theta; j++){
			if (i == 0) {
				if (j == 0) {
					height_map[i][j] = (float)((height_map[i][j] + height_map[i+1][j] + height_map[i][j+1])/3);
				} else if (j == (theta-1)){
					height_map[i][j] = (float)((height_map[i][j] + height_map[i+1][j] + height_map[i][j-1])/3);
				} else {
					height_map[i][j] = (float)((height_map[i][j] + height_map[i+1][j] + height_map[i][j+1] + height_map[i][j-1])/4);
				}
			} else if (i == (phy-1)){
				if (j == 0) {
					height_map[i][j] = (float)((height_map[i][j] + height_map[i-1][j] + height_map[i][j+1])/3);
				} else if (j == (theta-1)){
					height_map[i][j] = (float)((height_map[i][j] + height_map[i-1][j] + height_map[i][j-1])/3); 
				} else {
					height_map[i][j] = (float)((height_map[i][j] + height_map[i-1][j] + height_map[i][j+1] + height_map[i][j-1])/4);
				}
			} else {
				if (j == 0) {
					height_map[i][j] = (float)((height_map[i][j] + height_map[i-1][j] + height_map[i+1][j] + height_map[i][j+1])/4);
				} else if (j == (theta-1)){
					height_map[i][j] = (float)((height_map[i][j] + height_map[i-1][j] + height_map[i+1][j]  + height_map[i][j-1])/4); 
				} else {
					height_map[i][j] = (float)((height_map[i][j] + height_map[i-1][j] + height_map[i+1][j] + height_map[i][j+1] + height_map[i][j-1])/5);
				}
			}
		}
	}

	std::cout << "filter pass ended\n";
};

void planet::cut_off(float cut) {
	for(int i = 0; i < phy; i++){
		for(int j = 0; j < theta; j++){
			if (height_map[i][j] > cut) height_map[i][j] = cut;
		}
	}
}

void planet::render(){
	int i_max = MAP_X_MAX;
	int j_max = MAP_Y_MAX;

	glColor3f(0.0f, 1.0f, 0.0f);

	//Linee verticali
	for(int i = 0; i < i_max; i++){
		glBegin(GL_LINE_STRIP);
		for(int j = 0; j < j_max; j++){
			glVertex3f(
			  (pos[0] + this->height_map[i][j] * cos( i * (2*PI / phy)) * sin( j * (PI / theta)) ) * scale, 
			  (pos[2] + this->height_map[i][j] * cos( j * (PI / theta)) ) * scale,
			  (pos[1] + this->height_map[i][j] * sin( i * (2*PI / phy)) * sin( j * (PI / theta)) ) * scale
			);
		}
		glEnd();
	}

	//linee orizzontali
	for(int j = 0; j < j_max; j++){
		glBegin(GL_LINE_LOOP);
		for(int i = 0; i < i_max; i++){
			glVertex3f(
			  (pos[0] + this->height_map[i][j] * cos( i * (2*PI / phy)) * sin( j * (PI / theta)) ) * scale, 
			  (pos[2] + this->height_map[i][j] * cos( j * (PI / theta)) ) * scale,
			  (pos[1] + this->height_map[i][j] * sin( i * (2*PI / phy)) * sin( j * (PI / theta)) ) * scale
			);
		}
		glEnd();
	}

};


/* 
 * ----- GROUND ------ 
 */


void ground::gen_ground(int x, int y, int max) {

	dim_x = x;
	dim_y = y;
	dim_max = max;

	// this bit is to create a 2d array starting form unknown dimensions
	height_map = (int**)malloc( x * sizeof(int*));
	for(int i = 0; i < x; i++){
		height_map[i] = (int*)malloc( y * sizeof(int));
	}

	//this bit fills the array with random numbers
	this->random_fill();

	//this bit is the fileter, it makes an average over every position
	for(int p = 1; p <= FILTER_PASS; p++){
		filter_pass();
	};
};

void ground::print_ground() {
	std::cout << " dim : " << dim_x << " " << dim_y << "\n";
	for(int i = 0; i < dim_x; i++){
		for(int j = 0; j < dim_y; j++){
			std::cout << height_map[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void ground::random_fill() {
	for(int i = 0; i < dim_x; i++){
		for(int j = 0; j < dim_y; j++){

			int h = rand() % dim_max;
			height_map[i][j] = h;
		}
	}
}

void ground::filter_pass() {
	for(int i = 0; i < dim_x; i++){
		for(int j = 0; j < dim_y; j++){
			std::cout << "current h : " << height_map[i][j];
			if (i == 0) {
				if (j == 0) {
					height_map[i][j] = (int)((height_map[i][j] + height_map[i+1][j] + height_map[i][j+1])/3);
				} else if (j == (dim_y-1)){
					height_map[i][j] = (int)((height_map[i][j] + height_map[i+1][j] + height_map[i][j-1])/3);
					std::cout << " -- --  B  -- -- ";
				} else {
					height_map[i][j] = (int)((height_map[i][j] + height_map[i+1][j] + height_map[i][j+1] + height_map[i][j-1])/4);
				}
			} else if (i == (dim_x-1)){
				if (j == 0) {
					height_map[i][j] = (int)((height_map[i][j] + height_map[i-1][j] + height_map[i][j+1])/3);
				} else if (j == (dim_y-1)){
					height_map[i][j] = (int)((height_map[i][j] + height_map[i-1][j] + height_map[i][j-1])/3); 
					std::cout << " -- --  A  -- -- ";
				} else {
					height_map[i][j] = (int)((height_map[i][j] + height_map[i-1][j] + height_map[i][j+1] + height_map[i][j-1])/4);
				}
			} else {
				if (j == 0) {
					height_map[i][j] = (int)((height_map[i][j] + height_map[i-1][j] + height_map[i+1][j] + height_map[i][j+1])/4);
				} else if (j == (dim_y-1)){
					height_map[i][j] = (int)((height_map[i][j] + height_map[i-1][j] + height_map[i+1][j]  + height_map[i][j-1])/4); 
					std::cout << " -- --  C  -- -- ";
				} else {
					height_map[i][j] = (int)((height_map[i][j] + height_map[i-1][j] + height_map[i+1][j] + height_map[i][j+1] + height_map[i][j-1])/5);
				}
			}
			std::cout << "  now : " << height_map[i][j] << "  i: " << i << "  j: " << j << "\n";
		}
	}
}


void ground::render() {
	int i_max = MAP_X_MAX;
	int j_max = MAP_Y_MAX;

	glColor3f(0.0f, 1.0f, 0.0f);

	for(int i = 0; i < i_max; i++){
		glBegin(GL_LINE_STRIP);
		for(int j = 0; j < j_max; j++){
			glVertex3f(i * scale , this->height_map[i][j]  ,j * scale);
		}
		glEnd();
	}

	for(int j = 0; j < j_max; j++){
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i < i_max; i++){
			glVertex3f(i * scale , this->height_map[i][j]  ,j * scale);
		}
		glEnd();
	}
}

void ground::renderf() {
	int i_max = MAP_X_MAX;
	int j_max = MAP_Y_MAX;


	for(int i = 0; i < (i_max -1); i++){
		for(int j = 0; j < (j_max -1); j++){
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			GLfloat light_pos[] = {0.0f, 0.0f, 30.0f};
			glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

			GLfloat material_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			GLfloat material_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
			GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat material_shininess = 100.0f;

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);

			glBegin(GL_QUADS);

			glVertex3f(i * scale , this->height_map[i][j]  ,j * scale);
			glVertex3f((i +1) * scale , this->height_map[i+1][j]  ,j * scale);
			glVertex3f((i +1) * scale , this->height_map[i+1][j+1]  ,(j +1) * scale);
			glVertex3f(i * scale , this->height_map[i][j+1]  ,(j +1) * scale);

			glEnd();

			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}
	}

}
