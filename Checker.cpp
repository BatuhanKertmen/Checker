#include "Checker.h"



Checker::Checker(char Symbol, int Row, int Column, std::string Side, bool King) : Symbol(Symbol), Row(Row), Column(Column), Side(Side), King(King) {}

char Checker::ReturnSide() const
{
	return Side.at(0);
}

char Checker::ReturnSymbol() const
{
	return Symbol;
}

void Checker::CalculatePossibleMoves(const CheckerBoard& Board)
{
	PossibleMoves.clear();
	Location temp;

	if (Side == "White")
	{
		if (Row != 1 && Column != 1 && Board.IsEmpty(Row - 1, Column - 1) == '.')
		{
			temp = Location(Row - 1, Column - 1);
			PossibleMoves.push_back(temp);
		}

		if (Row != 1 && Column != 8 && Board.IsEmpty(Row - 1, Column + 1) == '.')
		{
			temp = Location(Row - 1, Column + 1);
			PossibleMoves.push_back(temp);
		}

		if(King)
		{
			if (Row != 8 && Column != 1 && Board.IsEmpty(Row + 1, Column - 1) == '.')
			{
				temp = Location(Row + 1, Column - 1);
				PossibleMoves.push_back(temp);
			}

			if (Row != 8 && Column != 8 && Board.IsEmpty(Row + 1, Column + 1) == '.')
			{
				temp = Location(Row + 1, Column + 1);
				PossibleMoves.push_back(temp);
			}
		}
	}
	else if (Side == "Black")
	{
		if (Row != 8 && Column != 1 && Board.IsEmpty(Row + 1, Column - 1) == '.')
		{
			temp = Location(Row + 1, Column - 1);
			PossibleMoves.push_back(temp);
		}

		if (Row != 8 && Column != 8 && Board.IsEmpty(Row + 1, Column + 1) == '.')
		{
			temp = Location(Row + 1, Column + 1);
			PossibleMoves.push_back(temp);
		}

		if (King)
		{
			if (Row != 1 && Column != 1 && Board.IsEmpty(Row - 1, Column - 1) == '.')
			{
				temp = Location(Row - 1, Column - 1);
				PossibleMoves.push_back(temp);
			}

			if (Row != 1 && Column != 8 && Board.IsEmpty(Row - 1, Column + 1) == '.')
			{
				temp = Location(Row - 1, Column + 1);
				PossibleMoves.push_back(temp);
			}
		}
	}
}

void Checker::CalculatePossibleKills(const CheckerBoard& Board)
{
	PossibleKills.clear();
	Location temp;

	if (Side == "White")
	{
		if (Row >= 3 && Column >= 3 && Board.IsEmpty(Row - 1, Column - 1) == 'B' && Board.IsEmpty(Row - 2,Column - 2) == '.')
		{
			temp = Location(Row - 2, Column - 2);
			PossibleKills.push_back(temp);
		}

		if (Row >= 3 && Column <= 6 && Board.IsEmpty(Row - 1, Column + 1) == 'B' && Board.IsEmpty(Row - 2, Column + 2) == '.')
		{
			temp = Location(Row - 2, Column + 2);
			PossibleKills.push_back(temp);
		}
		
		if (King)
		{
			if (Row <= 6 && Column >= 23 && Board.IsEmpty(Row + 1, Column - 1) == 'B' && Board.IsEmpty(Row + 2, Column - 2) == '.')
			{
				temp = Location(Row + 2, Column - 2);
				PossibleKills.push_back(temp);
			}

			if (Row <= 6 && Column <= 6 && Board.IsEmpty(Row + 1, Column + 1) == 'B' && Board.IsEmpty(Row + 2, Column + 2) == '.')
			{
				temp = Location(Row + 2, Column + 2);
				PossibleKills.push_back(temp);
			}
		}
	}
	else if (Side == "Black")
	{
		if (Row <= 6 && Column >= 3 && Board.IsEmpty(Row + 1, Column - 1) == 'W' && Board.IsEmpty(Row + 2, Column - 2) == '.')
		{
			temp = Location(Row + 2, Column - 2);
			PossibleKills.push_back(temp);
		}

		if (Row <= 6 && Column <= 6 && Board.IsEmpty(Row + 1, Column + 1) == 'W' && Board.IsEmpty(Row + 2, Column + 2) == '.')
		{
			temp = Location(Row + 2, Column + 2);
			PossibleKills.push_back(temp);
		}

		if (King)
		{
			if (Row >= 3 && Column >= 3 && Board.IsEmpty(Row - 1, Column - 1) == 'W' && Board.IsEmpty(Row - 2, Column - 2) == '.')
			{
				temp = Location(Row - 2, Column - 2);
				PossibleKills.push_back(temp);
			}

			if (Row >= 3 && Column <= 6 && Board.IsEmpty(Row - 1, Column + 1) == 'W' && Board.IsEmpty(Row - 2, Column + 2) == '.')
			{
				temp = Location(Row - 2, Column + 2);
				PossibleKills.push_back(temp);
			}
		}
	}
}

std::string Checker::IsInMoveSet(const int Row, const int Column) const
{
	Location temp(Row, Column);

	for (unsigned int i = 0; i < PossibleMoves.size(); i++)
	{
		if (PossibleMoves[i] == temp)
		{
			return "move";
		}
	}

	for (unsigned int i = 0; i < PossibleKills.size(); i++)
	{
		if (PossibleKills[i] == temp)
		{
			return "kill";
		}
	}

	return "no";
}

void Checker::MoveTo(const int GivenRow, const int GivenColumn)
{
	Row = GivenRow;
	Column = GivenColumn;

	if (Side == "White" && GivenRow == 1)
	{
		King = true;
		Symbol = 'W';
	}
	else if (Side == "Black" && GivenRow == 8)
	{
		King = true;
		Symbol = 'O';
	}

}

bool Checker::CanKill() const
{
	if (PossibleKills.size() > 0)
	{
		return true;
	}
	return false;
}