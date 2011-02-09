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
	//Enable Color Transparency
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_SMOOTH);

	glViewport(0, 0, WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
}

Graphics::~Graphics() {
	// TODO Auto-generated destructor stub
}


void Graphics::DrawLine(int xOrigin, int yOrigin, int x, int y, RGBAColor color){
	glColor4ub(color.r,color.g,color.b,color.a);
	glBegin(GL_LINE);
		glVertex2i(xOrigin,yOrigin);
		glVertex2i(x,y);
	glEnd();
}

void Graphics::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBAColor color){
	glColor4ub(color.r,color.g,color.b,color.a);
	glBegin(GL_TRIANGLES);
		//Draw our four points, clockwise.
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
		glVertex2i(x3,y3);
	glEnd();
}

void Graphics::DrawRectangle(vector<int> vx, vector<int> vy, RGBAColor color){
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

void Graphics::DrawCircle(int x, int y, int radius, RGBAColor color){
	GLUquadricObj *circle = gluNewQuadric ();

	glTranslatef((GLfloat) x, (GLfloat)y, 0);

	glColor4ub(color.r,color.g,color.b,color.a);
	gluQuadricDrawStyle (circle, GLU_FILL);
	gluQuadricNormals(circle, GLU_SMOOTH);
	gluDisk (circle,0,(GLdouble)radius,50,32);
	gluDeleteQuadric(circle);

	glLoadIdentity();
}

void Graphics::DrawPolygon(vector<int> vx, vector<int> vy, int n, RGBAColor color){
	glColor4ub(color.r,color.g,color.b,color.a);
	glBegin(GL_POLYGON);
		for(int i = 0 ; i < n ; i++){
			glVertex2i(vx.at(i), vy.at(i));
		}
	glEnd();
}

Graphics* Graphics::getInstance(){
	static Graphics *instance = NULL;
	if (instance == NULL) {
		instance = new Graphics();
	}
	return(instance);
}
