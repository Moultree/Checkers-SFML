#pragma once

#include <SFML/Graphics.hpp>

#include "PieceTypes.h"
#include "Game.h"
#include "Piece.h"

using namespace std;
using namespace sf;

class SceneRenderer
{
private:
	void buildBoard();
	void drawBoard();

	void drawPieces();
	void drawSpriteForWinning();
	void drawTextForWinning();
	void buildText(Text&, PieceTypes);
	void drawText();

	void drawMoves();

	BoardIndex index;

	RenderTarget* target;
	Game* game;
	bool temp = false;
	Font font;
	Text textRemainingWhite;
	Text textRemainingBlack;
	Text textForWinning;
	Texture boardTexture;
	Sprite boardSprite;

	Texture forWinningTexture;
	Sprite forWinningSprite;
	string strForWinning;
public:
	SceneRenderer(RenderTarget& _target, Game* _game);
	~SceneRenderer();

	void draw();
	BoardIndex getPieceIndex(Vector2i);

	void onMouseHolding(BoardIndex, Vector2i);
	void onMouseRelease(BoardIndex, Vector2i);

	bool isOnPlayButton(Vector2i);
	void play();

	bool isOnResetButton(Vector2i);
	void reset();
};