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
//	dinamico = new ImageLoader("D.png",0,0);
//	estatico = new ImageLoader("E2.png",0,75);
//	formalivre = new ImageLoader("freeform2.png",0,150);
//	circulo = new ImageLoader("BOLA.png",0,225);
//	retangulo = new ImageLoader("retangulo.png",0,300);
//	triangulo = new ImageLoader("triangulo.png",0,375);
//	borracha = new ImageLoader("B1.png",0,450);
//	musica = new ImageLoader("music.png",0,525);
//	vermelho = new ImageLoader("red.png",0,600);
//	azul = new ImageLoader("blue.png",37,600);
//	verde = new ImageLoader("green.png",74,600);
//	amarelo = new ImageLoader("yellow.png",0,637);
//	preto = new ImageLoader("black2.png",37,637);
//	branco = new ImageLoader("white.png",74,637);
	fechar = new ImageLoader("Fechar.png",(background->GetRect().w-25),3);
	bgMusic = new Audio("Wesnothmusic.ogg",1); //Background Music
	bgMusic->Play(-1);
//	toolColor.r = 0;
//	toolColor.g = 0;
//	toolColor.b = 0;
//	toolColor.a = 255;
	toolColor.r = 15;
	toolColor.g = 15;
	toolColor.b = 15;
	toolColor.a = 245;
	currentTool = freeform;
	dynamic = false;
	thickness = 5;
}

void LevelState::Unload(){
	delete background;
//	delete dinamico;
//	delete estatico;
//	delete circulo;
//	delete retangulo;
//	delete triangulo;
//	delete borracha;
	delete fechar;
//	delete musica;
//	delete vermelho;
//	delete azul;
//	delete verde;
//	delete amarelo;
//	delete preto;
//	delete branco;
	delete bgMusic;
}

