#include "Checker.h"

//Adds black and white checkers to the board
//Adds blank checkers (shown with . int the game) to empty spcaes 
CheckerBoard::CheckerBoard() : NumberOfBlackCheckers(12), NumberOfWhiteCheckers(12)
{
	Checker temp;
	Checker Empty;

	for (int i = 1; i <= 3; i++)
	{
		Board.push_back(std::vector<Checker>());

		for (int j = 1; j <= 8; j++)
		{
			if (((i + j) % 2) == 0)
			{
				temp = Checker('o', i, j, "Black", false);
				Board[i - 1].push_back(temp);
			}
			else
			{
				Empty = Checker('.', i, j, ".blank", false);
				Board[i - 1].push_back(Empty);
			}
		}
	}

	for (int  i = 4; i <= 5; i++)
	{
		Board.push_back(std::vector<Checker>());

		for (int j = 1; j <= 8; j++)
		{
			Empty = Checker('.', i, j, ".blank", false);
			Board[i - 1].push_back(Empty);
		}
	}

	for (int i = 6; i <= 8; i++)
	{
		Board.push_back(std::vector<Checker>());

		for (int j = 1; j <= 8; j++)
		{
			if (((i + j) % 2) == 0)
			{
				temp = Checker('w', i, j, "White", false);
				Board[i - 1].push_back(temp);
			}
			else
			{
				Empty = Checker('.', i, j, ".blank", false);
				Board[i - 1].push_back(Empty);
			}
		}
	}
}

void CheckerBoard::DrawBoard() const
{
	char counter = 'a';

	std::cout << "\n\n\n\n\n\n";
	std::cout << "       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
	std::cout << "       X                                           X" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << "  " << counter << "    X   ";
		for (int j = 0; j < 8; j++)
		{
			std::cout << Board[i][j].ReturnSymbol() << "    ";
		}
		std::cout << "X" << std::endl;
		std::cout << "       X                                           X" << std::endl;
		counter++;
	}
	std::cout << "       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl << std::endl;
	std::cout << "           1    2    3    4    5    6    7    8" << std::endl << std::endl;
}

std::string CheckerBoard::IsWon() const
{
	if (NumberOfBlackCheckers == 0)
	{
		return "White";
	}

	else if (NumberOfWhiteCheckers == 0)
	{
		return "Black";
	}

	return "no";
}

char CheckerBoard::IsEmpty(const int row, const int column) const
{
	return Board[row - 1][column - 1].ReturnSide();
}

void CheckerBoard::CallCalculations()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Board[i][j].ReturnSide() != '.')
			{
				Board[i][j].CalculatePossibleMoves(*this);
				Board[i][j].CalculatePossibleKills(*this);
			}
		}
	}
}

const Checker* CheckerBoard::ReturnChecker(const int Row, const int Column) const
{
	return &Board[Row - 1][Column - 1];
}

bool CheckerBoard::Move(const int oRow, const int oColumn, const int nRow, const int nColumn)
{
	bool HasKill = false;

	if (Board[oRow - 1][oColumn - 1].IsInMoveSet(nRow, nColumn) == "kill")
	{
		Checker kill('.', (oRow + nRow) / 2, (oColumn + nColumn) / 2, ".blank", false);
		Board[(oRow + nRow) / 2 - 1][(oColumn + nColumn) / 2 - 1] = kill;

		if (Board[(oRow + nRow) / 2 - 1][(oColumn + nColumn) / 2 - 1].ReturnSide() == 'W')
		{
			NumberOfWhiteCheckers--;
		}
		else
		{
			NumberOfBlackCheckers--;
		}

		HasKill = true;
	}

	Checker temp = Board[nRow - 1][nColumn - 1];
	Board[nRow - 1][nColumn - 1] = Board[oRow - 1][oColumn - 1];
	Board[nRow - 1][nColumn - 1].MoveTo(nRow, nColumn);
	Board[oRow - 1][oColumn - 1] = temp;
	Board[oRow - 1][oColumn - 1].MoveTo(oRow, oColumn);

	this->CallCalculations();
	return HasKill;
}

bool CheckerBoard::CanKill(const int Row, const int Column) const
{
	return Board[Row - 1][Column - 1].CanKill();
}