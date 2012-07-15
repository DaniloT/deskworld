/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Box2D/Box2D.h"
#include "../Common.h"

#include <string>
#include <vector>

using namespace std;

struct Object{
	b2Body* body;
	b2PolygonShape shape;
};

class Engine {
	b2Vec2 gravity;
	b2World* world;
	bool doSleep;
	Engine* instance;
	Engine();
	b2TimeStep timestep;
	b2Vec2 mouseWorld;
	b2Body* groundBody;
public:
	b2MouseJoint* mouseJoint[10001];
	virtual ~Engine();
	void Initialize();
	Engine* getInstance();
	Object CreateLine(int posX, int posY, int distance, float32 angle, bool dynamic);
	Object CreateTriangle(int posX, int posY, vector<int> vx, vector<int> vy, bool dynamic);
	Object CreateRectangle(int posX, int posY, int w, int h, bool dynamic);
	Object CreateCircle(int posX, int posY, float32 radius, bool dynamic);
	Object CreatePolygon(Point p, vector<int> vx, vector<int> vy, bool dynamic);
	Object CreateFreeform(vector<int> vx, vector<int> vy, float32 radius, bool dynamic);
	Object CreateWorld(vector<Point> vertices);
	Object CreateBarrier(vector<Point> vertices);
	void MouseDown(int xOrig, int yOrig, int id);
	void DestroyMouseJoint(int id);
	void DestroyObject(Object object);
	Object* EraseObject(int x, int y);
	void Update();
};

#endif /* ENGINE_H_ */
