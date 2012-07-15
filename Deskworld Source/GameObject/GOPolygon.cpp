/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 *
 */

#include "GOPolygon.h"


//positive signed area means counter clockwise
//negative signed area means clockwise.
bool SignedAreaIsPositive(vector<int> vx, vector<int> vy){
	b2Vec2 centroid;
	float signedArea = 0;
	int x0 = 0; // Current vertex X
	int y0 = 0; // Current vertex Y
	int x1 = 0; // Next vertex X
	int y1 = 0; // Next vertex Y
	int a = 0; // Partial signed area

	Uint32 i = 0;
	// For all vertices except last
	for (i=0; i < vx.size() - 1; i++){
		x0 = vx.at(i);
		y0 = vy.at(i);
		x1 = vx.at(i+1);
		y1 = vy.at(i+1);
		a = x0*y1 - x1*y0;
		signedArea += a;
		centroid.x += (x0 + x1)*a;
		centroid.y += (y0 + y1)*a;
	}

	// Do last vertex
	x0 = vx.at(i);
	y0 = vy.at(i);
	x1 = vx.at(0);
	y1 = vy.at(0);
	a = x0*y1 - x1*y0;
	signedArea += a;
	centroid.x += (x0 + x1)*a;
	centroid.y += (y0 + y1)*a;

	signedArea *= 0.5;
	centroid.x /= (6*signedArea);
	centroid.y /= (6*signedArea);

	return (signedArea > 0.0);
}

Point calculatePolygonCenter(vector<int> vx, vector<int> vy){
	Point p;
	double area = 0.0;
	int j = 0;
	int i = 0;
	for(i = 0; i < vx.size(); i++){
		j = (i+1) % vx.size();
		area += vx[i] * vy[j];
		area -= vy[i] * vx[j];
	}
	area /= 2.0;

	double cx, cy;
	cx = 0.0;
	cy = 0.0;
	double A = area;
	i = 0;
	j = 0;
	double factor = 0.0;
	for(i = 0; i < vx.size(); i++){
	j = (i+1) % vx.size();
	factor = (vx[i]*vy[j] - vx[j]*vy[i]);
	cx += (vx[i] + vx[j])*factor;
	cy += (vy[i] + vy[j])*factor;
	}
	A *= 6.0f;
	factor = 1/A;
	cx *= factor;
	cy *= factor;
	p.x = (int)cx;
	p.y = (int)cy;
	return p;
}

/*
   * Assuming the polygon is simple, checks
   * if it is convex.
   */
bool GOPolygon::isConvex(){
    bool isPositive = false;
    for (int i=0; i < vx.size(); ++i){
		int lower = (i==0)?(vx.size()-1):(i-1);
		int middle = i;
		int upper = (i == (vx.size()-1))?(0):(i+1);
		float dx0 = vx[middle]-vx[lower];
		float dy0 = vy[middle]-vy[lower];
		float dx1 = vx[upper]-vx[middle];
		float dy1 = vy[upper]-vy[middle];
		float cross = dx0*dy1-dx1*dy0;
		//Cross product should have same sign
		//for each vertex if poly is convex.
		bool newIsP = (cross>0)?true:false;
		if (i==0){
			isPositive = newIsP;
		} else if (isPositive != newIsP){
			return false;
		}
    }
    return true;
}

GOPolygon::GOPolygon(vector<int> vx, vector<int> vy, RGBAColor color, bool dynamic) {
	engine = engine->getInstance();
	this->color = color;
	this->dynamic = dynamic;


	if (!SignedAreaIsPositive(vx, vy)){
		vector<int>::reverse_iterator rx = vx.rbegin(), ry = vy.rbegin();
		vector<int> rvx, rvy;
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			rvx.push_back((*rx));
			rvy.push_back((*ry));
			++rx;
			++ry;
		}
		this->vx = rvx;
		this->vy = rvy;
	}else{
		this->vx = vx;
		this->vy = vy;
	}
	if(this->isConvex()){
		convex = true;
		Point p = calculatePolygonCenter(this->vx, this->vy);
		object = engine->CreatePolygon(p, this->vx, this->vy, dynamic);
	}else{
		convex = false;
	}

}

void GOPolygon::set(GOPolygon p){
    this->vx = p.vx;
    this->vy = p.vy;
}

GOPolygon::~GOPolygon() {
	engine->DestroyObject(this->object);
}

void GOPolygon::Update(){
	if(dynamic){
		for(Uint32 i = 0 ; i < vx.size() ; i++){
			vx.at(i) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(i)).x)*PIXELS_PER_METRE);
			vy.at(i) = (int)((object.body->GetWorldPoint(object.shape.GetVertex(i)).y)*PIXELS_PER_METRE);
		}
	}
}

void GOPolygon::Render(){
	graphics->DrawPolygon(vx, vy, vx.size(), color);
}
