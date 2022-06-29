#pragma once

#include <SFML/Graphics.hpp>
#include "SceneRenderer.h"
#include "PieceTypes.h"

using namespace std;
using namespace sf;

class AppController
{
private:
	const int WINDOW_SIZE = 704;
	RenderWindow window;
	SceneRenderer sceneRenderer;
	Game game;

	bool started;
	bool holding;
	BoardIndex pieceIndex;

public:
	AppController();

	void run();
	void draw();
	void processEvents();
};