int LevelState::Update(){
	int id;
	SDL_Rect rect;

	for(Uint32 i = 0; i < inputManager->click.size(); i++){
		if((inputManager->click[i].updated) && (!inputManager->click[i].remove)){
			for (Uint32 j = i+1; j < inputManager->click.size(); j++) {
				if((inputManager->click[j].updated) && (!inputManager->click[j].remove)){
					if((inputManager->click[j].time - inputManager->click[i].time) < TIMELIMIT){
						if ((inputManager->click[j].x > (inputManager->click[i].x - MENUPROX)) &&
								(inputManager->click[j].x < (inputManager->click[i].x + MENUPROX)) &&
								(inputManager->click[j].y > (inputManager->click[i].y - MENUPROX)) &&
								(inputManager->click[j].y < (inputManager->click[i].y + MENUPROX))){
							if(drawObjects[inputManager->click[j].id] == NULL){
								drawObjects[inputManager->click[j].id] = (DrawObject*) malloc(sizeof(DrawObject));
								drawObjects[inputManager->click[j].id]->drawing = false;
								drawObjects[inputManager->click[j].id]->menu = false;
								drawObjects[inputManager->click[j].id]->xMouse = 0;
								drawObjects[inputManager->click[j].id]->xOrig = 0;
								drawObjects[inputManager->click[j].id]->yMouse = 0;
								drawObjects[inputManager->click[j].id]->yOrig = 0;
							}
							drawObjects[inputManager->click[j].id]->menu = true;
							drawObjects[inputManager->click[j].id]->drawing = false;
							inputManager->click[j].remove = true;
							inputManager->click[i].remove = true;
							break;
						}
					}
				}
			}
		}
	}
	for(int i = 0; i < inputManager->getNumIds(); i++){
		id = inputManager->getId(i);
		if(drawObjects[id] == NULL){
			drawObjects[id] = (DrawObject*) malloc(sizeof(DrawObject));
			drawObjects[id]->drawing = false;
			drawObjects[id]->menu = false;
			drawObjects[id]->xMouse = 0;
			drawObjects[id]->xOrig = 0;
			drawObjects[id]->yMouse = 0;
			drawObjects[id]->yOrig = 0;
		}
		if(drawObjects[id]->drawing){
			if(inputManager->isKeyDown(SDLK_ESCAPE)){
				drawObjects[id]->drawing = false;
			}else if(inputManager->isTouchUp(id)){
				vector<int> vx, vy;
				GOTriangle* t;
				GORectangle* r;
				GOFreeform* ff;
				GOCircle* c;
				switch(currentTool){
				case triangle:
					// Mouse point above from origin
					if(drawObjects[id]->yMouse < drawObjects[id]->yOrig){
						if(drawObjects[id]->xMouse < drawObjects[id]->xOrig){
							// Mouse point at left from origin
							vx.push_back((((drawObjects[id]->xOrig-drawObjects[id]->xMouse)/2)+drawObjects[id]->xMouse));
							vy.push_back(drawObjects[id]->yMouse);
							vx.push_back(drawObjects[id]->xOrig);
							vy.push_back(drawObjects[id]->yOrig);
							vx.push_back(drawObjects[id]->xMouse);
							vy.push_back(drawObjects[id]->yOrig);
						}else if(drawObjects[id]->xMouse > drawObjects[id]->xOrig){
							// Mouse point at right from origin
							vx.push_back((((drawObjects[id]->xMouse-drawObjects[id]->xOrig)/2)+drawObjects[id]->xOrig));
							vy.push_back(drawObjects[id]->yMouse);
							vx.push_back(drawObjects[id]->xMouse);
							vy.push_back(drawObjects[id]->yOrig);
							vx.push_back(drawObjects[id]->xOrig);
							vy.push_back(drawObjects[id]->yOrig);
						}
						else{break;}
					// Mouse point below from origin
					}else if(drawObjects[id]->yMouse > drawObjects[id]->yOrig){
						if(drawObjects[id]->xMouse < drawObjects[id]->xOrig){
							// Mouse point at left from origin
							vx.push_back((((drawObjects[id]->xOrig-drawObjects[id]->xMouse)/2)+drawObjects[id]->xMouse));
							vy.push_back(drawObjects[id]->yOrig);
							vx.push_back(drawObjects[id]->xOrig);
							vy.push_back(drawObjects[id]->yMouse);
							vx.push_back(drawObjects[id]->xMouse);
							vy.push_back(drawObjects[id]->yMouse);
						}else if(drawObjects[id]->xMouse > drawObjects[id]->xOrig){
							// Mouse point at right from origin
							vx.push_back((((drawObjects[id]->xMouse-drawObjects[id]->xOrig)/2)+drawObjects[id]->xOrig));
							vy.push_back(drawObjects[id]->yOrig);
							vx.push_back(drawObjects[id]->xMouse);
							vy.push_back(drawObjects[id]->yMouse);
							vx.push_back(drawObjects[id]->xOrig);
							vy.push_back(drawObjects[id]->yMouse);
						}else{break;}
					}else{break;}
					t = new GOTriangle(vx, vy, toolColor, dynamic);
					objects.push_back(t);
					break;
				case rectangle:
					vx.push_back(drawObjects[id]->xOrig);
					vy.push_back(drawObjects[id]->yOrig);
					vx.push_back(drawObjects[id]->xMouse);
					vy.push_back(drawObjects[id]->yMouse);
					r = new GORectangle(vx, vy, toolColor, dynamic);
					objects.push_back(r);
					break;
				case circle:
					vx.push_back(drawObjects[id]->xOrig);
					vy.push_back(drawObjects[id]->yOrig);
					vx.push_back(drawObjects[id]->xMouse);
					vy.push_back(drawObjects[id]->yMouse);
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

				drawObjects[id]->drawing = false;

			}else if(currentTool == freeform){
			//Free form should have all the coordinates of a series of circles
				if(inputManager->isTouching(id)){
					if(id == 10000){
						//Test for finger movement
						if((ff_vx[id].back() != drawObjects[id]->xMouse)|| (ff_vy[id].back() != drawObjects[id]->yMouse)){
							ff_vx[id].push_back(drawObjects[id]->xMouse);
							ff_vy[id].push_back(drawObjects[id]->yMouse);
						}
					}else{
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
			//Test mouse or touch down
			if(drawObjects[id]->menu){
				if (menu != NULL) {
					delete menu;
				}
				menu = new ImageLoader("menutemp.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig);
				if (dynamic) {
					menuSelect[0] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 29);
				} else {
					menuSelect[0] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 9);
				}
				if (currentTool == freeform){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 51);
				} else if (currentTool == circle){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 71);
				} else if (currentTool == rectangle){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 89);
				} else if (currentTool == triangle){
					menuSelect[1] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 110);
				} else {
					menuSelect[1] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 127);
				}
				if (!bgMusic->isPlaying()){
					menuSelect[2] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 146);
				} else {
					if (menuSelect[2] != NULL){
						delete menuSelect[2];
					}
				}
				if (toolColor.g == 15){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 166);
				} else if (toolColor.g == 39){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 183);
				} else if (toolColor.g == 255){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 200);
				} else if (toolColor.g == 34){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 217);
				} else if (toolColor.g == 236){
					menuSelect[3] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 234);
				} else {
					menuSelect[3] = new ImageLoader("menutempselect.jpg", drawObjects[id]->xOrig, drawObjects[id]->yOrig + 251);
				}
				drawObjects[id]->menu = false;
			} else {
				if(inputManager->isTouched(id)){
					drawObjects[id]->xOrig = inputManager->touchPosX(id);
					drawObjects[id]->yOrig = inputManager->touchPosY(id);
					//Test overlap to erase objects
					if (inputManager->isTouchInside(fechar, id)){
						SDL_Event* event = new SDL_Event();
						event->type = SDL_QUIT;
						SDL_PushEvent(event);
						} else {
							if (menu != NULL) {
								if (inputManager->isTouchInside(menu, id)) {
									rect = menu->GetRect();
									if ((drawObjects[id]->xOrig >= rect.x) && (drawObjects[id]->xOrig <= rect.x + rect.w)
											&& (drawObjects[id]->yOrig >= rect.y) && (drawObjects[id]->yOrig <= rect.y + rect.h)){
										if (drawObjects[id]->yOrig < rect.y + 29){
											dynamic = false;
										} else if (drawObjects[id]->yOrig < rect.y + 51){
											dynamic = true;
										} else if (drawObjects[id]->yOrig < rect.y + 71){
											currentTool = freeform;
										} else if (drawObjects[id]->yOrig < rect.y + 89){
											currentTool = circle;
										} else if (drawObjects[id]->yOrig < rect.y + 110){
											currentTool = rectangle;
										} else if (drawObjects[id]->yOrig < rect.y + 127){
											currentTool = triangle;
										} else if (drawObjects[id]->yOrig < rect.y + 146){
											currentTool = erase;
										} else if (drawObjects[id]->yOrig < rect.y + 166){
											if(bgMusic->isPlaying()){
												bgMusic->Pause();
											}else{
												bgMusic->Resume();
											}
										} else if (drawObjects[id]->yOrig < rect.y + 183){
											toolColor.r = 15;
											toolColor.g = 15;
											toolColor.b = 15;
											toolColor.a = 245;
										} else if (drawObjects[id]->yOrig < rect.y + 200){
											toolColor.r = 235;
											toolColor.g = 39;
											toolColor.b = 37;
											toolColor.a = 245;
										} else if (drawObjects[id]->yOrig < rect.y + 217){
											toolColor.r = 34;
											toolColor.g = 255;
											toolColor.b = 34;
											toolColor.a = 245;
										} else if (drawObjects[id]->yOrig < rect.y + 234){
											toolColor.r = 34;
											toolColor.g = 34;
											toolColor.b = 255;
											toolColor.a = 245;
										} else if (drawObjects[id]->yOrig < rect.y + 251){
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
									}
								}
							}
							//						if (inputManager->isTouchInside(dinamico, id)){
							//							if (!dynamic) {
							//								delete dinamico;
							//								dinamico = new ImageLoader("D2.png",0,0);
							//								delete estatico;
							//								estatico = new ImageLoader("E.png",0,75);
							//							}
							//							dynamic = true;
							//						} else {
							//							if (inputManager->isTouchInside(estatico, id)){
							//								if (dynamic) {
							//									delete dinamico;
							//									dinamico = new ImageLoader("D.png",0,0);
							//									delete estatico;
							//									estatico = new ImageLoader("E2.png",0,75);
							//								}
							//								dynamic = false;
							//							} else {
							//								if (inputManager->isTouchInside(circulo, id)){
							//									if (currentTool == freeform){
							//										delete circulo;
							//										circulo = new ImageLoader("BOLA2.png",0,225);
							//										delete formalivre;
							//										formalivre = new ImageLoader("freeform.png",0,150);
							//									}else{
							//										if (currentTool == rectangle) {
							//											delete circulo;
							//											circulo = new ImageLoader("BOLA2.png",0,225);
							//											delete retangulo;
							//											retangulo = new ImageLoader("retangulo.png",0,300);
							//										} else {
							//											if (currentTool == triangle) {
							//												delete circulo;
							//												circulo = new ImageLoader("BOLA2.png",0,225);
							//												delete triangulo;
							//												triangulo = new ImageLoader("triangulo.png",0,375);
							//											} else {
							//												if (currentTool == erase) {
							//													delete circulo;
							//													circulo = new ImageLoader("BOLA2.png",0,225);
							//													delete borracha;
							//													borracha = new ImageLoader("B1.png",0,450);
							//												}
							//											}
							//										}
							//									}
							//									currentTool = circle;
							//								} else {
							//									if(inputManager->isTouchInside(formalivre, id)){
							//										if (currentTool == circle){
							//											delete formalivre;
							//											formalivre = new ImageLoader("freeform2.png",0,150);
							//											delete circulo;
							//											circulo = new ImageLoader("BOLA.png",0,225);
							//										}else{
							//											if (currentTool == rectangle) {
							//												delete formalivre;
							//												formalivre = new ImageLoader("freeform2.png",0,150);
							//												delete retangulo;
							//												retangulo = new ImageLoader("retangulo.png",0,300);
							//											} else {
							//												if (currentTool == triangle) {
							//													delete formalivre;
							//													formalivre = new ImageLoader("freeform2.png",0,150);
							//													delete triangulo;
							//													triangulo = new ImageLoader("triangulo.png",0,375);
							//												} else {
							//													if (currentTool == erase) {
							//														delete formalivre;
							//														formalivre = new ImageLoader("freeform2.png",0,150);
							//														delete borracha;
							//														borracha = new ImageLoader("B1.png",0,450);
							//													}
							//												}
							//											}
							//										}
							//										currentTool = freeform;
							//									}else{
							//										if (inputManager->isTouchInside(retangulo, id)){
							//											if (currentTool == freeform){
							//												delete retangulo;
							//												retangulo = new ImageLoader("retangulo2.png",0,300);
							//												delete formalivre;
							//												formalivre = new ImageLoader("freeform.png",0,150);
							//											}else{
							//												if (currentTool == circle) {
							//													delete circulo;
							//													circulo = new ImageLoader("BOLA.png",0,225);
							//													delete retangulo;
							//													retangulo = new ImageLoader("retangulo2.png",0,300);
							//												} else {
							//													if (currentTool == triangle) {
							//														delete retangulo;
							//														retangulo = new ImageLoader("retangulo2.png",0,300);
							//														delete triangulo;
							//														triangulo = new ImageLoader("triangulo.png",0,375);
							//													} else {
							//														if (currentTool == erase) {
							//															delete retangulo;
							//															retangulo = new ImageLoader("retangulo2.png",0,300);
							//															delete borracha;
							//															borracha = new ImageLoader("B1.png",0,450);
							//														}
							//													}
							//												}
							//											}
							//											currentTool = rectangle;
							//										} else {
							//											if (inputManager->isTouchInside(triangulo, id)){
							//												if (currentTool == freeform){
							//													delete triangulo;
							//													triangulo = new ImageLoader("triangulo2.png",0,375);
							//													delete formalivre;
							//													formalivre = new ImageLoader("freeform.png",0,150);
							//												}else{
							//													if (currentTool == rectangle) {
							//														delete triangulo;
							//														triangulo = new ImageLoader("triangulo2.png",0,375);
							//														delete retangulo;
							//														retangulo = new ImageLoader("retangulo.png",0,300);
							//													} else {
							//														if (currentTool == circle) {
							//															delete circulo;
							//															circulo = new ImageLoader("BOLA.png",0,225);
							//															delete triangulo;
							//															triangulo = new ImageLoader("triangulo2.png",0,375);
							//														} else {
							//															if (currentTool == erase) {
							//																delete triangulo;
							//																triangulo = new ImageLoader("triangulo2.png",0,375);
							//																delete borracha;
							//																borracha = new ImageLoader("B1.png",0,450);
							//															}
							//														}
							//													}
							//												}
							//												currentTool = triangle;
							//											} else {
							//												if (inputManager->isTouchInside(borracha, id)){
							//													if (currentTool == freeform){
							//														delete borracha;
							//														borracha = new ImageLoader("B2.png",0,450);
							//														delete formalivre;
							//														formalivre = new ImageLoader("freeform.png",0,150);
							//													}else{
							//														if (currentTool == rectangle) {
							//															delete borracha;
							//															borracha = new ImageLoader("B2.png",0,450);
							//															delete retangulo;
							//															retangulo = new ImageLoader("retangulo.png",0,300);
							//														} else {
							//															if (currentTool == triangle) {
							//																delete borracha;
							//																borracha = new ImageLoader("B2.png",0,450);
							//																delete triangulo;
							//																triangulo = new ImageLoader("triangulo.png",0,375);
							//															} else {
							//																if (currentTool == circle) {
							//																	delete circulo;
							//																	circulo = new ImageLoader("BOLA.png",0,225);
							//																	delete borracha;
							//																	borracha = new ImageLoader("B2.png",0,450);
							//																}
							//															}
							//														}
							//													}
							//													currentTool = erase;
							//												}else{
							//													//Changing colors
							//													if(inputManager->isTouchInside(vermelho, id)){
							//														delete vermelho;
							//														vermelho = new ImageLoader("red2.png",0,600);
							//														delete azul;
							//														azul = new ImageLoader("blue.png",37,600);
							//														delete verde;
							//														verde = new ImageLoader("green.png",74,600);
							//														delete amarelo;
							//														amarelo = new ImageLoader("yellow.png",0,637);
							//														delete preto;
							//														preto = new ImageLoader("black.png",37,637);
							//														delete branco;
							//														branco = new ImageLoader("white.png",74,637);
							//														toolColor.r = 235;
							//														toolColor.g = 39;
							//														toolColor.b = 37;
							//														toolColor.a = 245;
							//													}else if(inputManager->isTouchInside(azul, id)){
							//														delete vermelho;
							//														vermelho = new ImageLoader("red.png",0,600);
							//														delete azul;
							//														azul = new ImageLoader("blue2.png",37,600);
							//														delete verde;
							//														verde = new ImageLoader("green.png",74,600);
							//														delete amarelo;
							//														amarelo = new ImageLoader("yellow.png",0,637);
							//														delete preto;
							//														preto = new ImageLoader("black.png",37,637);
							//														delete branco;
							//														branco = new ImageLoader("white.png",74,637);
							//														toolColor.r = 34;
							//														toolColor.g = 34;
							//														toolColor.b = 255;
							//														toolColor.a = 245;
							//													}else if(inputManager->isTouchInside(verde, id)){
							//														delete vermelho;
							//														vermelho = new ImageLoader("red.png",0,600);
							//														delete azul;
							//														azul = new ImageLoader("blue.png",37,600);
							//														delete verde;
							//														verde = new ImageLoader("green2.png",74,600);
							//														delete amarelo;
							//														amarelo = new ImageLoader("yellow.png",0,637);
							//														delete preto;
							//														preto = new ImageLoader("black.png",37,637);
							//														delete branco;
							//														branco = new ImageLoader("white.png",74,637);
							//														toolColor.r = 34;
							//														toolColor.g = 255;
							//														toolColor.b = 34;
							//														toolColor.a = 245;
							//													}else if(inputManager->isTouchInside(amarelo, id)){
							//														delete vermelho;
							//														vermelho = new ImageLoader("red.png",0,600);
							//														delete azul;
							//														azul = new ImageLoader("blue.png",37,600);
							//														delete verde;
							//														verde = new ImageLoader("green.png",74,600);
							//														delete amarelo;
							//														amarelo = new ImageLoader("yellow2.png",0,637);
							//														delete preto;
							//														preto = new ImageLoader("black.png",37,637);
							//														delete branco;
							//														branco = new ImageLoader("white.png",74,637);
							//														toolColor.r = 255;
							//														toolColor.g = 236;
							//														toolColor.b = 139;
							//														toolColor.a = 245;
							//													}else if(inputManager->isTouchInside(preto, id)){
							//														delete vermelho;
							//														vermelho = new ImageLoader("red.png",0,600);
							//														delete azul;
							//														azul = new ImageLoader("blue.png",37,600);
							//														delete verde;
							//														verde = new ImageLoader("green.png",74,600);
							//														delete amarelo;
							//														amarelo = new ImageLoader("yellow.png",0,637);
							//														delete preto;
							//														preto = new ImageLoader("black2.png",37,637);
							//														delete branco;
							//														branco = new ImageLoader("white.png",74,637);
							//														toolColor.r = 15;
							//														toolColor.g = 15;
							//														toolColor.b = 15;
							//														toolColor.a = 245;
							//													}else if(inputManager->isTouchInside(branco, id)){
							//														delete vermelho;
							//														vermelho = new ImageLoader("red.png",0,600);
							//														delete azul;
							//														azul = new ImageLoader("blue.png",37,600);
							//														delete verde;
							//														verde = new ImageLoader("green.png",74,600);
							//														delete amarelo;
							//														amarelo = new ImageLoader("yellow.png",0,637);
							//														delete preto;
							//														preto = new ImageLoader("black.png",37,637);
							//														delete branco;
							//														branco = new ImageLoader("white2.png",74,637);
							//														toolColor.r = 250;
							//														toolColor.g = 240;
							//														toolColor.b = 230;
							//														toolColor.a = 245;
							//													}else if(inputManager->isTouchInside(musica, id)){
							//														delete musica;
							//														if(bgMusic->isPlaying()){
							//															bgMusic->Pause();
							//															musica = new ImageLoader("musicoff.png",0,525);
							//														}else{
							//															bgMusic->Resume();
							//															musica = new ImageLoader("music.png",0,525);
							//														}
							//													}else{
							if(currentTool == erase){
								Object* delObj;
								delObj = engine->EraseObject(drawObjects[id]->xOrig, drawObjects[id]->yOrig);
								if(delObj != NULL){
									for(Uint32 i = 0; i < objects.size() ; i++){
										if(objects.at(i)->GetBody() == (delObj->body)){
											objects.erase(objects.begin()+i);
											engine->DestroyObject(*delObj);
											break;
										}
									}
								}
							//Drawing or Mousejoint
							} else {
								engine->MouseDown(drawObjects[id]->xOrig, drawObjects[id]->yOrig, id);
								if (engine->mouseJoint[id] == NULL) {
									drawObjects[id]->drawing = true;
									if(currentTool == freeform){
										ff_vx[id].push_back(drawObjects[id]->xOrig);
										ff_vy[id].push_back(drawObjects[id]->yOrig);
									}
									inputManager->xy.clear();
								}
							}
	//													}
	//												}
	//											}
	//										}
	//									}
	//								}
	//							}
	//						}
	//					}
					}
				} else {
					//Mouse up to destroy joint
					if(inputManager->isTouchUp(id)){
						if(engine->mouseJoint[id] != NULL){
							engine->DestroyMouseJoint(id);
							inputManager->xy.clear();
						}
					//Update grabbed object with mouse position
					}else if(engine->mouseJoint[id] != NULL){
						b2Vec2 p(CONVERT(inputManager->touchPosX(id)), CONVERT(inputManager->touchPosY(id)));
						engine->mouseJoint[id]->SetTarget(p);
					}
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
		if(drawObjects[id]->drawing){

			drawObjects[id]->xMouse = inputManager->touchPosX(id);
			drawObjects[id]->yMouse = inputManager->touchPosY(id);

			if(inputManager->isTouching(id)){
				vector<int> vx, vy;
				switch(currentTool){
				case triangle:
					// Mouse point above from origin
					if(drawObjects[id]->yMouse < drawObjects[id]->yOrig){
						if(drawObjects[id]->xMouse < drawObjects[id]->xOrig){
							// Mouse point at left from origin
							graphics->DrawTriangle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, ((drawObjects[id]->xOrig-drawObjects[id]->xMouse)/2)+drawObjects[id]->xMouse, drawObjects[id]->yMouse, drawObjects[id]->xMouse, drawObjects[id]->yOrig, toolColor);
						}else if(drawObjects[id]->xMouse > drawObjects[id]->xOrig){
							// Mouse point at right from origin
							graphics->DrawTriangle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, ((drawObjects[id]->xMouse-drawObjects[id]->xOrig)/2)+drawObjects[id]->xOrig, drawObjects[id]->yMouse, drawObjects[id]->xMouse, drawObjects[id]->yOrig, toolColor);
						}
					// Mouse point below from origin
					}else if(drawObjects[id]->yMouse > drawObjects[id]->yOrig){
						if(drawObjects[id]->xMouse < drawObjects[id]->xOrig){
							// Mouse point at left from origin
							graphics->DrawTriangle(screen, ((drawObjects[id]->xOrig-drawObjects[id]->xMouse)/2)+drawObjects[id]->xMouse, drawObjects[id]->yOrig, drawObjects[id]->xOrig, drawObjects[id]->yMouse, drawObjects[id]->xMouse, drawObjects[id]->yMouse, toolColor);
						}else if(drawObjects[id]->xMouse > drawObjects[id]->xOrig){
							// Mouse point at right from origin
							graphics->DrawTriangle(screen, ((drawObjects[id]->xMouse-drawObjects[id]->xOrig)/2)+drawObjects[id]->xOrig, drawObjects[id]->yOrig, drawObjects[id]->xOrig, drawObjects[id]->yMouse, drawObjects[id]->xMouse, drawObjects[id]->yMouse, toolColor);
						}
					}
					break;
				case rectangle:
					vx.push_back(drawObjects[id]->xOrig);
					vy.push_back(drawObjects[id]->yOrig);
					vx.push_back(drawObjects[id]->xMouse);
					vy.push_back(drawObjects[id]->yOrig);
					vx.push_back(drawObjects[id]->xMouse);
					vy.push_back(drawObjects[id]->yMouse);
					vx.push_back(drawObjects[id]->xOrig);
					vy.push_back(drawObjects[id]->yMouse);
					graphics->DrawRectangle(screen, vx, vy, toolColor);
					break;
				case circle:
					if(drawObjects[id]->yMouse < drawObjects[id]->yOrig){
						if(drawObjects[id]->xMouse < drawObjects[id]->xOrig){
							// Ponto do mouse a esquerda da origem
							if((drawObjects[id]->xOrig-drawObjects[id]->xMouse)>(drawObjects[id]->yOrig-drawObjects[id]->yMouse)){
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->xOrig-drawObjects[id]->xMouse), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->yOrig-drawObjects[id]->yMouse), toolColor);
							}
						}else if(drawObjects[id]->xMouse > drawObjects[id]->xOrig){
							// Ponto do mouse a direita da origem
							if((drawObjects[id]->xMouse-drawObjects[id]->xOrig)>(drawObjects[id]->yOrig-drawObjects[id]->yMouse)){
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->xMouse-drawObjects[id]->xOrig), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->yOrig-drawObjects[id]->yMouse), toolColor);
							}
						}
					}else if(drawObjects[id]->yMouse > drawObjects[id]->yOrig){
						if(drawObjects[id]->xMouse < drawObjects[id]->xOrig){
							// Ponto do mouse a esquerda da origem
							if((drawObjects[id]->xOrig-drawObjects[id]->xMouse)>(drawObjects[id]->yMouse-drawObjects[id]->yOrig)){
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->xOrig-drawObjects[id]->xMouse), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->yMouse-drawObjects[id]->yOrig), toolColor);
							}
						}else if(drawObjects[id]->xMouse > drawObjects[id]->xOrig){
							// Ponto do mouse a direita da origem
							if((drawObjects[id]->xMouse-drawObjects[id]->xOrig)>(drawObjects[id]->yMouse-drawObjects[id]->yOrig)){
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->xMouse-drawObjects[id]->xOrig), toolColor);
							}else{
								graphics->DrawCircle(screen, drawObjects[id]->xOrig, drawObjects[id]->yOrig, (drawObjects[id]->yMouse-drawObjects[id]->yOrig), toolColor);
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
//	dinamico->Render(screen);
//	estatico->Render(screen);
//	formalivre->Render(screen);
//	circulo->Render(screen);
//	retangulo->Render(screen);
//	triangulo->Render(screen);
//	borracha->Render(screen);
	fechar->Render(screen);
//	musica->Render(screen);
//	vermelho->Render(screen);
//	azul->Render(screen);
//	verde->Render(screen);
//	amarelo->Render(screen);
//	preto->Render(screen);
//	branco->Render(screen);
	if (menu != NULL) {
		menu->Render(screen);
	}
	for (int i = 0; i < 4; i++) {
		if (menuSelect[i] != NULL) {
			menuSelect[i]->Render(screen);
		}
	}
}
