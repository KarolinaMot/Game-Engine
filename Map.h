#pragma once
#include "Engine.h"
#include "EntityManager.h"
#include "TileComponent.h"
#include <fstream>
#include <string>
class Map
{
	private:
		std::string textureId;
		int scale;
		int tileSize;

	public:
		Map(std::string textureId, int scale, int tileSize);
		void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
		void AddTile(int sourceX, int sourceY, int x, int y);
};

