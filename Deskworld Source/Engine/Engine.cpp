/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#include "Engine.h"

Engine::Engine() {
}

Engine::~Engine() {
}

void Engine::Initialize(){
	gravity.Set(0.0, 0.0);
	doSleep = true;
	world = new b2World(gravity, doSleep);
	timestep.dt = 1.0/60.0;
	timestep.velocityIterations = 10;
	timestep.positionIterations = 10;

	b2BodyDef bodyDef;
	groundBody = world->CreateBody(&bodyDef);
	for(int i = 0 ; i < 10001 ; i++){
		mouseJoint[i] = NULL;
	}

}

Engine* Engine::getInstance(){
	static Engine *instance = NULL;
	if (instance == NULL) {
		instance = new Engine();
	}
	return(instance);
}

Object Engine::CreateLine(int posX, int posY, int distance, float32 angle, bool dynamic){
	Object obj;
	b2BodyDef bodyDef;

	if(dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(CONVERT(posX),CONVERT(posY));
	bodyDef.angle = angle;
	obj.body = world->CreateBody(&bodyDef);

	obj.shape.SetAsBox(CONVERT(distance)/2, 0.1/2);

	if(!dynamic){
		obj.body->CreateFixture(&obj.shape, 0.0);
	}else{
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1;
		fixtureDef.friction = 0.3;
		fixtureDef.shape = &obj.shape;

		obj.body->CreateFixture(&fixtureDef);
	}

	return obj;
}

Object Engine::CreateTriangle(int posX, int posY, vector<int> vx, vector<int> vy, bool dynamic){
	Object obj;
	b2BodyDef bodyDef;
	b2Vec2 vertices[3];

	if(dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(CONVERT(posX),CONVERT(posY));
	obj.body = world->CreateBody(&bodyDef);

	//Getting relative position for Box2D
	vertices[0].x = CONVERT(vx[0] - posX);
	vertices[0].y = CONVERT(vy[0] - posY);
	vertices[1].x = CONVERT(vx[1] - posX);
	vertices[1].y = CONVERT(vy[1] - posY);
	vertices[2].x = CONVERT(vx[2] - posX);
	vertices[2].y = CONVERT(vy[2] - posY);

	obj.shape.Set(vertices, 3);

	if(!dynamic){
		obj.body->CreateFixture(&obj.shape, 0.0);
	}else{
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1;
		fixtureDef.friction = 0.3;
		fixtureDef.restitution = 0.2;
		fixtureDef.shape = &obj.shape;

		obj.body->CreateFixture(&fixtureDef);
	}

	return obj;
}

Object Engine::CreateRectangle(int posX, int posY, int w, int h, bool dynamic){
	Object obj;
	b2BodyDef bodyDef;

	if(dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(CONVERT(posX),CONVERT(posY));
	obj.body = world->CreateBody(&bodyDef);

	if(w <= 1) w = 2;
	if(h <= 1) h = 2;

	obj.shape.SetAsBox(CONVERT(w)/2, CONVERT(h)/2);

	if(!dynamic){
		obj.body->CreateFixture(&obj.shape, 0.0);
	}else{
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1;
		fixtureDef.friction = 0.3;
		fixtureDef.restitution = 0.2;
		fixtureDef.shape = &obj.shape;

		obj.body->CreateFixture(&fixtureDef);
	}

	return obj;
}

Object Engine::CreateCircle(int posX, int posY, float32 radius, bool dynamic){
	Object obj;
	b2BodyDef bodyDef;
	b2CircleShape shape;

	if(dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(CONVERT(posX),CONVERT(posY));
	obj.body = world->CreateBody(&bodyDef);
	shape.m_radius = CONVERT(radius);

	if(!dynamic){
		obj.body->CreateFixture(&shape, 0.0);
	}else{
		b2FixtureDef fixtureDef;
		fixtureDef.density = 1;
		fixtureDef.friction = 0.3;
		fixtureDef.restitution = 0.2;
		fixtureDef.shape = &shape;

		obj.body->CreateFixture(&fixtureDef);
	}

	return obj;
}

Object Engine::CreatePolygon(Point p, vector<int> vx, vector<int> vy, bool dynamic){
	Object obj;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2Vec2* vertices = (b2Vec2*)malloc(sizeof(b2Vec2)*vx.size());

	if(dynamic)
		bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(CONVERT(p.x), CONVERT(p.y));
	obj.body = world->CreateBody(&bodyDef);
	int32 vcount = (int32) vx.size();

	if(dynamic){
		fixtureDef.density = 1;
		fixtureDef.friction = 0.3;
		fixtureDef.restitution = 0.2;
		int s = 33;
		fixtureDef.userData = &s;

		for(Uint32 i = 0 ; i < vx.size() ; i++){
			vertices[i].x = CONVERT(vx.at(i));
			vertices[i].y = CONVERT(vy.at(i));
		}
		obj.shape.Set(vertices, vcount);
		fixtureDef.shape = &obj.shape;
		obj.body->CreateFixture(&fixtureDef);
	} else{
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			vertices[i].x = CONVERT(vx.at(i));
			vertices[i].y = CONVERT(vy.at(i));
		}
		obj.shape.Set(vertices, vcount);
		obj.body->CreateFixture(&obj.shape, 0.0);
	}

	return obj;
}

Object Engine::CreateFreeform(vector<int> vx, vector<int> vy, float32 radius, bool dynamic){
	Object obj;
	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2FixtureDef fixtureDef;


	if(dynamic)
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(CONVERT(vx.at(0)),CONVERT(vy.at(0)));
	obj.body = world->CreateBody(&bodyDef);
	shape.m_radius = CONVERT(radius);

	if(dynamic){

		fixtureDef.density = 1;
		fixtureDef.friction = 0.3;
		fixtureDef.restitution = 0.2;

		//creating multiple shapes
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			shape.m_p.x = CONVERT(vx.at(i) - vx.at(0));
			shape.m_p.y = CONVERT(vy.at(i) - vy.at(0));
			fixtureDef.shape = &shape;
			obj.body->CreateFixture(&fixtureDef);
		}
	} else{
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			shape.m_p.x = CONVERT(vx.at(i) - vx.at(0));
			shape.m_p.y = CONVERT(vy.at(i) - vy.at(0));
			fixtureDef.shape = &shape;
			obj.body->CreateFixture(&shape, 0.0);
		}
	}
	return obj;
}


Object Engine::CreateBarrier(vector<Point> vertices){
	Object obj;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2Vec2 vertex[2];
	vertex[0].x = CONVERT(vertices[0].x);
	vertex[0].y = CONVERT(vertices[0].y);
	vertex[1].x = CONVERT(vertices[1].x);
	vertex[1].y = CONVERT(vertices[1].y);
	string b = "barrier";
	fixtureDef.userData = &b;

	obj.body = world->CreateBody(&bodyDef);
	obj.shape.SetAsEdge(vertex[0], vertex[1]);
	fixtureDef.shape = &obj.shape;
	obj.body->CreateFixture(&fixtureDef);

	return obj;
}

Object Engine::CreateWorld(vector<Point> vertices){
	Object obj;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2Vec2* b2vertices = (b2Vec2*)malloc(sizeof(b2Vec2)*vertices.size());
	bodyDef.active = false;
	obj.body = world->CreateBody(&bodyDef);

	fixtureDef.isSensor = true;

	for(Uint32 i = 0 ; i < vertices.size() ; i++){
		b2vertices[i].x = CONVERT(vertices[i].x);
		b2vertices[i].y = CONVERT(vertices[i].y);
	}
	obj.shape.Set(b2vertices, vertices.size());
	fixtureDef.shape = &obj.shape;
	obj.body->CreateFixture(&fixtureDef);

	return obj;
}

class QueryCallback : public b2QueryCallback{
public:
	QueryCallback(const b2Vec2& point)
	{
		m_point = point;
		m_fixture = NULL;
		staticBody = NULL;
	}

	bool ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body->GetType() == b2_dynamicBody)
		{
			bool inside = fixture->TestPoint(m_point);
			if (inside)
			{
				m_fixture = fixture;

				// We are done, terminate the query.
				return false;
			}
		}else{
			if(fixture->IsSensor())
				return true;
			staticBody = body;
			// We are done, terminate the query.
			return false;
		}

		// Continue the query.
		return true;
	}

	b2Body* staticBody;
	b2Vec2 m_point;
	b2Fixture* m_fixture;
};

