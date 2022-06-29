#include <cmath>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Game.h"
#include "Piece.h"
#include "PieceTypes.h"
#include "Helpers.cpp"
using namespace std;
using namespace sf;

#pragma warning(disable: 4996)

Game::Game()
{
	turn = BLACK;
	pieces = vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr));
}

Game::~Game()
{

}

void Game::setup()
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if ((row + col) % 2)
			{
				if (row == 3 || row == 4) {
					pieces[col][row] = nullptr;
				}
				else
				{
					Vector2i coordinates = toVector2i(BoardIndex(col, row));
					PieceTypes color = row < 3 ? WHITE : BLACK;
					pieces[col][row] = new Piece(coordinates, color);
				}
			}
		}
	}
}

void Game::play()
{
	setup();
}

void Game::reset()
{
	pieces.clear();
	pieces = vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr));
	turn = BLACK;

	setup();
}
bool Game::isGameOver()
{
	if (getRemainingCount(WHITE) == 0 || getRemainingCount(BLACK) == 0)
		return true;

	bool cantMove = true;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (pieces[row][col] == nullptr) continue;

			if (turn == BLACK)
				if (pieces[row][col]->getType() == WHITE && pieces[row][col]->getType() == WHITE_KING)
					continue;
				else
					if (pieces[row][col]->getType() == BLACK && pieces[row][col]->getType() == BLACK_KING)
						continue;

			if (getAvailableMoves(BoardIndex(row, col)).size() != 0)
				cantMove = false;
		}
	}

	if (cantMove)
		return true;

	return false;
}

void Game::movePiece(Piece* piece, PieceMove move)
{
	swap(pieces[move.source.first][move.source.second],
		pieces[move.destination.first][move.destination.second]);

	piece->setCoordinates(toVector2i(move.destination));

	if (isKingableIndex(move.destination, piece->getType()))
		promoteToKing(piece);

	switchTurns();
}

void Game::jumpPiece(Piece* piece, PieceMove move)
{
	vector<BoardIndex> enemyIndex = getEnemyPieces(move);
	pieces[enemyIndex[0].first][enemyIndex[0].second] = nullptr;

	swap(pieces[move.source.first][move.source.second],
		pieces[move.destination.first][move.destination.second]);
	piece->setCoordinates(toVector2i(move.destination));

	if (isKingableIndex(move.destination, piece->getType()))
		promoteToKing(piece);

	if (getAvailableJumps(move.destination).size() == 0)
		switchTurns();
}

void Game::switchTurns()
{
	turn = turn == BLACK ? WHITE : BLACK;
}

bool Game::isLegalPieceMove(PieceMove move)
{
	if (!isValidIndex(move.source) && !isValidIndex(move.destination))
		return false;

	if (abs(move.horizontalDirection) != abs(move.verticalDirection))
		return false;

	if (!containsPlayerPiece(move.source))
		return false;

	if (containsPiece(move.destination))
		return false;

	return true;
}

bool Game::isLegalMove(PieceMove move, bool isKing)
{
	if (!isLegalPieceMove(move))
		return false;

	if (move.length != 1 && !isKing)
		return false;

	if (!isKing && ((move.verticalDirection > 0 && turn == BLACK) ||
		(move.verticalDirection < 0 && turn == WHITE)))
		return false;

	if (isKing && getEnemyPieces(move).size() != 0)
		return false;

	return true;
}

bool Game::isLegalJump(PieceMove move, bool isKing)
{
	if (!isLegalPieceMove(move))
		return false;

	if (move.length != 2 && !isKing)
		return false;

	if (getEnemyPieces(move).size() != 1)
		return false;

	return true;
}

bool Game::isKingableIndex(BoardIndex index, PieceTypes type)
{
	return (index.second == 0 && type == BLACK) || (index.second == 7 && type == WHITE);
}

void Game::promoteToKing(Piece* piece)
{
	if (piece->getType() == BLACK)
	{
		piece->setType(BLACK_KING);
	}
	else
	{
		piece->setType(WHITE_KING);
	}
}

vector<BoardIndex> Game::getEnemyPieces(PieceMove move)
{
	vector<BoardIndex> indexes;

	for (int i = 1; i < move.length; i++)
	{
		BoardIndex index = BoardIndex(
			move.source.first + move.horizontalDirection * i,
			move.source.second + move.verticalDirection * i
		);

		if (containsEnemyPiece(index))
		{
			indexes.push_back(index);
		}
	}

	return indexes;
}

vector<BoardIndex> Game::getAvailableMoves(BoardIndex index)
{
	vector<BoardIndex> moves;

	if (!isValidIndex(index) || pieces[index.first][index.second] == nullptr)
		return moves;

	PieceTypes type = pieces[index.first][index.second]->getType();
	bool isKing = type == BLACK_KING || type == WHITE_KING;

	// Top Left
	for (int x = index.first, y = index.second; x >= 0 && y >= 0; x--, y--)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing) || isLegalMove(move, isKing))
			moves.push_back(move.destination);
	}
	// Top right
	for (int x = index.first, y = index.second; x <= 7 && y >= 0; x++, y--)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing) || isLegalMove(move, isKing))
			moves.push_back(move.destination);
	}
	// Bottom Left
	for (int x = index.first, y = index.second; x >= 0 && y <= 7; x--, y++)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing) || isLegalMove(move, isKing))
			moves.push_back(move.destination);
	}
	// Bottom Right
	for (int x = index.first, y = index.second; x <= 7 && y <= 7; x++, y++)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing) || isLegalMove(move, isKing))
			moves.push_back(move.destination);
	}

	return moves;
}

