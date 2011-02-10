/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 * Descricao: Classe que possui definicoes padroes.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <cstdio>
#include <cstdlib>
#include <SDL/SDL.h>

#define PIXELS_PER_METRE 30.0f

#define CONVERT(pix) (((float32)(pix))/PIXELS_PER_METRE)

#define PI 3.14159265

#define WIDTH 1024

#define HEIGHT 768

struct RGBAColor{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

enum GO_types{
	triangle =0,
	rectangle,
	circle,
	erase,
	freeform,
	WORLD,
	BARRIER,
	JOINT,
	MOTOR
};

typedef struct Point{
	int x;
	int y;
}point;


#endif /* COMMON_H_ */
