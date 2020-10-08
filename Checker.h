#ifndef _Checker_H
#define _Checker_H

#include <string>
#include <vector>
#include <iostream>

class CheckerBoard;

/***************************
Class in order to stimulate an instance of checker
***************************/
class Checker
{
private:

	struct Location
	{
		int Row;
		int Column;

		Location(int row = 0, int column = 0) : Row(row), Column(column) {}
		
		bool operator== (const Location& rhs) const
		{
			if (Row == rhs.Row && Column == rhs.Column)
			{
				return true;
			}
			return false;
		}
	};

	char Symbol;
	int Row;
	int Column;
	bool King;
	std::string Side;
	std::vector<Location> PossibleMoves;
	std::vector<Location> PossibleKills;


public:

	Checker(char Symbol = 'o', int Row = 0, int Column = 0, std::string Side = "White", bool King = false);

	//returns from which team this checker is 
	char ReturnSide() const;
	
	//returns checker's symbol in order to print to board 
	char ReturnSymbol() const;

	// returns what happens when checker moves to given location (move, kill, no)  
	std::string IsInMoveSet(const int Row, const int Column) const;
	
	// checks if checker has any check potential
	bool CanKill() const;



	// adds all possible locations this checker move without checking can to a vector
	void CalculatePossibleMoves(const CheckerBoard& Board);

	// adds all possible locations this checker can move with checking to a vector
	void CalculatePossibleKills(const CheckerBoard& Board);

	// changes checker's adress to given location 
	void MoveTo(const int GivenRow, const int GivenColumn);
};


/***************************
Class in order to stimulate an 8x8 gameboard
***************************/
class CheckerBoard
{
public:

	// Creates a 8x8 game board with Checker objects placed with classic checker setup
	CheckerBoard();

	// Draws board to screen
	void DrawBoard() const;

	// Returns which team won, returns "no" if game is not won yet
	std::string IsWon() const;

	// Returns checkers symbol at given adress
	char IsEmpty(const int row, const int Column) const;

	// Returns a pointor for the checker at given adress
	const Checker* ReturnChecker(const int Row, const int Column) const;

	// Checks if checker located at given adress has check potential
	bool CanKill(const int Row, const int Column) const;

	
	
	
	// Calls neceseary calculations
	void CallCalculations();

	// Swaps the location of checkes at the given adresses
	// During Move proccess if checker checks another checker checked checker is turned into a blnak checker 
	bool Move(const int oRow, const int oColumn, const int nRow, const int nColumn);


private:

	std::vector<std::vector<Checker>> Board;
	int NumberOfWhiteCheckers;
	int NumberOfBlackCheckers;

};

#endif