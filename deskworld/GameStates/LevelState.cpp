/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 *
 * Autores:  Danilo Gaby Andersen Trindade - 06/82039
 * 			 Victor Sampaio Zucca 		  - 06/25566
 *
 * Descricao: State in game do jogo.
 */

#include "LevelState.h"

LevelState::~LevelState() {
	Unload();
}

void LevelState::Load(){
	inputManager = inputManager->getInstance();
	engine = engine->getInstance();
	graphics = graphics->getInstance();
	background = new ImageLoader("paper.jpg",0,0);
	fechar = new ImageLoader("Fechar.png",(background->GetRect().w-25),3);
	bgMusic = new Audio("Wesnothmusic.ogg",1); //Background Music
	bgMusic->Play(-1);
	thickness = 10;
	menu.clear();
	menuSelect[0].clear();
	menuSelect[1].clear();
	menuSelect[2].clear();
	for (int i = 0; i < 10001; i++) {
		drawObjects[i].drawing = false;
		drawObjects[i].menu = false;
		drawObjects[i].xMouse = 0;
		drawObjects[i].xOrig = 0;
		drawObjects[i].yMouse = 0;
		drawObjects[i].yOrig = 0;
	}
	//World Cage
	RGBAColor worldColor;
	worldColor.r = 15;
	worldColor.g = 15;
	worldColor.b = 15;
	worldColor.a = 245;
	vector<int> vx, vy;
	vx.push_back(0); vy.push_back(0);
	vx.push_back(-2); vy.push_back(HEIGHT);
	GORectangle* leftwall = new GORectangle(vx, vy, worldColor, false);
	vx.clear(); vy.clear();
	vx.push_back(0); vy.push_back(0);
	vx.push_back(WIDTH); vy.push_back(-2);
	GORectangle* topwall = new GORectangle(vx, vy, worldColor, false);
	vx.clear(); vy.clear();
	vx.push_back(WIDTH); vy.push_back(0);
	vx.push_back(WIDTH+2); vy.push_back(HEIGHT);
	GORectangle* rightwall = new GORectangle(vx, vy, worldColor, false);
	vx.clear(); vy.clear();
	vx.push_back(0); vy.push_back(HEIGHT);
	vx.push_back(WIDTH); vy.push_back(HEIGHT+2);
	GORectangle* bottomwall = new GORectangle(vx, vy, worldColor, false);
	vx.clear(); vy.clear();

	//Creating initial world of the size of screen
	point p;
	vector<Point> worldvertices;
	p.x = 0; p.y = 0;
	worldvertices.push_back(p);
	p.x = WIDTH; p.y = 0;
	worldvertices.push_back(p);
	p.x = WIDTH; p.y = HEIGHT;
	worldvertices.push_back(p);
	p.x = 0; p.y = HEIGHT;
	worldvertices.push_back(p);
	GOWorld* w = new GOWorld(worldvertices);
	w->SetObjects(&objects);
	b2Vec2 grav;
	grav.Set(0.0, 9.8);
	w->SetGravity(grav);
	worlds.push_back(w);

//	point p;
//	b2Vec2 grav;
//	vector<Point> worldvertices;
//	p.x = 0; p.y = 0;
//	worldvertices.push_back(p);
//	p.x = WIDTH/2; p.y = 0;
//	worldvertices.push_back(p);
//	p.x = WIDTH/2; p.y = HEIGHT;
//	worldvertices.push_back(p);
//	p.x = 0; p.y = HEIGHT;
//	worldvertices.push_back(p);
//	GOWorld* w1 = new GOWorld(worldvertices);
//	w1->SetObjects(&objects);
//	grav.Set(5.5, 0.0);
//	w1->SetGravity(grav);
//	worlds.push_back(w1);
//	worldvertices.clear();
//
//	p.x = WIDTH/2; p.y = 0;
//	worldvertices.push_back(p);
//	p.x = WIDTH; p.y = 0;
//	worldvertices.push_back(p);
//	p.x = WIDTH; p.y = HEIGHT;
//	worldvertices.push_back(p);
//	p.x = WIDTH/2; p.y = HEIGHT;
//	worldvertices.push_back(p);
//	GOWorld* w2 = new GOWorld(worldvertices);
//	w2->SetObjects(&objects);
//	grav.Set(-5.5, 0.0);
//	w2->SetGravity(grav);
//	worlds.push_back(w2);
}

void LevelState::Unload(){
	delete background;
	delete fechar;
	delete bgMusic;
}

