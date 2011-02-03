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

	memset(id, -1, sizeof(id));
	numIds = 0;

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
	Click clickTemp;
	int time;

	memset(keyDownState, false, sizeof(keyDownState));
	memset(keyUpState, false, sizeof(keyUpState));
	memset(buttomDownState, false, sizeof(buttomDownState));
	memset(buttomUpState, false, sizeof(buttomUpState));
	for (int i = 0; i < numIds; i++){
		if (touch[id[i]]->remove){
			int g;
			for (g = i; g < numIds; g++){
				id[g] = id[g+1];
			}
			id[g] = -1;
			numIds--;
			i--;
		} else {
			touch[id[i]]->tocou = false;
			touch[id[i]]->destocou = false;
		}
	}
	motion_event = false;
	time = SDL_GetTicks();
	for(Uint32 i = 0; i < click.size(); i++){
		if ((click[i].remove) || ((time - click[i].time) > 1000)) {
			click.erase(click.begin() + i);
		}
	}
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_KEYDOWN) {
			keyDownState[event.key.keysym.sym] = 1;
		}else if(event.type == SDL_KEYUP){
			keyUpState[event.key.keysym.sym] = 1;
		}else if(event.type == CURSOR_ADDEVENT){
			id[numIds] = event.user.code;
			numIds++;
			touch[event.user.code] = (TUIOData*)event.user.data1;
			touch[event.user.code]->tocou = true;
			touch[event.user.code]->tocando = true;
			clickTemp.id = event.user.code;
			clickTemp.x = touch[event.user.code]->x;
			clickTemp.y = touch[event.user.code]->y;
			clickTemp.updated = false;
			clickTemp.remove = false;
			clickTemp.time = SDL_GetTicks();
			click.push_back(clickTemp);
		}else if(event.type == CURSOR_REMOVEEVENT){
			data = (TUIOData*)event.user.data1;
			touch[event.user.code]->remove = true;
			touch[event.user.code]->destocou = true;
			touch[event.user.code]->tocando = false;
			touch[event.user.code]->x = data->x;
			touch[event.user.code]->y = data->y;
			for(Uint32 i = 0; i < click.size(); i++){
				if ((click[i].id == event.user.code) && (!click[i].updated)) {
					click[i].updated = true;
					break;
				}
			}
		}else if(event.type == CURSOR_MOVEEVENT){
			data = (TUIOData*)event.user.data1;
			point temp;
			temp.x = data->x;
			temp.y = data->y;
			xy.insert(pair<int, point >(event.user.code, temp));
			touch[event.user.code]->x = data->x;
			touch[event.user.code]->y = data->y;
			motion_event = true;
			for(Uint32 i = 0; i < click.size(); i++){
				if (click[i].id == event.user.code) {
					click.erase(click.begin() + i);
				}
			}
		}else if(event.type == SDL_MOUSEBUTTONDOWN){
			buttomDownState[event.button.button] = 1;
			data = (TUIOData*) malloc(sizeof(TUIOData));
			data->tocou = true;
			data->tocando = true;
			data->destocou = false;
			data->remove = false;
			data->x = event.button.x;
			data->y = event.button.y;
			id[numIds] = 10000;
			numIds++;
			touch[10000] = data;
			clickTemp.id = 10000;
			clickTemp.x = touch[10000]->x;
			clickTemp.y = touch[10000]->y;
			clickTemp.updated = false;
			clickTemp.remove = false;
			clickTemp.time = SDL_GetTicks();
			click.push_back(clickTemp);
		}else if(event.type == SDL_MOUSEBUTTONUP){
			buttomUpState[event.button.button] = 1;
			touch[10000]->tocando = false;
			touch[10000]->destocou = true;
			touch[10000]->x = event.button.x;
			touch[10000]->y = event.button.y;
			touch[10000]->remove = true;
			for(Uint32 i = 0; i < click.size(); i++){
				if ((click[i].id == 10000) && (!click[i].updated)) {
					click[i].updated = true;
					break;
				}
			}
		}else if(event.type == SDL_MOUSEMOTION){
			if (touch[10000] != NULL) {
				touch[10000]->x = event.button.x;
				touch[10000]->y = event.button.y;
				motion_event = true;
				for(Uint32 i = 0; i < click.size(); i++){
					if (click[i].id == 10000) {
						click.erase(click.begin() + i);
					}
				}
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

int InputManager::mousePosX(){
	return touch[10000]->x;
}

int InputManager::mousePosY(){
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

int InputManager::touchPosX(int code){
	return touch[code]->x;
}

int InputManager::touchPosY(int code){
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
	event.user.code = tcur->getCursorID();
	data->x = (int)tcur->getScreenX(WIDTH);
	data->y = (int)tcur->getScreenY(HEIGHT);
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
	int penultimoX = (*rit).getScreenX(WIDTH),
		penultimoY = (*rit).getScreenY(HEIGHT);

	event->type = CURSOR_MOVEEVENT;
	event->user.code = tcur->getCursorID();

	dist = tcur->getScreenDistance((*rit), WIDTH, HEIGHT);

	distX = tcur->getScreenX(WIDTH) - penultimoX;
	distY = tcur->getScreenY(HEIGHT) - penultimoY;

	dxRatio = (3*((float)distX/(float)dist));
	dyRatio = (3*((float)distY/(float)dist));

	cont = dist; //Counter for filling the gap

	for(int i = 1; cont > abs(3) ; i++){
		data->x = (int)(penultimoX + roundf(i * dxRatio));
		data->y = (int)(penultimoY + roundf(i * dyRatio));
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
		event->user.code = tcur->getCursorID();
	}

	data->x = (int)(tcur->getScreenX(WIDTH));
	data->y = (int)(tcur->getScreenY(HEIGHT));
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
	event.user.code = tcur->getCursorID();
	data->x = (int)tcur->getScreenX(WIDTH);
	data->y = (int)tcur->getScreenY(HEIGHT);
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

int InputManager::getNumIds(){
	return(numIds);
}

int InputManager::getId(int pos){
	return(id[pos]);
}
