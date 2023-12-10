
#include "AppController.h"
#include "Game.h"
#include "PieceTypes.h"
#include "ResourcePath.h"
#include "SceneRenderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

AppController::AppController()
    : window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Checkers"), sceneRenderer(window, &game), game()
{
    started = false;
    holding = false;
}

void AppController::run()
{
    sf::Image appIcon;
    if (appIcon.loadFromFile(getResourcePath("black_piece_king.png")))
    {
		//add Window icon
        auto dims = appIcon.getSize();
        window.setIcon(dims.x, dims.y, appIcon.getPixelsPtr());
    }
    while (window.isOpen())
    {
        draw();
        processEvents();
    }
}

void AppController::draw()
{
    window.clear();
    sceneRenderer.draw();
    window.display();
}

void AppController::processEvents()
{

    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }
    if (!game.isGameOver() && started)
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (!holding)
            {
                pieceIndex = sceneRenderer.getPieceIndex(Mouse::getPosition(window));
                if (pieceIndex.first != -1 && pieceIndex.second != -1)
                    holding = true;
            }
            if (holding)
            {
                Vector2i mousePosition(Mouse::getPosition(window).x - 32, Mouse::getPosition(window).y - 32);
                sceneRenderer.onMouseHolding(pieceIndex, mousePosition);
            }
        }

        if (!Mouse::isButtonPressed(Mouse::Left) && holding)
        {
            sceneRenderer.onMouseRelease(pieceIndex, Mouse::getPosition(window));
            holding = false;
        }
    }

    if (Mouse::isButtonPressed(Mouse::Left) && sceneRenderer.isOnPlayButton(Mouse::getPosition(window)) && !started)
    {
        sceneRenderer.play();
        started = true;
    }

    if (Mouse::isButtonPressed(Mouse::Left) && sceneRenderer.isOnResetButton(Mouse::getPosition(window)) && started)
    {
        sceneRenderer.reset();
    }
}