void Engine::MouseDown(int xOrig, int yOrig, int id)
{
	b2Vec2 p(CONVERT(xOrig), CONVERT(yOrig));
	mouseWorld = p;

	if (mouseJoint[id] != NULL)
	{
		return;
	}

	// Make a small box.
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = p - d;
	aabb.upperBound = p + d;

	// Query the world for overlapping shapes.
	QueryCallback callback(p);
	world->QueryAABB(&callback, aabb);
	if (callback.m_fixture){
		b2Body* body = callback.m_fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = groundBody;
		md.bodyB = body;
		md.target = p;
		md.maxForce = 1000.0f * body->GetMass();
		mouseJoint[id] = (b2MouseJoint*)world->CreateJoint(&md);
		body->SetAwake(true);
	}
}

void Engine::DestroyMouseJoint(int id)
{
	world->DestroyJoint(mouseJoint[id]);
	mouseJoint[id] = NULL;
}

void Engine::DestroyObject(Object object){
	world->DestroyBody(object.body);
}

Object* Engine::EraseObject(int x, int y){
	b2Vec2 p(CONVERT(x), CONVERT(y));
	Object* obj = new Object();

	// Make a small box.
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = p - d;
	aabb.upperBound = p + d;

	// Query the world for overlapping shapes.
	QueryCallback callback(p);
	world->QueryAABB(&callback, aabb);

	if (callback.m_fixture){
		obj->body = callback.m_fixture->GetBody();
		return obj;
	}else if((callback.staticBody)){
		obj->body = callback.staticBody;
		return obj;
	}

	return NULL;
}

void Engine::Update(){
	world->Step(timestep.dt, timestep.velocityIterations, timestep.positionIterations);

	world->ClearForces();
}