vector<BoardIndex> Game::getAvailableJumps(BoardIndex index)
{
	vector<BoardIndex> jumps;
	PieceTypes type = pieces[index.first][index.second]->getType();
	bool isKing = type == BLACK_KING || type == WHITE_KING;

	// Top Left
	for (int x = index.first, y = index.second; x >= 0 && y >= 0; x--, y--)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing))
			jumps.push_back(move.destination);
	}
	// Top right
	for (int x = index.first, y = index.second; x <= 7 && y >= 0; x++, y--)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing))
			jumps.push_back(move.destination);
	}
	// Bottom Left
	for (int x = index.first, y = index.second; x >= 0 && y <= 7; x--, y++)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing))
			jumps.push_back(move.destination);
	}
	// Bottom Right
	for (int x = index.first, y = index.second; x <= 7 && y <= 7; x++, y++)
	{
		PieceMove move(index, BoardIndex(x, y));
		if (isLegalJump(move, isKing))
			jumps.push_back(move.destination);
	}

	return jumps;
}

bool Game::containsPiece(Vector2i vectorPosition)
{
	BoardIndex index = toBoardIndex(vectorPosition);
	return containsPiece(index);
}

bool Game::containsPiece(BoardIndex index)
{
	if (!isValidIndex(index))
		return false;

	return pieces[index.first][index.second] != nullptr;
}

bool Game::containsEnemyPiece(Vector2i vectorPosition)
{
	return containsEnemyPiece(toBoardIndex(vectorPosition));
}

bool Game::containsEnemyPiece(BoardIndex index)
{
	if (!containsPiece(index))
		return false;

	PieceTypes type = pieces[index.first][index.second]->getType();

	return turn == BLACK ? (type == WHITE || type == WHITE_KING) : (type == BLACK || type == BLACK_KING);
}

bool Game::containsPlayerPiece(Vector2i vectorPosition)
{
	return containsPlayerPiece(toBoardIndex(vectorPosition));
}

bool Game::containsPlayerPiece(BoardIndex index)
{
	if (!containsPiece(index))
		return false;

	PieceTypes type = pieces[index.first][index.second]->getType();

	return turn == BLACK ? (type == BLACK || type == BLACK_KING) : (type == WHITE || type == WHITE_KING);
}

bool Game::isValidIndex(Vector2i vectorPosition)
{
	return vectorPosition.x >= START_POS
		&& vectorPosition.x <= START_POS + BOARD_SIZE
		&& vectorPosition.y >= START_POS
		&& vectorPosition.y <= START_POS + BOARD_SIZE;
}

bool Game::isValidIndex(BoardIndex index)
{
	return index.first >= 0
		&& index.first <= 7
		&& index.second >= 0
		&& index.second <= 7;
}

int Game::getRemainingCount(PieceTypes type)
{
	int sum = 0;
	if (type == BLACK)
	{
		for (int row = 0; row < pieces.size(); row++)
		{
			sum += count_if(pieces[row].begin(), pieces[row].end(), [](Piece* piece) {
				if (piece == nullptr) return false;
				return piece->getType() == WHITE || piece->getType() == WHITE_KING;
				});
		}
	}
	else
	{
		for (int row = 0; row < pieces.size(); row++)
		{
			sum += count_if(pieces[row].begin(), pieces[row].end(), [](Piece* piece) {
				if (piece == nullptr) return false;
				return piece->getType() == BLACK || piece->getType() == BLACK_KING;
				});
		}
	}

	return sum;
}

Piece* Game::getPiece(int row, int col)
{
	return pieces[row][col];
}

void Game::dragPiece(BoardIndex pieceIndex, Vector2i mousePosition)
{
	if (pieces[pieceIndex.first][pieceIndex.second] == nullptr)
		return;

	pieces[pieceIndex.first][pieceIndex.second]->setCoordinates(mousePosition);
}

void Game::releasePiece(BoardIndex pieceIndex, Vector2i mousePosition)
{
	PieceMove move(pieceIndex, toBoardIndex(mousePosition));

	if (pieces[pieceIndex.first][pieceIndex.second] == nullptr)
	{
		return;
	}

	Piece* piece = pieces[pieceIndex.first][pieceIndex.second];
	bool isKing = piece->getType() == BLACK_KING || piece->getType() == WHITE_KING;

	if (!isValidIndex(mousePosition))
	{
		piece->setCoordinates(toVector2i(pieceIndex));
	}
	else if (isLegalJump(move, isKing))
	{
		jumpPiece(piece, move);
	}
	else if (isLegalMove(move, isKing))
	{
		movePiece(piece, move);
	}
	else
	{
		piece->setCoordinates(toVector2i(pieceIndex));
	}
}

PieceMove::PieceMove(BoardIndex _source, BoardIndex _destination)
{
	source = _source;
	destination = _destination;

	horizontalDistance = destination.first - source.first;
	verticalDistance = destination.second - source.second;

	horizontalDirection = (horizontalDistance > 0) - (horizontalDistance < 0);
	verticalDirection = (verticalDistance > 0) - (verticalDistance < 0);

	length = max(abs(horizontalDistance), abs(verticalDistance));
}

PieceMove::PieceMove(BoardIndex _source, int _hDirection, int _vDirection)
{
	source = _source;
	destination = source;

	horizontalDistance = destination.first - source.first;
	verticalDistance = destination.second - source.second;

	horizontalDirection = _hDirection;
	verticalDirection = _vDirection;

	length = 0;
}


