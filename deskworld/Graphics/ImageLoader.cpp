/*
 * ImageLoader.cpp
 *
 *  Created on: 21/01/2011
 *      Author: Zucca
 */

#include "ImageLoader.h"

ImageLoader::ImageLoader(string fileName, int x, int y) {
	this->x = x;
	this->y = y;

	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLenum texture_format;
	GLint  nOfColors;

	if ( (surface = IMG_Load(fileName.c_str())) ) {
		w = surface->w;
		h = surface->h;

		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
				if (surface->format->Rmask == 0x000000ff)
						texture_format = GL_RGBA;
				else
						texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
				if (surface->format->Rmask == 0x000000ff)
						texture_format = GL_RGB;
				else
						texture_format = GL_BGR;
		} else {
				printf("Warning: the image is not truecolor.\n");
		}

		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );

        SDL_LockSurface(surface);

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
	                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );

		SDL_UnlockSurface(surface);

		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	}else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	// Free the SDL_Surface only if it was successfully created
	if ( surface ) {
		SDL_FreeSurface( surface );
	}
}

ImageLoader::~ImageLoader() {
	glDeleteTextures(1,&texture);
}

void ImageLoader::Render(){

	glBindTexture( GL_TEXTURE_2D, texture );
	glEnable( GL_TEXTURE_2D );

	glMatrixMode( GL_MODELVIEW );

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		//Top-left vertex (corner)
		glTexCoord2i( 0, 0 );
		glVertex2i(x, y);

		//Top-right vertex (corner)
		glTexCoord2i( 1, 0 );
		glVertex2i(x + w, y);

		//Bottom-right vertex (corner)
		glTexCoord2i( 1, 1 );
		glVertex2i(x + w, y + h);

		//Bottom-left vertex (corner)
		glTexCoord2i( 0, 1 );
		glVertex2i(x , y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void ImageLoader::UpdatePos(int x, int y){
	this->x = x;
	this->y = y;
}

SDL_Rect ImageLoader::GetRect(){
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}
