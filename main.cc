///@file main.cc
// Brock Ferrell
// CS2401
// November 23, 2015
// Project7
/// includes game.h
#include "game.h"
///includes othello.h
#include "othello.h"
using namespace main_savitch_14;

/// this is the main program that will run the game/ restart the game/ and play the game
int main()
{
/// This command will run the game
	Othello theGame;
	///This command will restart the game using the game
	theGame.restart();
	///this command with play the game
	theGame.play();
}
