#include "GameMap.h"

GameMap::GameMap() {

	//World = new GameWorld();


	Init();
//	LoadMap();

}

void GameMap::Init() {

	World = new GameWorld;

	LoadMap();

}