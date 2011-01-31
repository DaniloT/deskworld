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
 * Descricao: Classe que possui definicoes padroes.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <cstdio>
#include <cstdlib>
#include <SDL/SDL.h>

#define PIXELS_PER_METRE 30.0f

#define CONVERT(pix) (((float32)(pix))/PIXELS_PER_METRE)

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
	freeform
};


#endif /* COMMON_H_ */
