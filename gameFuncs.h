#pragma once
#include "auxiliary.h"

int OneStage(short board[][COLSIZE], Array ***possibilities, int *x, int *y);
void playersTurn(Tree *tr, PlayersList *activePlayersList, PlayersList *winnersList);
void playersTurnRecInOrder(TreeNode *root, PlayersList *activePlayersList, PlayersList *winnersList);
void playerSelection(PlayerListNode *player, int row, int col);
void printPossibleDigitsArr(Array ***possibilities, int row, int col);
void PrintWinners(PlayersList *lst);
