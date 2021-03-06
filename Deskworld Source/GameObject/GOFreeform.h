/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#ifndef GOFREEFORM_H_
#define GOFREEFORM_H_

#include "GameObject.h"

class GOFreeform : public GameObject{
	float32 thickness;
public:
	GOFreeform(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic, float32 thickness);
	virtual ~GOFreeform();
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

#endif /* FREEFORM_H_ */
