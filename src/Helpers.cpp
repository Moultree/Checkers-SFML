#include <SFML/Graphics.hpp>
#include "PieceTypes.h"

using namespace sf;
using namespace std;

static const int START_POS = 96;
static const int BOARD_SIZE = 512;
static const int SQUARE_SIZE = 64;

static Vector2i PLAY_BUTTON_LEFT_CORNER = { 496,648 };
static Vector2i PLAY_BUTTON_RIGHT_CORNER = { 648,691 };

static Vector2i RESET_BUTTON_LEFT_CORNER = { 592,648 };
static Vector2i RESET_BUTTON_RIGHT_CORNER = { 635,691 };

static Vector2f BLACK_REMAINING_POSITION = { 125,29 };
static Vector2f WHITE_REMAINING_POSITION = { 125,659 };

static BoardIndex toBoardIndex(Vector2i vector)
{
	return make_pair((vector.x - START_POS) / SQUARE_SIZE, (vector.y - START_POS) / SQUARE_SIZE);
}

static Vector2i toVector2i(BoardIndex index)
{
	return Vector2i((index.first) * SQUARE_SIZE + START_POS, (index.second) * SQUARE_SIZE + START_POS);
}