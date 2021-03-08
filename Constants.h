#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

enum LayerType {
	BACKGROUND_LAYER = 0,
	LAYER_2 = 1,
	LAYER_3 = 2,
	PLAYER_LAYER = 3,
	LAYER_5 = 4,
	LAYER_6 = 5
};

const unsigned int NUM_LAYERS = 6;

#endif
