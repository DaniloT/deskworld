/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#ifndef GOCIRCLE_H_
#define GOCIRCLE_H_

#include "GameObject.h"

class GOCircle : public GameObject{
	float32 radius;
public:
	GOCircle(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic);
	virtual ~GOCircle();
	// Updates the objects.
	void Update();
	// Render the object.
	void Render();
	float32 GetRestitution();
	float32 GetFriction();
	float32 GetDensity();
	void SetRestitution(float32 rest);
	void SetFriction(float32 fric);
	void SetDensity(float32 dens);
};

#endif /* CIRCLE_H_ */
