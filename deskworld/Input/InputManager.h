/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * 	Danilo Gaby Andersen Trindade
 * 	Victor Sampaio Zucca
 *
 * Descricao: Classe que trata o input do jogo. Abstracao entre a SDL e o jogo.
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define CURSOR_ADDEVENT 25
#define CURSOR_MOVEEVENT 26
#define CURSOR_REMOVEEVENT 27
#define TIMELIMIT 500

#include "../Common.h"
#include "Tuio/TuioClient.h"
#include "Tuio/TuioListener.h"
#include "Tuio/TuioObject.h"
#include "../Graphics/ImageLoader.h"
#include <iostream>
#include <vector>
#include <map>

using namespace TUIO;
using namespace std;

typedef struct TUIOData{
	int x;
	int y;
	bool remove, tocou, destocou, tocando;
} TUIOData;

typedef struct Point{
	int x;
	int y;
}point;

typedef struct Click{
	int id;
	int x;
	int y;
	bool updated, remove;
	int time;
} Click;

class InputManager : public TuioListener {
	TUIOData* touch[10001];
	Uint8* keyState;
	Uint8 buttomState;
	int numIds, numIdsRem;
	int id[10001], idRem[10001];
	TuioClient* tuio_client;
	// Vectors that save state of mouse and keyboard input.
	bool keyDownState[400], keyUpState[400], buttomUpState[4], buttomDownState[4];
	InputManager* instance;
	InputManager();
public:
	vector<Click> click;
	multimap<int, point > xy;
	bool quit;
	bool motion_event;
	virtual ~InputManager();
	// Register events.
	void pollEvents();
	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isKeyPressed(int key);
	bool isMouseDown(int buttom);
	bool isMouseUp(int buttom);
	bool isMousePressed(int buttom);
	bool isMouseInside(ImageLoader* img);
	int mousePosX();
	int mousePosY();
	bool isTouched(int code);
	bool isTouching(int code);
	bool isTouchUp(int code);
	bool isTouchInside(ImageLoader* img, int code);
	int touchPosX(int code);
	int touchPosY(int code);
	InputManager* getInstance();

	// TuioListener methods
	void addTuioObject(TuioObject *tobj);
	void updateTuioObject(TuioObject *tobj);
	void removeTuioObject(TuioObject *tobj);

	void addTuioCursor(TuioCursor *tcur);
	void updateTuioCursor(TuioCursor *tcur);
	void removeTuioCursor(TuioCursor *tcur);

	void refresh(TuioTime ftime);

	int getNumIds();
	int getId(int pos);
};

#endif /* INPUTMANAGER_H_ */
