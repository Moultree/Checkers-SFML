#pragma once
#include <SFML/Graphics.hpp>

#include "PieceTypes.h"

using namespace std;
using namespace sf;

class Piece : public Drawable
{
private:
	PieceTypes type;

	Texture texture;
	Sprite sprite;

	virtual	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
public:
	Piece();
	Piece(Vector2i, PieceTypes);
	~Piece();

	PieceTypes getType();
	Vector2i getCoordinates();

	void setType(PieceTypes _type);
	void setCoordinates(Vector2i);
	void setCoordinates(int x, int y);
	void setTexture();
};