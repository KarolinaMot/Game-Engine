#pragma once
#include <vector>

class Layer
{
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};


class GameMap
{
	public:
		void Render() {
			for (unsigned int i = 0; i < mapLayers.size(); i++){
				mapLayers[i]->Render();
			}
		}
		void Update() {
			for (unsigned int i = 0; i < mapLayers.size(); i++){
				mapLayers[i]->Update();
			}
		}
		std::vector<Layer*>GetMapLayers() {
			return mapLayers;
		}

	private:
		std::vector<Layer*> mapLayers;
};

