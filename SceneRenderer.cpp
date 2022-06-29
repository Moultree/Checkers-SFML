#include <SFML/Graphics.hpp>
#include <string>
#include "SceneRenderer.h"
#include "PieceTypes.h"
#include "Game.h"
#include "Piece.h"
#include "Helpers.cpp"
#include "AppController.h"
using namespace std;
using namespace sf;

SceneRenderer::SceneRenderer(RenderTarget& _target, Game* _game)
	: target(&_target)
	, game(_game)
{
	index = BoardIndex(-1, -1);
}

SceneRenderer::~SceneRenderer()
{

}

void SceneRenderer::buildBoard()
{
	boardTexture.loadFromFile("resources/board.png");
	boardSprite.setTexture(boardTexture);
}

void SceneRenderer::drawBoard()
{
	buildBoard();
	target->draw(boardSprite);
}

void SceneRenderer::drawPieces()
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (game->getPiece(row, col) == nullptr) continue;

			game->getPiece(row, col)->setTexture();
			target->draw(*(game->getPiece(row, col)));
		}
	}
}

void SceneRenderer::buildText(Text& text, PieceTypes type)
{
	font.loadFromFile("resources/minecraft.ttf");
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(Color::Black);
	string remainingCount = game->getRemainingCount(type) < 10 ? "0" + to_string(game->getRemainingCount(type)) : to_string(game->getRemainingCount(type));
	text.setString(remainingCount);
	text.setPosition(type == BLACK ? BLACK_REMAINING_POSITION : Vector2f(WHITE_REMAINING_POSITION));
}

void SceneRenderer::drawText()
{
	buildText(textRemainingBlack, BLACK);
	buildText(textRemainingWhite, WHITE);
	target->draw(textRemainingBlack);
	target->draw(textRemainingWhite);
}

void SceneRenderer::drawMoves()
{
	vector<BoardIndex> moves = game->getAvailableMoves(index);

	if (moves.size() == 0)
		return;

	Texture t;
	Sprite shadow;
	t.loadFromFile("resources/move.png");
	for (int i = 0; i < moves.size(); i++)
	{
		shadow.setTexture(t);
		shadow.setPosition((Vector2f)toVector2i(moves[i]));
		target->draw(shadow);
	}
}

void SceneRenderer::drawSpriteForWinning() {
	forWinningTexture.loadFromFile("resources/winning.png");
	forWinningSprite.setTexture(forWinningTexture);
	forWinningSprite.setPosition(257, 299);
	target->draw(forWinningSprite);
}
void SceneRenderer::drawTextForWinning() {
	font.loadFromFile("resources/minecraft.ttf");
	textForWinning.setFont(font);
	textForWinning.setCharacterSize(16);
	textForWinning.setFillColor(Color::Black);
	textForWinning.setPosition(303, 365);
	if (game->getRemainingCount(WHITE) == 0 || game->getRemainingCount(BLACK) == 0) {
		strForWinning = game->getRemainingCount(WHITE) == WHITE ? "White wins" : "Black wins";
	}
	else {
		strForWinning = "Drawn game";
	}
	textForWinning.setString(strForWinning);
	target->draw(textForWinning);

}

void SceneRenderer::draw()
{
	drawBoard();
	drawMoves();
	drawPieces();
	drawText();
	if (game->isGameOver() && temp) {
		drawSpriteForWinning();
		drawTextForWinning();
	}
}

BoardIndex SceneRenderer::getPieceIndex(Vector2i mousePosition)
{
	if (!game->isValidIndex(mousePosition))
		return make_pair(-1, -1);
	return toBoardIndex(mousePosition);
}

void SceneRenderer::onMouseHolding(BoardIndex pieceIndex, Vector2i mousePosition)
{
	index = pieceIndex;
	game->dragPiece(pieceIndex, mousePosition);
}

void SceneRenderer::onMouseRelease(BoardIndex pieceIndex, Vector2i mousePosition)
{
	index = BoardIndex(-1, -1);
	game->releasePiece(pieceIndex, mousePosition);
}

bool SceneRenderer::isOnPlayButton(Vector2i mousePosition)
{
	return mousePosition.x >= PLAY_BUTTON_LEFT_CORNER.x
		&& mousePosition.x <= PLAY_BUTTON_RIGHT_CORNER.x
		&& mousePosition.y >= PLAY_BUTTON_LEFT_CORNER.y
		&& mousePosition.y <= PLAY_BUTTON_RIGHT_CORNER.y;
}

bool SceneRenderer::isOnResetButton(Vector2i mousePosition)
{
	return mousePosition.x >= RESET_BUTTON_LEFT_CORNER.x
		&& mousePosition.x <= RESET_BUTTON_RIGHT_CORNER.x
		&& mousePosition.y >= RESET_BUTTON_LEFT_CORNER.y
		&& mousePosition.y <= RESET_BUTTON_RIGHT_CORNER.y;
}

void SceneRenderer::play()
{
	temp = true;
	game->play();
}

void SceneRenderer::reset()
{
	game->reset();
}