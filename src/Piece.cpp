#include "Piece.h"
#include "ResourcePath.h"
#include "PieceTypes.h"

// Constructors

Piece::Piece()
{

}

Piece::Piece(Vector2i _coordinates, PieceTypes _type)
{
	sprite.setPosition((Vector2f)_coordinates);
	type = _type;
}

Piece::~Piece()
{

}

// Getters

PieceTypes Piece::getType()
{
	return type;
}

Vector2i Piece::getCoordinates()
{
	return (Vector2i)sprite.getPosition();
}

// Setters

void Piece::setType(PieceTypes _type)
{
	type = _type;
}

void Piece::setCoordinates(Vector2i _coordinates)
{
	sprite.setPosition((Vector2f)_coordinates);
}

void Piece::setCoordinates(int x, int y)
{
	return setCoordinates(Vector2i(x, y));
}

void Piece::setTexture()
{
	switch (getType())
	{
	case BLACK:
		texture.loadFromFile(getResourcePath("black_piece.png"));
		break;
	case WHITE:
		texture.loadFromFile(getResourcePath("white_piece.png"));
		break;
	case BLACK_KING:
		texture.loadFromFile(getResourcePath("black_piece_king.png"));
		break;
	case WHITE_KING:
		texture.loadFromFile(getResourcePath("/white_piece_king.png"));
		break;
	}

	sprite.setTexture(texture);
}

// Drawable

void Piece::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(sprite, state);
}