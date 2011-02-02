/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 * Descricao: Desenha graficos complexos do jogo.
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Input/InputManager.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "../Common.h"

#include <vector>

class Graphics {
	Graphics* instance;
	Graphics();
public:
	virtual ~Graphics();
	void DrawPixel(SDL_Surface* screen,int x, int y, RGBAColor color);
	void DrawLine(SDL_Surface* screen,int xOrigin, int yOrigin, int x, int y, RGBAColor color);
	void DrawTriangle(SDL_Surface* screen,int x1, int y1, int x2, int y2, int x3, int y3, RGBAColor color);
	void DrawRectangle(SDL_Surface* screen, vector<int> vx, vector<int> vy, RGBAColor color);
	void DrawCircle(SDL_Surface* screen, int vx, int vy, int r, RGBAColor color);
	void DrawPolygon(SDL_Surface* screen, vector<int> vx, vector<int> vy, int n, RGBAColor color);
	Graphics* getInstance();
};

#endif /* GRAPHICS_H_ */
