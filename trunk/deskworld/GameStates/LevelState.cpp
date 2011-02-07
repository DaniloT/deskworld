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
	toolColor.r = 15;
	toolColor.g = 15;
	toolColor.b = 15;
	toolColor.a = 245;
	currentTool = freeform;
	dynamic = false;
	thickness = 5;
	menu = NULL;
	menuSelect[0] = NULL;
	menuSelect[1] = NULL;
	menuSelect[2] = NULL;
	menuSelect[3] = NULL;
	for (int i = 0; i < 10001; i++) {
		drawObjects[i].drawing = false;
		drawObjects[i].menu = false;
		drawObjects[i].xMouse = 0;
		drawObjects[i].xOrig = 0;
		drawObjects[i].yMouse = 0;
		drawObjects[i].yOrig = 0;
	}
}

void LevelState::Unload(){
	delete background;
	delete fechar;
	delete bgMusic;
}

int LevelState::Update(){
	int id, time;
	SDL_Rect rect;

	time = SDL_GetTicks();
	for(Uint32 i = 0; i < inputManager->click.size(); i++){
//		if(inputManager->isTouched(inputManager->click[i].id)){
			drawObjects[inputManager->click[i].id].xOrig = inputManager->click[i].x;
			drawObjects[inputManager->click[i].id].yOrig = inputManager->click[i].y;
			//Test mouse or touch down
			if (inputManager->isTouchInside(fechar, inputManager->click[i].id)){
				SDL_Event* event = new SDL_Event();
				event->type = SDL_QUIT;
				SDL_PushEvent(event);
				break;
			} else {
				if (menu != NULL) {
					if (inputManager->isTouchInside(menu, inputManager->click[i].id)) {
						rect = menu->GetRect();
						if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 29){
							dynamic = false;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 51){
							dynamic = true;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 71){
							currentTool = freeform;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 89){
							currentTool = circle;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 110){
							currentTool = rectangle;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 127){
							currentTool = triangle;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 146){
							currentTool = erase;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 166){
							if(bgMusic->isPlaying()){
								bgMusic->Pause();
							}else{
								bgMusic->Resume();
							}
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 183){
							toolColor.r = 15;
							toolColor.g = 15;
							toolColor.b = 15;
							toolColor.a = 245;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 200){
							toolColor.r = 235;
							toolColor.g = 39;
							toolColor.b = 37;
							toolColor.a = 245;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 217){
							toolColor.r = 34;
							toolColor.g = 255;
							toolColor.b = 34;
							toolColor.a = 245;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 234){
							toolColor.r = 34;
							toolColor.g = 34;
							toolColor.b = 255;
							toolColor.a = 245;
						} else if (drawObjects[inputManager->click[i].id].yOrig < rect.y + 251){
							toolColor.r = 255;
							toolColor.g = 236;
							toolColor.b = 139;
							toolColor.a = 245;
						} else {
							toolColor.r = 250;
							toolColor.g = 240;
							toolColor.b = 230;
							toolColor.a = 245;
						}
						menu->UpdatePos(20000, 20000);
						for (int g = 0; g < 4; g++){
							if (menuSelect[g] != NULL){
								menuSelect[g]->UpdatePos(20000, 20000);
							}
						}
						drawObjects[inputManager->click[i].id].drawing = false;
						inputManager->click[i].release = true;
					} else {
						//Test overlap to erase objects
						if(currentTool == erase){
							Object* delObj;
							delObj = engine->EraseObject(drawObjects[inputManager->click[i].id].xOrig, drawObjects[inputManager->click[i].id].yOrig);
							if(delObj != NULL){
								for(Uint32 i = 0; i < objects.size() ; i++){
									if(objects.at(i)->GetBody() == (delObj->body)){
										objects.erase(objects.begin()+i);
										engine->DestroyObject(*delObj);
										break;
									}
								}
							}
							drawObjects[inputManager->click[i].id].drawing = false;
							inputManager->click[i].release = true;
						//Drawing or Mousejoint
						} else {
							engine->MouseDown(drawObjects[inputManager->click[i].id].xOrig, drawObjects[inputManager->click[i].id].yOrig, inputManager->click[i].id);
							if (engine->mouseJoint[inputManager->click[i].id] != NULL) {
								drawObjects[inputManager->click[i].id].drawing = false;
								inputManager->click[i].release = true;
							}
	//						if (engine->mouseJoint[inputManager->click[i].id] == NULL) {
	//							cout << "drawing vira true " << endl;
	//							drawObjects[inputManager->click[i].id].drawing = true;
	//							if(currentTool == freeform){
	//								ff_vx[inputManager->click[i].id].push_back(drawObjects[inputManager->click[i].id].xOrig);
	//								ff_vy[inputManager->click[i].id].push_back(drawObjects[inputManager->click[i].id].yOrig);
	//							}
	//							inputManager->xy.clear();
	//						}
						}
					}
				} else {
					//Test overlap to erase objects
					if(currentTool == erase){
						Object* delObj;
						delObj = engine->EraseObject(drawObjects[inputManager->click[i].id].xOrig, drawObjects[inputManager->click[i].id].yOrig);
						if(delObj != NULL){
							for(Uint32 i = 0; i < objects.size() ; i++){
								if(objects.at(i)->GetBody() == (delObj->body)){
									objects.erase(objects.begin()+i);
									engine->DestroyObject(*delObj);
									break;
								}
							}
						}
						drawObjects[inputManager->click[i].id].drawing = false;
						inputManager->click[i].release = true;
					//Drawing or Mousejoint
					} else {
						engine->MouseDown(drawObjects[inputManager->click[i].id].xOrig, drawObjects[inputManager->click[i].id].yOrig, inputManager->click[i].id);
						if (engine->mouseJoint[inputManager->click[i].id] != NULL) {
							drawObjects[inputManager->click[i].id].drawing = false;
							inputManager->click[i].release = true;
						}
	//					if (engine->mouseJoint[inputManager->click[i].id] == NULL) {
	//						cout << "drawing vira true " << endl;
	//						drawObjects[inputManager->click[i].id].drawing = true;
	//						if(currentTool == freeform){
	//							ff_vx[inputManager->click[i].id].push_back(drawObjects[inputManager->click[i].id].xOrig);
	//							ff_vy[inputManager->click[i].id].push_back(drawObjects[inputManager->click[i].id].yOrig);
	//						}
	//						inputManager->xy.clear();
	//					}
					}
				}
			}
//		} else {
			//Mouse up to destroy joint
			if(inputManager->click[i].updated){//inputManager->isTouchUp(inputManager->click[i].id)){
				if(engine->mouseJoint[inputManager->click[i].id] != NULL){
					engine->DestroyMouseJoint(inputManager->click[i].id);
					inputManager->xy.clear();
					drawObjects[inputManager->click[i].id].drawing = false;
					inputManager->click[i].release = true;
				}
			//Update grabbed object with mouse position
			} else if(engine->mouseJoint[inputManager->click[i].id] != NULL){
//				b2Vec2 p(CONVERT(inputManager->touchPosX(inputManager->click[i].id)), CONVERT(inputManager->touchPosY(inputManager->click[i].id)));
				b2Vec2 p(CONVERT(inputManager->click[i].x), CONVERT(inputManager->click[i].y));
				engine->mouseJoint[inputManager->click[i].id]->SetTarget(p);
				drawObjects[inputManager->click[i].id].drawing = false;
				inputManager->click[i].release = true;
			}
//		}
		if ((time - inputManager->click[i].time) > TIMELIMIT) {
			drawObjects[inputManager->click[i].id].menu = false;
			inputManager->click[i].release = true;

			drawObjects[inputManager->click[i].id].drawing = true;
			if(currentTool == freeform){
				ff_vx[inputManager->click[i].id].push_back(drawObjects[inputManager->click[i].id].xOrig);
				ff_vy[inputManager->click[i].id].push_back(drawObjects[inputManager->click[i].id].yOrig);
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
							drawObjects[inputManager->click[j].id].xOrig = inputManager->click[j].x;
							drawObjects[inputManager->click[j].id].yOrig = inputManager->click[j].y;
							drawObjects[inputManager->click[j].id].menu = true;
							drawObjects[inputManager->click[j].id].drawing = false;
							inputManager->click[i].remove = true;
							inputManager->click[i].release = false;
							inputManager->click[j].release = true;
							break;
						}
					}
				}
			}
		}
	}
	for(int i = 0; i < inputManager->getNumIds(); i++){
		id = inputManager->getId(i);
		cout << "levelstate tratando id " << id << ", drawing: " << drawObjects[id].drawing << ", menu: " << drawObjects[id].menu << endl;
		if(drawObjects[id].drawing){
			if(inputManager->isKeyDown(SDLK_ESCAPE)){
				drawObjects[id].drawing = false;
			}else if(inputManager->isTouchUp(id)){
				vector<int> vx, vy;
				GOTriangle* t;
				GORectangle* r;
				GOFreeform* ff;
				GOCircle* c;
				switch(currentTool){
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
					t = new GOTriangle(vx, vy, toolColor, dynamic);
					objects.push_back(t);
					break;
				case rectangle:
					vx.push_back(drawObjects[id].xOrig);
					vy.push_back(drawObjects[id].yOrig);
					vx.push_back(drawObjects[id].xMouse);
					vy.push_back(drawObjects[id].yMouse);
					r = new GORectangle(vx, vy, toolColor, dynamic);
					objects.push_back(r);
					break;
				case circle:
					vx.push_back(drawObjects[id].xOrig);
					vy.push_back(drawObjects[id].yOrig);
					vx.push_back(drawObjects[id].xMouse);
					vy.push_back(drawObjects[id].yMouse);
					c = new GOCircle(vx, vy, toolColor, dynamic);
					objects.push_back(c);
					break;
				case freeform:
					vx = ff_vx[id];
					vy = ff_vy[id];
					ff = new GOFreeform(vx, vy, toolColor, dynamic, thickness);
					ff_vx[id].clear();
					ff_vy[id].clear();
					inputManager->xy.clear();
					objects.push_back(ff);
					break;
				}

				drawObjects[id].drawing = false;

			}else if(currentTool == freeform){
			//Free form should have all the coordinates of a series of circles
				if(inputManager->isTouching(id)){
					if(id == 10000){
						if((ff_vx[id].back() != drawObjects[id].xMouse)|| (ff_vy[id].back() != drawObjects[id].yMouse)){
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
				if (menu != NULL) {
					delete menu;
				}
				menu = new ImageLoader("menutemp.jpg", drawObjects[id].xOrig, drawObjects[id].yOrig);
				rect = menu->GetRect();
				if ((rect.x + rect.w) > WIDTH){
					menu->UpdatePos(rect.x-rect.w, rect.y);
					rect = menu->GetRect();
				}
				if ((rect.y + rect.h) > HEIGHT){
					menu->UpdatePos(rect.x, rect.y-rect.h);
					rect = menu->GetRect();
				}
				if (dynamic) {
					menuSelect[0] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 29);
				} else {
					menuSelect[0] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 9);
				}
				if (currentTool == freeform){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 51);
				} else if (currentTool == circle){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 71);
				} else if (currentTool == rectangle){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 89);
				} else if (currentTool == triangle){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 110);
				} else {
					menuSelect[1] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 127);
				}
				if (!bgMusic->isPlaying()){
					menuSelect[2] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 146);
				} else {
					if (menuSelect[2] != NULL){
						delete menuSelect[2];
					}
				}
				if (toolColor.g == 15){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 166);
				} else if (toolColor.g == 39){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 183);
				} else if (toolColor.g == 255){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 200);
				} else if (toolColor.g == 34){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 217);
				} else if (toolColor.g == 236){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 234);
				} else {
					menuSelect[3] = new ImageLoader("menutempselect.jpg", rect.x, rect.y + 251);
				}
				drawObjects[id].menu = false;
			} else {
				//Mouse up to destroy joint
				if(inputManager->isTouchUp(id)){
					if(engine->mouseJoint[id] != NULL){
						engine->DestroyMouseJoint(id);
						inputManager->xy.clear();
					}
				//Update grabbed object with mouse position
				} else if(engine->mouseJoint[id] != NULL){
					b2Vec2 p(CONVERT(inputManager->touchPosX(id)), CONVERT(inputManager->touchPosY(id)));
					engine->mouseJoint[id]->SetTarget(p);
				}
			}
		}
	}

	//Objects update
	for(Uint32 i = 0; i < objects.size() ; i++){
		if(objects.at(i)->Update() > 2000){
			objects.erase(objects.begin()+i);
		}
	}
	//World update
	engine->Update();
	return 0;
}

