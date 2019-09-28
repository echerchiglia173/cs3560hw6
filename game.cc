///@file game.cc

#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include "game.h"     // Provides definition of game class
using namespace std;


namespace main_savitch_14
{

//*************************************************************************
// STATIC MEMBER CONSTANTS
// const int game::SEARCH_LEVELS;

//*************************************************************************
// PUBLIC MEMBER FUNCTIONS

/** A normal member with return type enum
 * plays one round of the game
 * @see display_status()
 * @see countingPieces()
 * @see make_human_move()
 * @see make_computer_move()
 * @return The winner of the game or neutral for a tie
 */
game::who game::play( )
// The play function should not be overridden. It plays one round of the
// game, with the human player moving first and the computer second.
// The return value is the winner of the game (or NEUTRAL for a tie).
{
	restart( );

	while (!is_game_over( ))
	{
		display_status( );
		whosTurn();
		if (last_mover( ) == COMPUTER) {
			countingPieces();
			make_human_move( );
		}
		else {
			make_computer_move( );
		}
	}
	display_status( );
	return HUMAN;
}



//*************************************************************************
// OPTIONAL VIRTUAL FUNCTIONS (overriding these functions is optional)

/**
 * A virtual member function taking a string and outputing it to the screen.
 * @param message a constant refrence string
 */

void game::display_message(const string& message) const
{
	cout << message;
}

/**
 * A virtual member that gets the user move and returns a string
 * @see display_message()
 * @return the userer move as a string
 */
string game::get_user_move( ) const
{
	string answer;

	display_message("If you cannot move, please press 'S'\n");
	display_message("Your move, please: ");
	getline(cin, answer);
	return answer;
}

/**
 * A virtual member that returns emu vlaue of type who for th person winning.
 * based on the value from evaluate
 * @see evaluate()
 * @return returns the name of the perosn winning or neutral if it is a tie
 */
game::who game::winning()const {

	int value = evaluate();

	if (value > 0) {
		return last_mover();
	} else if (value < 0) {
		return next_mover();
	} else {
		return NEUTRAL;
	}

}


// PRIVATE FUNCTIONS (these are the same for every game)

/**
 * Private member taking two argument and returning an integer value.
 * Evaluates the board postion  with lookahead for a single move recursively
 * Evaluating the opnets moves and the computers moves, to see the outcome after so many moves were made.
 * @see is_game_over()
 * @see last_mover()
 * @see compute_moves()
 * @see make_move()
 * @param  look_ahead as an integer for how deep it should go to evaluate the move
 * @param  beat_this as a integer for the calue of another move
 * @return THe value is larger if the position is good for the player who just moved
 */
int game::eval_with_lookahead(int look_ahead, int beat_this)
// Evaluates a board position with lookahead.
// --int look_aheads:  How deep the lookahead should go to evaluate the move.
// --int beat_this: Value of another move that we're considering. If the
// current board position can't beat this, then cut it short.
// The return value is large if the position is good for the player who just
// moved.
{
	queue<string> moves;   // All possible opponent moves
	int value;             // Value of a board position after opponent moves
	int best_value;        // Evaluation of best opponent move
	game* future;          // Pointer to a future version of this game

	// Base case:
	if (look_ahead == 0 || is_game_over( ))
	{
		if (last_mover( ) == COMPUTER)
			return evaluate( );
		else
			return -evaluate( );
	}

	// Recursive case:
	// The level is above 0, so try all possible opponent moves. Keep the
	// value of the best of these moves from the opponent's perspective.
	compute_moves(moves);
	// assert(!moves.empty( ));
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
		future = clone( );
		future->make_move(moves.front( ));
		value = future->eval_with_lookahead(look_ahead - 1, best_value);
		delete future;
		if (value > best_value)
		{
			if (-value <= beat_this)
				return INT_MIN + 1; // Alpha-beta pruning
			best_value = value;
		}
		moves.pop( );
	}

	// The value was calculated from the opponent's perspective.
	// The answer we return should be from player's perspective, so multiply times -1:
	return -best_value;
}
///@breif private member that takes the computers turn.
/**
 * Determines the best move for the computer by finding all of the moves that can be made.
 * Then evaluating each move and saving the best move to be made at the end.
 * @see compute_moves()
 * @see eval_with_lookahead()
 *
 */
void game::make_computer_move( )
{
	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	game* future;

	// Compute all legal moves that the computer could make.
	compute_moves(moves);
	//assert(!moves.empty( ));

	// Evaluate each possible legal move, saving the index of the best
	// in best_index and saving its value in best_value.
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
		future = clone( );
		future->make_move(moves.front( ));
		value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
		delete future;
		if (value >= best_value)
		{
			best_value = value;
			best_move = moves.front( );
		}
		moves.pop( );
	}

	// Make the best move.
	make_move(best_move);
}

/**
 * Privat member that makes the move for the user. Input the move the user want to make and the makes sure its a legal move.
 * if its not legal it reasj for a move. Once the move is legal that move is made.
 * @see get_user_move()
 * @see is_legal()
 * @see  make_move()
 */

void game::make_human_move( ) {
	string move;

	move = get_user_move( );
	while (!is_legal(move))
	{
		display_message("Illegal move.\n");
		move = get_user_move( );
	}
	make_move(move);
}

}
