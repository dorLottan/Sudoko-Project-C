#include "sudokoBoardFuncs.h"
#include "helperFuncs.h"
#include "possibleCellsListsFuncs.h"

//This function creats an empty sudoko board
void createEmptySudokoBoard(short board[][COLSIZE])
{
	int row, col;
	for (row = 0; row < ROWSIZE; row++)
	{
		for (col = 0; col < COLSIZE; col++) {
			board[row][col] = -1;
		}
	}
}

//This function fills the board randomly according to the instructions in the question
Array ***randomFillSudokoBoard(short board[][COLSIZE])
{
	Array ***possibilities = PossibleDigits(board);
	int N = getRandomNumber(20), K, randomPossibleDigit;

	PossibleCellsList PCList;
	makeEmptyPossibleCellsList(&PCList);
	createPossibleCellsList(&PCList);
	PossibleCellsListNode *kCell;

	int i;
	for (i = 0; i < N; i++)
	{
		K = getRandomNumber(PCList.size);
		kCell = getPossibleCellsListNode(&PCList, K - 1);

		randomPossibleDigit = getRandomNumber(possibilities[kCell->place.R][kCell->place.C]->size) - 1;
		board[kCell->place.R][kCell->place.C] = possibilities[kCell->place.R][kCell->place.C]->arr[randomPossibleDigit];

		upatePossibleDigits(board, possibilities, kCell->place.R, kCell->place.C);

		deletePossibleCellsNodeFromList(&PCList, kCell);
	}
	freePossibleCellsList(&PCList);
	return possibilities;
}

//This function creates a possible digits array.
Array ***createEmptyPossibleDigitsArr(short board[][COLSIZE])
{
	Array ***possibilities = (Array***)malloc(COLSIZE * sizeof(Array**));
	checkAllocation(possibilities, "Failed to allocate possible digits array to memory");

	int row, col; 
	for (row = 0; row < ROWSIZE; row++)
	{
		possibilities[row] = (Array**)malloc(ROWSIZE * sizeof(Array*));
		checkAllocation(possibilities[row], "Failed to allocate possible digits array to memory");

		for (col = 0; col < COLSIZE; col++)
		{
			if (board[row][col] == -1)
			{
				possibilities[row][col] = (Array*)malloc(sizeof(Array));
				checkAllocation(possibilities[row][col], "Failed to allocate possible digits array to memory");
			}
			else 
			{
				possibilities[row][col] = NULL;
			}
		}
	}
	return possibilities;
}

//This funcion creats an array of all the possible digits of evry cell
Array ***PossibleDigits(short board[][COLSIZE])
{
	Array ***possibilities = createEmptyPossibleDigitsArr(board);

	int row, col;
	for (row = 0; row < COLSIZE; row++)
	{
		for (col = 0; col < ROWSIZE; col++)
		{
			if (board[row][col] == -1)
			{
				updatePossibleDigitsCell(board, possibilities[row][col], row, col);
			}
		}
	}
	return possibilities;
}



//This function marks and inserts into the array whether the digit exists in the row 
void isDigitExsistInRow(short board[][COLSIZE], int *existingDigits, int row)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (board[row][i] != -1) {
			if (existingDigits[board[row][i] - 1] == 0) {
				existingDigits[board[row][i] - 1]++;
			}
		}
	}
}

//This function marks and inserts into the array whether the digit exists in the col 
void isDigitExsistInCol(short board[][COLSIZE], int *existingDigits, int col)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (board[i][col] != -1) {
			if (existingDigits[board[i][col] - 1] == 0) {
				existingDigits[board[i][col] - 1]++;
			}
		}
	}
}

//This function marks and inserts into the array whether the digit exists in the square 
void isDigitExsistInSquare(short board[][COLSIZE], int *existingDigits, int row, int col)
{
	int i, j;
	for (i = row - (row % 3); i < row - (row % 3) + 3; i++)
	{
		for (j = col - (col % 3); j < col - (col % 3) + 3; j++)
		{
			if ((board[i][j] - 1) != -1) {
				if (existingDigits[board[i][j] - 1] == 0) {
					existingDigits[board[i][j] - 1]++;
				}
			}
		}
	}
}

//This function updates in the possible digits array and size of the cell
void updatePossibleDigitsCell(short board[][COLSIZE], Array *cell, int row, int col)
{
	int i, existingDigits[COLSIZE];
	for (i = 0; i < COLSIZE; i++) {
		existingDigits[i] = 0;
	}

	isDigitExsistInSquare(board, existingDigits, row, col);
	isDigitExsistInRow(board, existingDigits, row);
	isDigitExsistInCol(board, existingDigits, col);

	cell->size = 0;
	for (i = 0; i < 9; i++)
	{
		if (existingDigits[i] != 1) {
			cell->size++;
		}
	}
	cell->arr = (short*)malloc(cell->size * sizeof(short));
	checkAllocation(cell->arr, "Failed to allocate cell to memory");

	int cellArrInd = 0;
	for (i = 0; i < ROWSIZE; i++)
	{
		if (existingDigits[i] != 1)
		{
			cell->arr[cellArrInd] = i + 1;
			cellArrInd++;
		}
	}
}

