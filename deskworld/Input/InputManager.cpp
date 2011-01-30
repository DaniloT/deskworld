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

#include "InputManager.h"
#include <iostream>

InputManager::InputManager() {
	keyState = SDL_GetKeyState(NULL);

	memset(keyDownState, false, sizeof(keyDownState));
	memset(keyUpState, false, sizeof(keyUpState));
	memset(buttomDownState, false, sizeof(buttomDownState));
	memset(buttomUpState, false, sizeof(buttomUpState));

	quit = false;

	tuio_client = new TuioClient(3333);
	tuio_client->addTuioListener(this);
	tuio_client->connect();
}

InputManager::~InputManager() {
	tuio_client->disconnect();
	delete instance;
}

void InputManager::pollEvents() {
	SDL_Event event;
	TUIOData* data;

	memset(keyDownState, false, sizeof(keyDownState));
	memset(keyUpState, false, sizeof(keyUpState));
	memset(buttomDownState, false, sizeof(buttomDownState));
	memset(buttomUpState, false, sizeof(buttomUpState));
	for(it = touch.begin(); it != touch.end(); it++){
		if (it->second->remove){
			touch.erase(it);
		} else {
			it->second->tocou = false;
			it->second->destocou = false;
		}
	}
	motion_event = false;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_KEYDOWN) {
			keyDownState[event.key.keysym.sym] = 1;
		}else if(event.type == SDL_KEYUP){
			keyUpState[event.key.keysym.sym] = 1;
		}else if(event.type == CURSOR_ADDEVENT){
			data = (TUIOData*)event.user.data1;
			data->tocou = true;
			data->tocando = true;
			touch.insert(pair<Sint16,TUIOData*>(data->id,data));
		}else if(event.type == CURSOR_REMOVEEVENT){
			data = (TUIOData*)event.user.data1;
			touch[data->id]->destocou = true;
			touch[data->id]->tocando = false;
			touch[data->id]->x = data->x;
			touch[data->id]->y = data->y;
			touch[data->id]->remove = true;
		}else if(event.type == CURSOR_MOVEEVENT){
			data = (TUIOData*)event.user.data1;
			point temp;
			temp.x = data->x;
			temp.y = data->y;
			xy.insert(pair<Sint16, point >(data->id, temp ));
			touch[data->id]->x = data->x;
			touch[data->id]->y = data->y;
			motion_event = true;
		}else if(event.type == SDL_MOUSEBUTTONDOWN){
			buttomDownState[event.button.button] = 1;
			data = (TUIOData*) malloc(sizeof(TUIOData));
			data->tocou = true;
			data->tocando = true;
			data->destocou = false;
			data->remove = false;
			data->x = event.button.x;
			data->y = event.button.y;
			data->id = 10000;
			touch.insert(pair<Sint16,TUIOData*>(data->id,data));
		}else if(event.type == SDL_MOUSEBUTTONUP){
			buttomUpState[event.button.button] = 1;
			touch[10000]->tocando = false;
			touch[10000]->destocou = true;
			touch[10000]->x = event.button.x;
			touch[10000]->y = event.button.y;
			touch[10000]->remove = true;
		}else if(event.type == SDL_MOUSEMOTION){
			it = touch.find(10000);
			if(it != touch.end()){
				touch[10000]->x = event.button.x;
				touch[10000]->y = event.button.y;
				motion_event = true;
			}
		}else if(event.type == SDL_QUIT){
			quit = true;
		}
	}
}

bool InputManager::isKeyDown(int key){
	if(keyDownState[key] == true) {
		return true;
	}else{
		return false;
	}
}

bool InputManager::isKeyUp(int key){
	if(keyUpState[key]) {
		return true;
	}else{
		return false;
	}
}

bool InputManager::isKeyPressed(int key){
	if(keyState[key]){
		return true;
	}else{
		return false;
	}
}

bool InputManager::isMouseDown(int buttom){
	if(buttomDownState[buttom]) {
		return true;
	}else{
		return false;
	}
}

bool InputManager::isMouseUp(int buttom){
	if(buttomUpState[buttom]) {
		return true;
	}else{
		return false;
	}
}

bool InputManager::isMousePressed(int buttom){
	if((SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(buttom))){
		return true;
	}else{
		return false;
	}
}

bool InputManager::isMouseInside(ImageLoader* img){
	if((touch[10000]->x < img->x)||(touch[10000]->x > (img->x+img->GetRect().w)))
		return false;
	else if((touch[10000]->y < img->y)||(touch[10000]->y > (img->y+img->GetRect().h)))
		return false;
	else
		return true;
}

Sint16 InputManager::mousePosX(){
	return touch[10000]->x;
}

