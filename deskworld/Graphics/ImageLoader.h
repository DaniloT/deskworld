/*
 * ImageLoader.h
 *
 *  Created on: 21/01/2011
 *      Author: Zucca
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
	int w, h;
	GLuint texture; //this is a handle to our texture object
public:
	int x,y;
	ImageLoader(string fileName, int x, int y);
	virtual ~ImageLoader();
	void Render(SDL_Surface *screen);
	// Moves the sprites position on screen.
	void UpdatePos(int x, int y);
	// Returns the sprites rectangle
	SDL_Rect GetRect();
};

#endif /* ImageLoader_H_ */