void LevelState::Render(SDL_Surface * screen){
	int id;

	background->Render(screen);

	for(int i = 0; i < inputManager->getNumIds(); i++){
		id = inputManager->getId(i);
		if(drawObjects[id].drawing){

			drawObjects[id].xMouse = inputManager->touchPosX(id);
			drawObjects[id].yMouse = inputManager->touchPosY(id);

			if(inputManager->isTouching(id)){
				vector<int> vx, vy;
				switch(currentTool){
				case triangle:
					// Mouse point above from origin
					if(drawObjects[id].yMouse < drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Mouse point at left from origin
							graphics->DrawTriangle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, ((drawObjects[id].xOrig-drawObjects[id].xMouse)/2)+drawObjects[id].xMouse, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yOrig, toolColor);
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Mouse point at right from origin
							graphics->DrawTriangle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, ((drawObjects[id].xMouse-drawObjects[id].xOrig)/2)+drawObjects[id].xOrig, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yOrig, toolColor);
						}
					// Mouse point below from origin
					}else if(drawObjects[id].yMouse > drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Mouse point at left from origin
							graphics->DrawTriangle(screen, ((drawObjects[id].xOrig-drawObjects[id].xMouse)/2)+drawObjects[id].xMouse, drawObjects[id].yOrig, drawObjects[id].xOrig, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yMouse, toolColor);
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Mouse point at right from origin
							graphics->DrawTriangle(screen, ((drawObjects[id].xMouse-drawObjects[id].xOrig)/2)+drawObjects[id].xOrig, drawObjects[id].yOrig, drawObjects[id].xOrig, drawObjects[id].yMouse, drawObjects[id].xMouse, drawObjects[id].yMouse, toolColor);
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
					graphics->DrawRectangle(screen, vx, vy, toolColor);
					break;
				case circle:
					if(drawObjects[id].yMouse < drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Ponto do mouse a esquerda da origem
							if((drawObjects[id].xOrig-drawObjects[id].xMouse)>(drawObjects[id].yOrig-drawObjects[id].yMouse)){
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xOrig-drawObjects[id].xMouse), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yOrig-drawObjects[id].yMouse), toolColor);
							}
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Ponto do mouse a direita da origem
							if((drawObjects[id].xMouse-drawObjects[id].xOrig)>(drawObjects[id].yOrig-drawObjects[id].yMouse)){
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xMouse-drawObjects[id].xOrig), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yOrig-drawObjects[id].yMouse), toolColor);
							}
						}
					}else if(drawObjects[id].yMouse > drawObjects[id].yOrig){
						if(drawObjects[id].xMouse < drawObjects[id].xOrig){
							// Ponto do mouse a esquerda da origem
							if((drawObjects[id].xOrig-drawObjects[id].xMouse)>(drawObjects[id].yMouse-drawObjects[id].yOrig)){
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xOrig-drawObjects[id].xMouse), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yMouse-drawObjects[id].yOrig), toolColor);
							}
						}else if(drawObjects[id].xMouse > drawObjects[id].xOrig){
							// Ponto do mouse a direita da origem
							if((drawObjects[id].xMouse-drawObjects[id].xOrig)>(drawObjects[id].yMouse-drawObjects[id].yOrig)){
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].xMouse-drawObjects[id].xOrig), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id].xOrig, drawObjects[id].yOrig, (drawObjects[id].yMouse-drawObjects[id].yOrig), toolColor);
							}
						}
					}
					break;
				case freeform:
						for(Uint32 i = 0 ; i < ff_vx[id].size() ; i++){
							graphics->DrawCircle(screen, ff_vx[id].at(i), ff_vy[id].at(i), (int)thickness, toolColor);
						}
					break;
				}
			}
		}
	}
	for(Uint32 i = 0; i < objects.size() ; i++){
		objects.at(i)->Render(screen);
	}
	fechar->Render(screen);
	if (menu != NULL) {
		menu->Render(screen);
	}
	for (int i = 0; i < 4; i++) {
		if (menuSelect[i] != NULL) {
			menuSelect[i]->Render(screen);
		}
	}
}
