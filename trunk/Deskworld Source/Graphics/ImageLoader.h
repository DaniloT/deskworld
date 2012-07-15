/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <cstdio>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_opengl.h>

using namespace std;

class ImageLoader {
	int w, h;		//width and height of image
	GLuint texture; //this handle our texture object
	GLUquadricObj *quadratic; // quad
public:
	int x,y;
	ImageLoader(string fileName, int x, int y);
	virtual ~ImageLoader();
	void Render();
	// Moves the sprites position on screen.
	void UpdatePos(int x, int y);
	// Returns the sprites rectangle
	SDL_Rect GetRect();
};

#endif /* ImageLoader_H_ */
