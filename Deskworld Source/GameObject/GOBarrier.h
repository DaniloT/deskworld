/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#ifndef GOBARRIER_H_
#define GOBARRIER_H_

#include "GameObject.h"

class GOBarrier : public GameObject{
public:
	GOBarrier(vector<int> vx, vector<int> vy, RGBAColor color);
	virtual ~GOBarrier();
	void Update();
	void Render();
};

#endif /* GOBARRIER_H_ */
