#include "Checker.h"
#include <string>
#include <iostream>


using namespace std;

/***************************
Asking user which checker (s)he wants to move and where (s)he wants it
returns true if taken is in correct format
***************************/
bool TakeInputs(int& FromRow, int& FromColumn, int& ToRow, int& ToColumn, const char Turn, const CheckerBoard& Board)
{
	string From, To;
	cout << "Please enter the adress of the checker you want to move and where you want to move it: ";
	cin >> From >> To;

	//Length check for given adresses
	if (From.length() != 2 || To.length() != 2)
	{
		cout << "Adress of the checker you want to move and adress of the place you want to go must be a 2-lettered code! " << endl << endl;
		return false;
	}

	//Checking Letter-part of the given adresses
	if (From.at(0) < 'a' || From.at(0) > 'h' || To.at(0) < 'a' || To.at(0) > 'h')
	{
		cout << "Adresses can only start with the letters between \"a-h\"! " << endl << endl;
		return false;
	}

	//Checking number part of the given adresses
	if (From.at(1) < '1' || From.at(1) > '8' || To.at(1) < '1' || To.at(1) > '8')
	{
		cout << "Adresses can only end with numbers between \"1-8\"! " << endl << endl;
		return false;
	}

	//Checking if given adress really contains that players checker
	if (Board.IsEmpty((int)From.at(0) - 'a' + 1, (int)From.at(1) - '0') != Turn)
	{
		cout << "You do not have any checker at position: " << From << "! " << endl << endl;
		return false;
	}

	//Checking if that checker can move to given location
	if (Board.ReturnChecker((int)From.at(0) - 'a' + 1, (int)From.at(1) - '0')->IsInMoveSet((int)To.at(0) - 'a' + 1, (int)To.at(1) - '0') == "no")
	{
		cout << "The checker you have at " << From << " can not go to " << To << "! " << endl << endl;
		return false;
	}

	FromRow = (int)From.at(0) - 'a' + 1;
	FromColumn = (int)From.at(1) - '0';

	ToRow = (int)To.at(0) - 'a' + 1;
	ToColumn = (int)To.at(1) - '0';

	return true;
}

/***************************
called Only when player has checked a checker and has another possible check
asking for only aimed location since same checker has to be played again
returns true taken adress is in correct format
***************************/
bool TakeInputs(int& ToRow, int& ToColumn, const char Turn, const CheckerBoard& Board)
{
	string To, From;
	cout << "Please enter where you want to move your active checker at position: " << (char)(ToRow + 'a' - 1) << ToColumn << endl;
	From += (char)ToRow + 'a' - 1;
	From += (char)ToColumn + '1' - 1;
	cin >> To;
	
	//Length check for given adress
	if (To.length() != 2)
	{
		cout << "Adress of the place you want to move your checker must be 2-lettered code! " << endl;
		return false;
	}

	//Checking Letter-part of the given adress
	if (To.at(0) < 'a' || To.at(0) > 'h')
	{
		cout << "Adresses can only start with the letters between \"a-h\"! " << endl << endl;
		return false;
	}

	//Checking number part of the given adress
	if (To.at(1) < '1' || To.at(1) > '8')
	{
		cout << "Adresses can only end between numbers \"1-8\"! " << endl << endl;
		return false;
	}

	//Checking if that checker can move to given location
	if (Board.ReturnChecker((int)From.at(0) - 'a' + 1, (int)From.at(1) - '0')->IsInMoveSet((int)To.at(0) - 'a' + 1, (int)To.at(1) - '0') != "kill")
	{
		cout << "The checker you have at " << From << " can not go to " << To << "! " << endl << endl;
		return false;
	}

	ToRow = (int)To.at(0) - 'a' + 1;
	ToColumn = (int)To.at(1) - '0';

	return true;
}


int main()
{

	/***************************
	Creating gameboard
	Calculating where checkers can move
	Setting turn
	***************************/
	CheckerBoard Board;
	Board.CallCalculations();
	char Turn = 'W';
	bool HasKill = false;

	
	/***************************
	Game loop continues as long as one player looses his(her) all pieces
	***************************/

	while (Board.IsWon() == "no")
	{
		/***************************
		Drawing board to screen
		Announcing players whose turn it is
		resetting variables for the start of the turn
		***************************/

		HasKill = false;
		Board.DrawBoard();
		cout << "it is " << Turn << "'s turn." << endl;
		
		int FromRow, FromColumn, ToRow, ToColumn;
		bool IsCorrect = TakeInputs(FromRow, FromColumn, ToRow, ToColumn, Turn, Board);
		while (!IsCorrect)
		{
			IsCorrect = TakeInputs(FromRow, FromColumn, ToRow, ToColumn, Turn, Board);
		}


		/***************************
		After taking correct input recalculating locations of checkers and their possible moves
		***************************/

		HasKill = Board.Move(FromRow, FromColumn, ToRow, ToColumn);
		while (HasKill && Board.CanKill(ToRow, ToColumn))
		{	
			/***************************
			if player has checked a checer and still has another possible check
				taking another input from user until possible checks are finished
				Drawing board and racalculating checkers locations and possible moves
				Turn doesn't chage during his process
			***************************/

			Board.DrawBoard();
			std::cout << "You checked a checker. You can check a checker again! " << std::endl;
			FromRow = ToRow;
			FromColumn = ToColumn;
			bool IsCorrect2 = TakeInputs(ToRow, ToColumn, Turn, Board);
			while (!IsCorrect2)
			{
				bool IsCorrect2 = TakeInputs(ToRow, ToColumn, Turn, Board);
			}
			HasKill = Board.Move(FromRow, FromColumn, ToRow, ToColumn);
		}

		/***************************
		Move of the player has ended changing turns
		***************************/

		if (Turn == 'W')
		{
			Turn = 'B';
		}
		else if(Turn == 'B')
		{
			Turn = 'W';
		}
	}

	/***************************
	After someone has won showing the ending table and announcing who won
	***************************/
	
	Board.DrawBoard();
	cout << endl << endl;
	cout << "Congratulations \"" << Board.IsWon() << " Team\" has won!!!!!!" << endl;

	return 0;
}