Sint16 InputManager::mousePosY(){
	return touch[10000]->y;
}

// Singleton that guarantees there is only one Instance of Input Manager
InputManager* InputManager::getInstance(){
	static InputManager *instance = NULL;
	if (instance == NULL) {
		instance = new InputManager();
	}
	return(instance);
}

bool InputManager::isTouched(int code){
	return touch[code]->tocou;
}

bool InputManager::isTouching(int code){
	return touch[code]->tocando;
}

bool InputManager::isTouchUp(int code){
	return touch[code]->destocou;
}

bool InputManager::isTouchInside(ImageLoader* img, int code){
	if((touch[code]->x < img->x)||(touch[code]->x > (img->x+img->GetRect().w)))
		return false;
	else if((touch[code]->y < img->y)||(touch[code]->y > (img->y+img->GetRect().h)))
		return false;
	else
		return true;
}

Sint16 InputManager::touchPosX(int code){
	return touch[code]->x;
}

Sint16 InputManager::touchPosY(int code){
	return touch[code]->y;
}

// TuioListener methods
void InputManager::addTuioObject(TuioObject *tobj){

}

void InputManager::updateTuioObject(TuioObject *tobj){

}

void InputManager::removeTuioObject(TuioObject *tobj){

}

void InputManager::addTuioCursor(TuioCursor *tcur){
	SDL_Event event;
	TUIOData* data = (TUIOData*) malloc(sizeof(TUIOData));

	event.type = CURSOR_ADDEVENT;
	data->id = tcur->getCursorID();
	data->x = (Sint16)tcur->getScreenX(800);
	data->y = (Sint16)tcur->getScreenY(600);
	data->remove = false;
	data->tocou = false;
	data->destocou = false;
	data->tocando = false;
	event.user.data1 = data;
	event.user.data2 = 0;
	SDL_PushEvent(&event);

}

void InputManager::updateTuioCursor(TuioCursor *tcur){
	SDL_Event* event = (SDL_Event*) malloc(sizeof(SDL_Event));
	TUIOData* data = (TUIOData*) malloc(sizeof(TUIOData));
	int dist, distX, distY, cont;
	float dxRatio, dyRatio;
	list <TuioPoint>::reverse_iterator rit = tcur->path.rbegin();
	++rit;	//Getting penult object
	int penultimoX = (*rit).getScreenX(800),
		penultimoY = (*rit).getScreenY(600);

	event->type = CURSOR_MOVEEVENT;
	data->id = tcur->getCursorID();

	dist = tcur->getScreenDistance((*rit), 800, 600);

	distX = tcur->getScreenX(800) - penultimoX;
	distY = tcur->getScreenY(600) - penultimoY;

	dxRatio = (3*((float)distX/(float)dist));
	dyRatio = (3*((float)distY/(float)dist));

	cont = dist; //Counter for filling the gap

	for(int i = 1; cont > abs(3) ; i++){
		data->x = (Sint16)(penultimoX + roundf(i * dxRatio));
		data->y = (Sint16)(penultimoY + roundf(i * dyRatio));
		data->remove = false;
		data->tocou = false;
		data->destocou = false;
		data->tocando = false;
		event->user.data1 = data;
		event->user.data2 = 0;
		SDL_PushEvent(event);
		cont-=3;
		data = (TUIOData*) malloc(sizeof(TUIOData));
		event = (SDL_Event*) malloc(sizeof(SDL_Event));
		event->type = CURSOR_MOVEEVENT;
		data->id = tcur->getCursorID();
	}

	data->x = (Sint16)(tcur->getScreenX(800));
	data->y = (Sint16)(tcur->getScreenY(600));
	data->remove = false;
	data->tocou = false;
	data->destocou = false;
	data->tocando = false;
	event->user.data1 = data;
	event->user.data2 = 0;
	SDL_PushEvent(event);
}

void InputManager::removeTuioCursor(TuioCursor *tcur){
	SDL_Event event;
	TUIOData* data = (TUIOData*) malloc(sizeof(TUIOData));

	event.type = CURSOR_REMOVEEVENT;
	data->id = tcur->getCursorID();
	data->x = (Sint16)tcur->getScreenX(800);
	data->y = (Sint16)tcur->getScreenY(600);
	data->remove = false;
	data->tocou = false;
	data->destocou = false;
	data->tocando = false;
	event.user.data1 = data;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
}

void InputManager::refresh(TuioTime ftime){

}

Uint16 InputManager::getNumIds(){
	return(touch.size());
}

map<Sint16,TUIOData*>::iterator InputManager::getTouchBegin(){
	return(touch.begin());
}

map<Sint16,TUIOData*>::iterator InputManager::getTouchEnd(){
	return(touch.end());
}