int LevelState::Update(){
	int id, time;
	SDL_Rect rect;
	RGBAColor worldColor;
	uint8 worldTool;
	bool worldDynamic, menutouch, jointEvent;//, menuBool, drawBool;
	Point p;
	ImageLoader* menuTemp;
	ImageLoader* menuSelectTemp[3];
	ImageLoader* menuSliderTemp[4];

	if(inputManager->isKeyDown(SDLK_ESCAPE)){
		SDL_Event* event = new SDL_Event();
		event->type = SDL_QUIT;
		SDL_PushEvent(event);
	}

	time = SDL_GetTicks();
	for(Uint32 i = 0; i < inputManager->click.size(); i++){
		menutouch = false;
//		menuBool = false;
//		drawBool = false;
		//Test mouse or touch down
		if (inputManager->isTouchInside(fechar, inputManager->click[i].id)){
			SDL_Event* event = new SDL_Event();
			event->type = SDL_QUIT;
			SDL_PushEvent(event);
			break;
		} else {
			GOWorld* currentWorld;
			for(Uint32 k = 0; k < menu.size(); k++){
				//Getting world info
				for(Uint32 j = 0 ; j < worlds.size(); j++){
					if(worlds[j]->isInside(menuP[k])){
						currentWorld = worlds[j];
						worldTool = worlds[j]->GetCurrentTool();
						break;
					}
				}

				if (inputManager->isTouchInside(menu[k], inputManager->click[i].id)) {
					menutouch = true;
					rect = menu[k]->GetRect();
					if (inputManager->click[i].y < rect.y + 18){
						if (inputManager->click[i].x > rect.x + 138){
							menu.erase(menu.begin()+k);
							for (int g = 0; g < 3; g++){
								menuSelect[g].erase(menuSelect[g].begin()+k);
							}
							menuSlider[0].erase(menuSlider[0].begin()+k);
							menuSlider[1].erase(menuSlider[1].begin()+k);
							menuSlider[2].erase(menuSlider[2].begin()+k);
							menuSlider[3].erase(menuSlider[3].begin()+k);
						}
					} else if (inputManager->click[i].y < rect.y + 42){
						currentWorld->SetDynamic(false);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 62){
						currentWorld->SetDynamic(true);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
					} else if (inputManager->click[i].y < rect.y + 82){
						currentWorld->SetCurrentTool(freeform);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 102){
						currentWorld->SetCurrentTool(circle);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 122){
						currentWorld->SetCurrentTool(rectangle);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 142){
						currentWorld->SetCurrentTool(triangle);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 162){
						if(bgMusic->isPlaying()){
							bgMusic->Pause();
						}else{
							bgMusic->Resume();
						}
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 182){
						currentWorld->SetCurrentTool(BARRIER);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 202){
						currentWorld->SetCurrentTool(erase);
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if (inputManager->click[i].y < rect.y + 222){
						// gravity
					} else if ((inputManager->click[i].y < rect.y + 318) &&
							(inputManager->click[i].y > rect.y + 306) &&
							(inputManager->click[i].x < rect.x + 46) &&
							(inputManager->click[i].x > rect.x + 7)){
						menu.erase(menu.begin()+k);
						for (int g = 0; g < 3; g++){
							menuSelect[g].erase(menuSelect[g].begin()+k);
						}
						menuSlider[0].erase(menuSlider[0].begin()+k);
						menuSlider[1].erase(menuSlider[1].begin()+k);
						menuSlider[2].erase(menuSlider[2].begin()+k);
						menuSlider[3].erase(menuSlider[3].begin()+k);
					} else if ((inputManager->click[i].y <= rect.y + 233) &&
							(inputManager->click[i].y >= rect.y + 217) &&
							(inputManager->click[i].x <= rect.x + 131) &&
							(inputManager->click[i].x >= rect.x + 71)) {

//						menuSliderTemp[0] = new ImageLoader("slider.png", (worldColor.r/(4.25))+(rect.x + 71), rect.y + 225);
//						menuSliderTemp[1] = new ImageLoader("slider.png", (worldColor.g/(4.25))+(rect.x + 71), rect.y + 245);
//						menuSliderTemp[2] = new ImageLoader("slider.png", (worldColor.b/(4.25))+(rect.x + 71), rect.y + 265);
//						menuSliderTemp[3] = new ImageLoader("slider.png", (worldColor.a/(4.25))+(rect.x + 71), rect.y + 285);
					}

//					} else if (inputManager->click[i].y < rect.y + 183){
//						RGBAColor worldColor;
//						worldColor.r = 15;
//						worldColor.g = 15;
//						worldColor.b = 15;
//						worldColor.a = 245;
//						currentWorld->SetWorldColor(worldColor);
//					} else if (inputManager->click[i].y < rect.y + 200){
//						RGBAColor worldColor;
//						worldColor.r = 235;
//						worldColor.g = 39;
//						worldColor.b = 37;
//						worldColor.a = 245;
//						currentWorld->SetWorldColor(worldColor);
//					} else if (inputManager->click[i].y < rect.y + 217){
//						RGBAColor worldColor;
//						worldColor.r = 34;
//						worldColor.g = 255;
//						worldColor.b = 34;
//						worldColor.a = 245;
//						currentWorld->SetWorldColor(worldColor);
//					} else if (inputManager->click[i].y < rect.y + 234){
//						RGBAColor worldColor;
//						worldColor.r = 34;
//						worldColor.g = 34;
//						worldColor.b = 255;
//						worldColor.a = 245;
//						currentWorld->SetWorldColor(worldColor);
//					} else if (inputManager->click[i].y < rect.y + 251){
//						RGBAColor worldColor;
//						worldColor.r = 255;
//						worldColor.g = 236;
//						worldColor.b = 139;
//						worldColor.a = 245;
//						currentWorld->SetWorldColor(worldColor);
//					} else {
//						RGBAColor worldColor;
//						worldColor.r = 250;
//						worldColor.g = 240;
//						worldColor.b = 230;
//						worldColor.a = 245;
//						currentWorld->SetWorldColor(worldColor);
//					}
//					menu.erase(menu.begin()+k);
//					for (int g = 0; g < 3; g++){
//						menuSelect[g].erase(menuSelect[g].begin()+k);
//					}
					drawObjects[inputManager->click[i].id].drawing = false;
//					drawBool = false;
					inputManager->click[i].release = true;
				}
			}
			if (!menutouch){
				//Test overlap to erase objects
				if(worldTool == erase){
					Object* delObj;
					delObj = engine->EraseObject(inputManager->click[i].x, inputManager->click[i].y);
					if(delObj != NULL){
						for(Uint32 j = 0; j < objects.size() ; j++){
							if(objects.at(j)->GetBody() == (delObj->body)){
								objects.erase(objects.begin()+j);
								engine->DestroyObject(*delObj);
								drawObjects[inputManager->click[i].id].drawing = false;
//								drawBool = false;
								inputManager->click[i].release = true;
								break;
							}
						}
					}
				//Drawing or Mousejoint
				} else {
					engine->MouseDown(inputManager->click[i].x, inputManager->click[i].y, inputManager->click[i].id);
					if (engine->mouseJoint[inputManager->click[i].id] != NULL) {
						drawObjects[inputManager->click[i].id].drawing = false;
//						drawBool = false;
						jointEvent = true;
						inputManager->click[i].release = true;
					}
				}
			}
		}
		//Mouse up to destroy joint
		if(inputManager->click[i].updated){//inputManager->isTouchUp(inputManager->click[i].id)){
			if(engine->mouseJoint[inputManager->click[i].id] != NULL){
				engine->DestroyMouseJoint(inputManager->click[i].id);
				inputManager->xy.clear();
				drawObjects[inputManager->click[i].id].drawing = false;
//				drawBool = false;
				jointEvent = true;
				inputManager->click[i].release = true;
//					drawObjects[inputManager->click[i].id].xOrig = inputManager->click[i].x;
//					drawObjects[inputManager->click[i].id].yOrig = inputManager->click[i].y;
			}
		//Update grabbed object with mouse position
		} else if(engine->mouseJoint[inputManager->click[i].id] != NULL){
//				b2Vec2 p(CONVERT(inputManager->touchPosX(inputManager->click[i].id)), CONVERT(inputManager->touchPosY(inputManager->click[i].id)));
			b2Vec2 p(CONVERT(inputManager->click[i].x), CONVERT(inputManager->click[i].y));
			engine->mouseJoint[inputManager->click[i].id]->SetTarget(p);
			drawObjects[inputManager->click[i].id].drawing = false;
//			drawBool = false;
			jointEvent = true;
			inputManager->click[i].release = true;
//				drawObjects[inputManager->click[i].id].xOrig = inputManager->click[i].x;
//				drawObjects[inputManager->click[i].id].yOrig = inputManager->click[i].y;
		}
//		}
//		if ((time - inputManager->click[i].time) > TIMELIMIT) {
		if ((inputManager->click[i].time)==0) {
			//CHECAR ISSO TODO
			p.x = inputManager->click[i].x;//drawObjects[inputManager->click[i].id].xMouse;
			p.y = inputManager->click[i].y;//drawObjects[inputManager->click[i].id].yMouse;
			//Getting world info
			for(Uint32 j = 0 ; j < worlds.size(); j++){
				if(worlds[j]->isInside(p)){
					worldTool = worlds[j]->GetCurrentTool();
					break;
				}
			}

//			menuBool = false;
//			drawBool = true;
			drawObjects[inputManager->click[i].id].menu = false;
			inputManager->click[i].release = true;
			drawObjects[inputManager->click[i].id].drawing = true;
//			drawObjects[inputManager->click[i].id].xOrig = inputManager->click[i].x;
//			drawObjects[inputManager->click[i].id].yOrig = inputManager->click[i].y;

			if(worldTool == freeform){
				if(ff_vx[inputManager->click[i].id].empty()){
					ff_vx[inputManager->click[i].id].push_back(inputManager->click[i].x);
					ff_vy[inputManager->click[i].id].push_back(inputManager->click[i].y);
				}
			}
			inputManager->xy.clear();
		}
		if((inputManager->click[i].updated) && (!inputManager->click[i].remove)){
			for (Uint32 j = i+1; j < inputManager->click.size(); j++) {
				if((inputManager->click[j].updated) && (!inputManager->click[j].remove)){
					if((inputManager->click[j].time - inputManager->click[i].time) < TIMELIMIT){
						if ((inputManager->click[j].x > (inputManager->click[i].x - MENUPROX)) &&
								(inputManager->click[j].x < (inputManager->click[i].x + MENUPROX)) &&
								(inputManager->click[j].y > (inputManager->click[i].y - MENUPROX)) &&
								(inputManager->click[j].y < (inputManager->click[i].y + MENUPROX))){
							inputManager->click[j].release = true;
//							if (inputManager->isTouching(inputManager->click[j].id)) {
//								inputManager->click[j].id = 9000;
//							}
//							while (inputManager->isTouching(inputManager->click[j].id)) {
//								inputManager->click[j].id--;
//							}
							drawObjects[inputManager->click[j].id].xOrig = inputManager->click[j].x;
							drawObjects[inputManager->click[j].id].yOrig = inputManager->click[j].y;
							drawObjects[inputManager->click[j].id].menu = true;
							drawObjects[inputManager->click[j].id].drawing = false;
							inputManager->click[i].remove = true;
							inputManager->click[i].release = false;
							break;
						}
					}
				}
			}
		}
		if (inputManager->click[i].release) {
//			int newId = inputManager->click[i].id;
//			if (inputManager->isTouching(newId)) {
//				newId = 9000;
//			}
//			while (inputManager->isTouching(newId)) {
//				newId--;
//			}
//			if (newId != inputManager->click[i].id){
				drawObjects[inputManager->click[i].id].xOrig = inputManager->click[i].x;
				drawObjects[inputManager->click[i].id].yOrig = inputManager->click[i].y;
//				drawObjects[newId].xMouse = drawObjects[inputManager->click[i].id].xMouse;
//				drawObjects[newId].yMouse = drawObjects[inputManager->click[i].id].yMouse;
//				drawObjects[newId].drawing = drawObjects[inputManager->click[i].id].drawing;
//				drawObjects[newId].menu = drawObjects[inputManager->click[i].id].menu;
//				if (jointEvent) {
//					engine->MouseDown(inputManager->click[i].x, inputManager->click[i].y, newId);
////					engine->mouseJoint[newId] = engine->mouseJoint[inputManager->click[i].id];
//					engine->DestroyMouseJoint(inputManager->click[i].id);
//				}
//				inputManager->click[i].id = newId;
//			}
//////			drawObjects[inputManager->click[i].id].menu = menuBool;
//			drawObjects[inputManager->click[i].id].drawing = true;
		}
	}
	for(int i = 0; i < inputManager->getNumIds(); i++){
		id = inputManager->getId(i);
		drawObjects[id].xMouse = inputManager->touchPosX(id);
		drawObjects[id].yMouse = inputManager->touchPosY(id);
		if(drawObjects[id].drawing){
			//TODO
			p.x = drawObjects[id].xOrig;
			p.y = drawObjects[id].yOrig;
			//Getting world info
			GOWorld* currentWorld;
			for(Uint32 j = 0 ; j < worlds.size(); j++){
				if(worlds[j]->isInside(p)){
					worldColor = worlds[j]->GetWorldColor();
					worldTool = worlds[j]->GetCurrentTool();
					worldDynamic = worlds[j]->GetDynamic();
					currentWorld = worlds[j];
					break;
				}
			}
			if(inputManager->isTouchUp(id)){
				vector<int> vx, vy;
				GOTriangle* t;
				GORectangle* r;
				GOFreeform* ff;
				GOCircle* c;
				GOBarrier* b;
				switch(worldTool){
				case triangle:
					// Mouse point above from origin
					if(drawObjects[id].yMouse < drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Mouse point at left from origin
							vx.push_back((((drawObjects[id].xOrig-drawObjects[id].xMouse)/2)+drawObjects[id].xMouse));
							vy.push_back(drawObjects[id].yMouse);
							vx.push_back(drawObjects[id].xOrig);
							vy.push_back(drawObjects[id].yOrig);
							vx.push_back(drawObjects[id].xMouse);
							vy.push_back(drawObjects[id].yOrig);
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Mouse point at right from origin
							vx.push_back((((drawObjects[id].xMouse-drawObjects[id].xOrig)/2)+drawObjects[id].xOrig));
							vy.push_back(drawObjects[id].yMouse);
							vx.push_back(drawObjects[id].xMouse);
							vy.push_back(drawObjects[id].yOrig);
							vx.push_back(drawObjects[id].xOrig);
							vy.push_back(drawObjects[id].yOrig);
						}
						else{break;}
					// Mouse point below from origin
					}else if(drawObjects[id].yMouse > drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Mouse point at left from origin
							vx.push_back((((drawObjects[id].xOrig-drawObjects[id].xMouse)/2)+drawObjects[id].xMouse));
							vy.push_back(drawObjects[id].yOrig);
							vx.push_back(drawObjects[id].xOrig);
							vy.push_back(drawObjects[id].yMouse);
							vx.push_back(drawObjects[id].xMouse);
							vy.push_back(drawObjects[id].yMouse);
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Mouse point at right from origin
							vx.push_back((((drawObjects[id].xMouse-drawObjects[id].xOrig)/2)+drawObjects[id].xOrig));
							vy.push_back(drawObjects[id].yOrig);
							vx.push_back(drawObjects[id].xMouse);
							vy.push_back(drawObjects[id].yMouse);
							vx.push_back(drawObjects[id].xOrig);
							vy.push_back(drawObjects[id].yMouse);
						}else{break;}
					}else{break;}
					t = new GOTriangle(vx, vy, worldColor, worldDynamic);
					objects.push_back(t);
					break;
				case rectangle:
					vx.push_back(drawObjects[id].xOrig);
					vy.push_back(drawObjects[id].yOrig);
					vx.push_back(drawObjects[id].xMouse);
					vy.push_back(drawObjects[id].yMouse);
					r = new GORectangle(vx, vy, worldColor, worldDynamic);
					objects.push_back(r);
					break;
				case circle:
					vx.push_back(drawObjects[id].xOrig);
					vy.push_back(drawObjects[id].yOrig);
					vx.push_back(drawObjects[id].xMouse);
					vy.push_back(drawObjects[id].yMouse);
					c = new GOCircle(vx, vy, worldColor, worldDynamic);
					objects.push_back(c);
					break;
				case freeform:
					vx = ff_vx[id];
					vy = ff_vy[id];
					ff = new GOFreeform(vx, vy, worldColor, worldDynamic, thickness);
					ff_vx[id].clear();
					ff_vy[id].clear();
					inputManager->xy.clear();
					objects.push_back(ff);
					break;
				case BARRIER:
					vector<Point> p = currentWorld->GetVertices();
					int difx = abs(drawObjects[id].xMouse - p[0].x);
					if(difx > abs(drawObjects[id].xMouse - p[1].x)){
						difx = abs(drawObjects[id].xMouse - p[1].x);
					}
					int dify = abs(drawObjects[id].yMouse - p[0].y);
					if(dify > abs(drawObjects[id].yMouse - p[2].y)){
						dify = abs(drawObjects[id].yMouse - p[2].y);
					}
					if(difx > dify){
						vx.push_back(drawObjects[id].xMouse);
						vy.push_back(p[0].y);
						vx.push_back(drawObjects[id].xMouse);
						vy.push_back(p[2].y);
						b = new GOBarrier(vx, vy, worldColor);
						objects.push_back(b);
						//subdividing worlds
						delete(currentWorld);
						//first subworld
						vector<Point> worldVertices;
						Point paux;
						paux.x = p[0].x;
						paux.y = p[0].y;
						worldVertices.push_back(paux);
						paux.x = drawObjects[id].xMouse;
						paux.y = p[0].y;
						worldVertices.push_back(paux);
						paux.x = drawObjects[id].xMouse;
						paux.y = p[2].y;
						worldVertices.push_back(paux);
						paux.x = p[0].x;
						paux.y = p[2].y;
						worldVertices.push_back(paux);
						GOWorld* w1 = new GOWorld(worldVertices);
						w1->SetObjects(&objects);
						worldVertices.clear();
						//second subworld
						paux.x = drawObjects[id].xMouse;
						paux.y = p[0].y;
						worldVertices.push_back(paux);
						paux.x = p[1].x;
						paux.y = p[1].y;
						worldVertices.push_back(paux);
						paux.x = p[2].x;
						paux.y = p[2].y;
						worldVertices.push_back(paux);
						paux.x = drawObjects[id].xMouse;
						paux.y = p[2].y;
						worldVertices.push_back(paux);
						GOWorld* w2 = new GOWorld(worldVertices);
						w2->SetObjects(&objects);
						worldVertices.clear();
						//including worlds
						worlds.push_back(w1);
						worlds.push_back(w2);
					}else{
						vx.push_back(p[0].x);
						vy.push_back(drawObjects[id].yMouse);
						vx.push_back(p[1].x);
						vy.push_back(drawObjects[id].yMouse);
						b = new GOBarrier(vx, vy, worldColor);
						objects.push_back(b);
						//subdividing worlds
						delete(currentWorld);
						//first subworld
						vector<Point> worldVertices;
						Point paux;
						paux.x = p[0].x;
						paux.y = p[0].y;
						worldVertices.push_back(paux);
						paux.x = p[1].x;
						paux.y = p[1].y;
						worldVertices.push_back(paux);
						paux.x = p[1].x;
						paux.y = drawObjects[id].yMouse;
						worldVertices.push_back(paux);
						paux.x = p[0].x;
						paux.y = drawObjects[id].yMouse;
						worldVertices.push_back(paux);
						GOWorld* w1 = new GOWorld(worldVertices);
						w1->SetObjects(&objects);
						worldVertices.clear();
						//second subworld
						paux.x = p[0].x;
						paux.y = drawObjects[id].yMouse;
						worldVertices.push_back(paux);
						paux.x = p[1].x;
						paux.y = drawObjects[id].yMouse;
						worldVertices.push_back(paux);
						paux.x = p[1].x;
						paux.y = p[2].y;
						worldVertices.push_back(paux);
						paux.x = p[0].x;
						paux.y = p[2].y;
						worldVertices.push_back(paux);
						GOWorld* w2 = new GOWorld(worldVertices);
						w2->SetObjects(&objects);
						worldVertices.clear();
						//including worlds
						worlds.push_back(w1);
						worlds.push_back(w2);
					}
					break;
				}

				drawObjects[id].drawing = false;
				drawObjects[id].menu = false;
				drawObjects[id].xMouse = 0;
				drawObjects[id].xOrig = 0;
				drawObjects[id].yMouse = 0;
				drawObjects[id].yOrig = 0;

			}else if(worldTool == freeform){
			//Free form should have all the coordinates of a series of circles
				if(inputManager->isTouching(id)){
					if(id == 10000){
						if(!(ff_vx[id].empty())){
							if((ff_vx[id].back() != drawObjects[id].xMouse) || (ff_vy[id].back() != drawObjects[id].yMouse)){
								ff_vx[id].push_back(drawObjects[id].xMouse);
								ff_vy[id].push_back(drawObjects[id].yMouse);
							}
						}else{
							ff_vx[id].push_back(drawObjects[id].xMouse);
							ff_vy[id].push_back(drawObjects[id].yMouse);
						}
					}else{
						//Test for finger movement
						multimap<int ,point>::iterator it;
						while((inputManager->xy.end()!= (it = inputManager->xy.find(id)))){
							ff_vx[id].push_back(it->second.x);
							ff_vy[id].push_back(it->second.y);
							inputManager->xy.erase(it);
						}
					}
				}
			}
		}else{
			if(drawObjects[id].menu){
				p.x = drawObjects[id].xOrig;
				p.y = drawObjects[id].yOrig;
				menuP.push_back(p);
				//Getting world info
				for(Uint32 j = 0 ; j < worlds.size(); j++){
					if(worlds[j]->isInside(p)){
						worldTool = worlds[j]->GetCurrentTool();
						worldDynamic = worlds[j]->GetDynamic();
						worldColor = worlds[j]->GetWorldColor();
						break;
					}
				}
				if (menuTemp != NULL){
//					delete menuTemp;
					menuTemp = NULL;
				}
				menuTemp = new ImageLoader("menu.png", drawObjects[id].xOrig, drawObjects[id].yOrig);
				rect = menuTemp->GetRect();
				if ((rect.x + rect.w) > WIDTH){
					menuTemp->UpdatePos(rect.x-rect.w, rect.y);
					rect = menuTemp->GetRect();
				}
				if ((rect.y + rect.h) > HEIGHT){
					menuTemp->UpdatePos(rect.x, rect.y-rect.h);
					rect = menuTemp->GetRect();
				}
				if (worldDynamic) {
					menuSelectTemp[0] = new ImageLoader("menuselect.png", rect.x, rect.y + 46);
				} else {
					menuSelectTemp[0] = new ImageLoader("menuselect.png", rect.x, rect.y + 26);
				}
				if (worldTool == freeform){
					menuSelectTemp[1] = new ImageLoader("menuselect.png", rect.x, rect.y + 66);
				} else if (worldTool == circle){
					menuSelectTemp[1] = new ImageLoader("menuselect.png", rect.x, rect.y + 86);
				} else if (worldTool == rectangle){
					menuSelectTemp[1] = new ImageLoader("menuselect.png", rect.x, rect.y + 106);
				} else if (worldTool == triangle){
					menuSelectTemp[1] = new ImageLoader("menuselect.png", rect.x, rect.y + 126);
				} else {
					menuSelectTemp[1] = new ImageLoader("menuselect.png", rect.x, rect.y + 186);
				}
				if (!bgMusic->isPlaying()){
					menuSelectTemp[2] = new ImageLoader("menuselect.png", rect.x, rect.y + 146);
				} else {
					if (menuSelectTemp[2] != NULL){
//						delete menuSelectTemp[2];
						menuSelectTemp[2] = NULL;
					}
				}
				//1 pixel = 4.25 cor;
				menuSliderTemp[0] = new ImageLoader("slider.png", (worldColor.r/(4.25))+(rect.x + 71), rect.y + 225);
				menuSliderTemp[1] = new ImageLoader("slider.png", (worldColor.g/(4.25))+(rect.x + 71), rect.y + 245);
				menuSliderTemp[2] = new ImageLoader("slider.png", (worldColor.b/(4.25))+(rect.x + 71), rect.y + 265);
				menuSliderTemp[3] = new ImageLoader("slider.png", (worldColor.a/(4.25))+(rect.x + 71), rect.y + 285);
				//Max
//				menuSliderTemp[0] = new ImageLoader("slider.png", rect.x + 131, rect.y + 225);
//				menuSliderTemp[1] = new ImageLoader("slider.png", rect.x + 131, rect.y + 245);
//				menuSliderTemp[2] = new ImageLoader("slider.png", rect.x + 131, rect.y + 265);
//				menuSliderTemp[3] = new ImageLoader("slider.png", rect.x + 131, rect.y + 285);
				//Min
//				menuSliderTemp[0] = new ImageLoader("slider.png", rect.x + 71, rect.y + 225);
//				menuSliderTemp[1] = new ImageLoader("slider.png", rect.x + 71, rect.y + 245);
//				menuSliderTemp[2] = new ImageLoader("slider.png", rect.x + 71, rect.y + 265);
//				menuSliderTemp[3] = new ImageLoader("slider.png", rect.x + 71, rect.y + 285);
				menu.push_back(menuTemp);
				menuSelect[0].push_back(menuSelectTemp[0]);
				menuSelect[1].push_back(menuSelectTemp[1]);
				menuSelect[2].push_back(menuSelectTemp[2]);
				menuSlider[0].push_back(menuSliderTemp[0]);
				menuSlider[1].push_back(menuSliderTemp[1]);
				menuSlider[2].push_back(menuSliderTemp[2]);
				menuSlider[3].push_back(menuSliderTemp[3]);
				drawObjects[id].menu = false;
			} else {
				//Mouse up to destroy joint
				if(inputManager->isTouchUp(id)){
					if(engine->mouseJoint[id] != NULL){
						engine->DestroyMouseJoint(id);
						inputManager->xy.clear();
					}
					drawObjects[id].drawing = false;
					drawObjects[id].menu = false;
					drawObjects[id].xMouse = 0;
					drawObjects[id].xOrig = 0;
					drawObjects[id].yMouse = 0;
					drawObjects[id].yOrig = 0;
				//Update grabbed object with mouse position
				} else if(engine->mouseJoint[id] != NULL){
					b2Vec2 p(CONVERT(inputManager->touchPosX(id)), CONVERT(inputManager->touchPosY(id)));
					engine->mouseJoint[id]->SetTarget(p);
				}
			}
		}
	}

