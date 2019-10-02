/// @file othello.h

// Brock Ferrell
// CS2401
// November 23, 2015
// Project7

#ifndef OTHELLO_H
#define OTHELLO_H
#include "game.h"
#include "piece.h"
#include "colors.h"
#include <iostream>
using namespace std;

namespace main_savitch_14
{
/// this is the othelo class using the game clas
class Othello: public game {
public:
	/// this is the constructor for the othello class
	Othello() {}
	void display_status()const;
	int evaluate()const;
	bool is_game_over()const;
	bool is_legal(const string& move)const;
	void make_move(const string& move);
	void restart();
	void make_skips();
	void countingPieces();
	void whosTurn();
	game* clone()const{return new Othello(*this);}
	void compute_moves(std::queue<std::string>& moves)const;
	who winning()const;

protected:
	int black;
	int white;
	int skips;
	int openSpots;
	int b;
	int w;

private:
	///this is a double array that identifies the gameboard
	piece gameBoard[8][8];
};
}

#endif
