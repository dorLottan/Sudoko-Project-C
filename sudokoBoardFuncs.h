#pragma once
#include "auxiliary.h"

void createEmptySudokoBoard(short board[][COLSIZE]);
Array ***randomFillSudokoBoard(short board[][COLSIZE]);
Array ***createEmptyPossibleDigitsArr(short board[][COLSIZE]);
Array ***PossibleDigits(short board[][COLSIZE]);
void isDigitExsistInRow(short board[][COLSIZE], int *existingDigits, int row);
void isDigitExsistInCol(short board[][COLSIZE], int *existingDigits, int col);
void isDigitExsistInSquare(short board[][COLSIZE], int *existingDigits, int row, int col);
void updatePossibleDigitsCell(short board[][COLSIZE], Array *cell, int row, int col);
void upatePossibleDigitsRow(short board[][COLSIZE], Array ***possibilities, int row, int col);
void upatePossibleDigitsCol(short board[][COLSIZE], Array ***possibilities, int row, int col);
void updatePossibleDigitsSquare(short board[][COLSIZE], Array ***possibilities, int row, int col);
void upatePossibleDigits(short board[][COLSIZE], Array ***possibilities, int row, int col);
bool checkBoardByCol(short board[][COLSIZE], int input, int col);
bool checkBoardByRow(short board[][COLSIZE], int input, int row);
bool checkBoardBySquare(short board[][COLSIZE], int input, int row, int col);
void printSudokoBoard(short sudokuBoard[][COLSIZE]);
