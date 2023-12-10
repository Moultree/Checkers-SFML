#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "PieceTypes.h"

#pragma warning(disable: 4996)

using namespace std;
using namespace sf;

struct PieceMove;

class Game
{
private:
	PieceTypes turn;

	vector<vector<Piece*>> pieces;

	void setup();

	void movePiece(Piece*, PieceMove);


	void jumpPiece(Piece*, PieceMove);

	void switchTurns();

	bool isLegalPieceMove(PieceMove);

	bool isLegalMove(PieceMove, bool);

	bool isLegalJump(PieceMove, bool);

	bool isKingableIndex(BoardIndex, PieceTypes);

	void promoteToKing(Piece*);

	vector<BoardIndex> getEnemyPieces(PieceMove);

	vector<BoardIndex> getAvailableJumps(BoardIndex);

	bool containsPiece(BoardIndex);
	bool containsPiece(Vector2i);

	bool containsEnemyPiece(BoardIndex);
	bool containsEnemyPiece(Vector2i);

	bool containsPlayerPiece(BoardIndex);
	bool containsPlayerPiece(Vector2i);
public:
	Game();
	~Game();
	void play();

	void reset();

	bool isGameOver();
	void dragPiece(BoardIndex, Vector2i);

	void releasePiece(BoardIndex, Vector2i);

	Piece* getPiece(int, int);

	int getRemainingCount(PieceTypes);


	bool isValidIndex(Vector2i);
	bool isValidIndex(BoardIndex);

	vector<BoardIndex> getAvailableMoves(BoardIndex);
};



struct PieceMove
{
	PieceMove(BoardIndex _source, BoardIndex _destination);
	PieceMove(BoardIndex _source, int _hDirection, int _vDirection);

	BoardIndex source;
	BoardIndex destination;

	int verticalDistance;
	int horizontalDistance;

	int verticalDirection;
	int horizontalDirection;

	int length;
};