//	for(Uint32 i = 0; i < inputManager->click.size(); i++){
//		if (inputManager->click[i].release) {
//			drawObjects[inputManager->click[i].id].xOrig = inputManager->click[i].x;
//			drawObjects[inputManager->click[i].id].yOrig = inputManager->click[i].y;
//		}
//	}
	//Worlds update
	for(Uint32 i = 0; i < worlds.size() ; i++){
		worlds[i]->Update();
	}
	//World update
	engine->Update();
	return 0;
}

void LevelState::Render(){
	int id;
	RGBAColor worldColor;
	uint8 worldTool;
	GOWorld* currentWorld;
	Point p;

	background->Render();

	for(int i = 0; i < inputManager->getNumIds(); i++){
		id = inputManager->getId(i);
		if(drawObjects[id].drawing){

			drawObjects[id].xMouse = inputManager->touchPosX(id);
			drawObjects[id].yMouse = inputManager->touchPosY(id);

			p.x = drawObjects[id].xOrig;
			p.y = drawObjects[id].yOrig;
			//Getting world info
			for(Uint32 j = 0 ; j < worlds.size(); j++){
				if(worlds[j]->isInside(p)){
					worldColor = worlds[j]->GetWorldColor();
					worldTool = worlds[j]->GetCurrentTool();
					currentWorld = worlds[j];
					break;
				}
			}

			if(inputManager->isTouching(id)){
				vector<int> vx, vy;
				switch(worldTool){
				case triangle:
					// Mouse point above from origin
					if(drawObjects[id].yMouse < drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Mouse point at left from origin
							graphics->DrawTriangle( drawObjects[id].xOrig, drawObjects[id].yOrig, ((drawObjects[id].xOrig-drawObjects[id].xMouse)/2)+drawObjects[id].xMouse, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yOrig, worldColor);
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Mouse point at right from origin
							graphics->DrawTriangle( drawObjects[id].xOrig, drawObjects[id].yOrig, ((drawObjects[id].xMouse-drawObjects[id].xOrig)/2)+drawObjects[id].xOrig, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yOrig, worldColor);
						}
					// Mouse point below from origin
					}else if(drawObjects[id].yMouse > drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Mouse point at left from origin
							graphics->DrawTriangle( ((drawObjects[id].xOrig-drawObjects[id].xMouse)/2)+drawObjects[id].xMouse, drawObjects[id].yOrig, drawObjects[id].xOrig, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yMouse, worldColor);
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Mouse point at right from origin
							graphics->DrawTriangle( ((drawObjects[id].xMouse-drawObjects[id].xOrig)/2)+drawObjects[id].xOrig, drawObjects[id].yOrig, drawObjects[id].xOrig, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yMouse, worldColor);
						}
					}
					break;
				case rectangle:
					vx.push_back(drawObjects[id].xOrig);
					vy.push_back(drawObjects[id].yOrig);
					vx.push_back(drawObjects[id].xMouse);
					vy.push_back(drawObjects[id].yOrig);
					vx.push_back(drawObjects[id].xMouse);
					vy.push_back(drawObjects[id].yMouse);
					vx.push_back(drawObjects[id].xOrig);
					vy.push_back(drawObjects[id].yMouse);
					graphics->DrawRectangle( vx, vy, worldColor);
					break;
				case circle:
					if(drawObjects[id].yMouse < drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Ponto do mouse a esquerda da origem
							if((drawObjects[id].xOrig-drawObjects[id].xMouse)>(drawObjects[id].yOrig-drawObjects[id].yMouse)){
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xOrig-drawObjects[id].xMouse), worldColor);
							}else{
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yOrig-drawObjects[id].yMouse), worldColor);
							}
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Ponto do mouse a direita da origem
							if((drawObjects[id].xMouse-drawObjects[id].xOrig)>(drawObjects[id].yOrig-drawObjects[id].yMouse)){
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xMouse-drawObjects[id].xOrig), worldColor);
							}else{
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yOrig-drawObjects[id].yMouse), worldColor);
							}
						}
					}else if(drawObjects[id].yMouse > drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Ponto do mouse a esquerda da origem
							if((drawObjects[id].xOrig-drawObjects[id].xMouse)>(drawObjects[id].yMouse-drawObjects[id].yOrig)){
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xOrig-drawObjects[id].xMouse), worldColor);
							}else{
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yMouse-drawObjects[id].yOrig), worldColor);
							}
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Ponto do mouse a direita da origem
							if((drawObjects[id].xMouse-drawObjects[id].xOrig)>(drawObjects[id].yMouse-drawObjects[id].yOrig)){
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xMouse-drawObjects[id].xOrig), worldColor);
							}else{
								graphics->DrawCircle( drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yMouse-drawObjects[id].yOrig), worldColor);
							}
						}
					}
					break;
				case freeform:
						for(Uint32 i = 0 ; i < ff_vx[id].size() ; i++){
							graphics->DrawCircle( ff_vx[id].at(i), ff_vy[id].at(i), (int)thickness, worldColor);
						}
					break;
				case BARRIER:
					vector<Point> p = currentWorld->GetVertices();
					int difx = abs(drawObjects[id].xMouse - p[0].x);
					if(difx > abs(drawObjects[id].xMouse - p[1].x)){
						difx = abs(drawObjects[id].xMouse - p[1].x);
					}
					int dify = abs(drawObjects[id].yMouse - p[0].y);
					if(dify > abs(drawObjects[id].yMouse - p[2].y)){
						dify = abs(drawObjects[id].yMouse - p[2].y);
					}
					if(difx > dify){
						graphics->DrawLine(drawObjects[id].xMouse, p[0].y, drawObjects[id].xMouse, p[2].y, worldColor);
					}else{
						graphics->DrawLine(p[0].x, drawObjects[id].yMouse, p[1].x, drawObjects[id].yMouse, worldColor);
					}
					break;
				}
			}
		}
	}
	for(Uint32 i = 0; i < objects.size() ; i++){
		objects.at(i)->Render();
	}
	fechar->Render();
	for(Uint32 k = 0; k < menu.size(); k++){
		menu[k]->Render();
		for (int i = 0; i < 3; i++) {
			if (menuSelect[i][k] != NULL) {
				menuSelect[i][k]->Render();
			}
		}
		menuSlider[0][k]->Render();
		menuSlider[1][k]->Render();
		menuSlider[2][k]->Render();
		menuSlider[3][k]->Render();
	}

}
