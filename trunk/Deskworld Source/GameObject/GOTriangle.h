/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#ifndef GOTRIANGLE_H_
#define GOTRIANGLE_H_

#include "GameObject.h"

class GOTriangle : public GameObject{
public:
	GOTriangle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic);
	virtual ~GOTriangle();
	// Updates triangle position.
	void Update();
	// Render the triangle.
	void Render();
	float32 GetRestitution();
	float32 GetFriction();
	float32 GetDensity();
	void SetRestitution(float32 rest);
	void SetFriction(float32 fric);
	void SetDensity(float32 dens);
};

#endif /* TRIANGLE_H_ */
