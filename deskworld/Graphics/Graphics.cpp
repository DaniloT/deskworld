/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Introducao ao Desenvolvimento de Jogos - 01/2010
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 * Turma: A
 *
 * Descricao: Desenha graficos complexos do jogo.
 */

#include "Graphics.h"

Graphics::Graphics() {
}

Graphics::~Graphics() {
	// TODO Auto-generated destructor stub
}

void Graphics::DrawPixel(SDL_Surface* screen, Uint16 x, Uint16 y, RGBAColor color){
	if(pixelRGBA(screen, (Sint16)x,(Sint16)y, color.r, color.g, color.b, color.a)==-1){
		printf("Error at DrawPixel\n");
	}

}

void Graphics::DrawLine(SDL_Surface* screen, Uint16 xOrigin, Uint16 yOrigin, Uint16 x, Uint16 y, RGBAColor color){
	if(lineRGBA(screen, (Sint16)xOrigin,(Sint16)yOrigin, (Sint16)x, (Sint16)y, color.r, color.g, color.b, color.a)==-1){
		printf("Error at DrawLine\n");
	}
}

void Graphics::DrawTriangle(SDL_Surface* screen, Uint16 x1, Uint16 y1, Uint16 x2, Uint16 y2, Uint16 x3, Uint16 y3, RGBAColor color){
	glColor4ub(color.r,color.g,color.b,color.a);
	glBegin(GL_TRIANGLES);
		//Draw our four points, clockwise.
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
		glVertex2i(x3,y3);
	glEnd();
}

void Graphics::DrawRectangle(SDL_Surface* screen, vector<Sint16> vx, vector<Sint16> vy, RGBAColor color){
	//Define the color
	glColor4ub(color.r,color.g,color.b,color.a);
	glBegin(GL_QUADS);
	  //Draw our four points, clockwise.
	  glVertex2i(vx.at(0), vy.at(0));
	  glVertex2i(vx.at(1), vy.at(1));
	  glVertex2i(vx.at(2), vy.at(2));
	  glVertex2i(vx.at(3), vy.at(3));
	glEnd();
}

void Graphics::DrawCircle(SDL_Surface* screen, Uint16 x, Uint16 y, Uint16 radius, RGBAColor color){
	GLUquadricObj *circle = gluNewQuadric ();

	glTranslatef((GLfloat) x, (GLfloat)y, 0);

	glColor4ub(color.r,color.g,color.b,color.a);
	gluQuadricDrawStyle (circle, GLU_FILL);
	gluQuadricNormals(circle, GLU_SMOOTH);
	gluDisk (circle,0,(GLdouble)radius,50,32);
	gluDeleteQuadric(circle);

	glLoadIdentity();
}

void Graphics::DrawPolygon(SDL_Surface* screen, vector<Sint16> vx, vector<Sint16> vy, int n, RGBAColor color){
	glColor4ub(color.r,color.g,color.b,color.a);
	glBegin(GL_POLYGON);
		for(int i = 0 ; i < n ; i++){
			glVertex2i(vx.at(i), vy.at(i));
		}
	glEnd();
}

Graphics* Graphics::getInstace(){
	static Graphics *instance = NULL;
	if (instance == NULL) {
		instance = new Graphics();
	}
	return(instance);
}