//This function updates the possible digits array of the row of the cell
void upatePossibleDigitsRow(short board[][COLSIZE], Array ***possibilities, int row, int col)
{
	int i;
	for (i = 0; i < ROWSIZE; i++)
	{
		if (board[row][i] == -1)
		{
			if (isDigitExsistInPossibleDigitsArr(possibilities[row][i], board[row][col]))
			{
				deleteDigitFromPossibleDigitsArr(possibilities[row][i], board[row][col]);
			}
		}
	}
}

//This function updates the possible digits array of the col of the cell
void upatePossibleDigitsCol(short board[][COLSIZE], Array ***possibilities, int row, int col)
{
	int i;
	for (i = 0; i < COLSIZE; i++)
	{
		if (board[i][col] == -1)
		{
			if (isDigitExsistInPossibleDigitsArr(possibilities[i][col], board[row][col]))
			{
				deleteDigitFromPossibleDigitsArr(possibilities[i][col], board[row][col]);
			}
		}
	}
}

//This function updates the possible digits array of the square of the cell
void updatePossibleDigitsSquare(short board[][COLSIZE], Array ***possibilities, int row, int col)
{
	int i, j;
	for (i = row - (row % 3); i < row - (row % 3) + 3; i++)
	{
		for (j = col - (col % 3); j < col - (col % 3) + 3; j++)
		{
			if (board[i][j] == -1)
			{
				if (isDigitExsistInPossibleDigitsArr(possibilities[i][j], board[row][col]))
				{
					deleteDigitFromPossibleDigitsArr(possibilities[i][j], board[row][col]);
				}
			}
		}
	}
}

//This function updates the possible digits array of the cell
void upatePossibleDigits(short board[][COLSIZE], Array ***possibilities, int row, int col)
{
	upatePossibleDigitsRow(board, possibilities, row, col);
	upatePossibleDigitsCol(board, possibilities, row, col);
	updatePossibleDigitsSquare(board, possibilities, row, col);
}

//This function checks whether the board is correct by col
bool checkBoardByCol(short board[][COLSIZE], int input, int col)
{
	int i;
	int count = 0;
	for (i = 0; i < ROWSIZE; i++) {
		if (board[i][col] != -1) {
			if (board[i][col] == input) {
				count++;
			}
		}
	}
	if (count > 1) {
		return false;
	}
	return true;
}

//This function checks whether the board is correct by row
bool checkBoardByRow(short board[][COLSIZE], int input, int row)
{
	int i;
	int count = 0;
	for (i = 0; i < ROWSIZE; i++) {
		if (board[row][i] != -1) {
			if (board[row][i] == input) {
				count++;
			}
		}
	}
	if (count > 1) {
		return false;
	}
	return true;
}

//This function checks whether the board is correct by square
bool checkBoardBySquare(short board[][COLSIZE], int input, int row, int col) {
	int i, j;
	int count = 0;
	for (i = row - (row % 3); i < row - (row % 3) + 3; i++)
	{
		for (j = col - (col % 3); j < col - (col % 3) + 3; j++)
		{
			if (board[i][j] != -1) {
				if (board[i][j] == input) {
					count++;
				}
			}
		}
	}
	if (count > 1) {
		return false;
	}
	return true;
}

//This function prints the suduko board
void printSudokoBoard(short sudokuBoard[][COLSIZE])
{
	int i, j; 
	printf("%s", DIVIDER); 
	printf("\n%3c", '|');
	for (i = 0; i < ROWSIZE; i++) 
	{
		printf("%2d", i); 
		if ((i % 3 == 2) && (i != COLSIZE - 1)) {
			printf("%c", '|');
		}
	}
	printf("\n");
	printf("%s\n", DIVIDER);
	for (i = 0; i < ROWSIZE; i++)
	{
		printf("%2d%c", i, '|');
		for (j = 0; j < COLSIZE; j++)
		{
			if (sudokuBoard[i][j] != -1) {
				printf("%2d", sudokuBoard[i][j]);
			}
			else {
				printf("%s", "  ");
			}
			if ((j % 3 == 2) && (j != COLSIZE - 1)) {
				printf("%c", '|');
			}
		}
		printf("\n");
		if ((i % 3 == 2) && (i != COLSIZE - 1)) {
			printf("%s\n", DIVIDER);
		}
	}
	printf("%s\n", DIVIDER);
}
