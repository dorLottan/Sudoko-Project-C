#include "gameFuncs.h"
#include "sudokoBoardFuncs.h"
#include "playersListsFuncs.h"

//This function fills all the cells which can be filled by a single digit and updates the board
//and updates x, y to be the cell with minimum posiible digits
int OneStage(short board[][COLSIZE], Array ***possibilities, int *x, int *y)
{
	int minimumPossibleDigits = 9, row, col;
	int res = FINISH_SUCCESS;
	bool isCellWithOneOp = true; 

	while ((res != FINISH_FAILURE) && (isCellWithOneOp))
	{
		isCellWithOneOp = false; 
		minimumPossibleDigits = 9; 
		res = FINISH_SUCCESS;

		for (row = 0; row < ROWSIZE; row++)
		{
			for (col = 0; col < COLSIZE; col++)
			{
				if (board[row][col] == -1)
				{
					if ((possibilities[row][col]->size > 1) && (minimumPossibleDigits > possibilities[row][col]->size))
					{
						res = NOT_FINISH;
						minimumPossibleDigits = possibilities[row][col]->size;
						*x = row;
						*y = col;
					}
					else if (possibilities[row][col]->size == 1)
					{
						isCellWithOneOp = true;
						board[row][col] = possibilities[row][col]->arr[0];
						printf("Updating cell [%d,%d] with value %d\n\n", row, col, possibilities[row][col]->arr[0]);
						free(possibilities[row][col]->arr);
						free(possibilities[row][col]);
						possibilities[row][col] = NULL;
						upatePossibleDigits(board, possibilities, row, col);
					}
					else if (possibilities[row][col]->size == 0)
					{
						res = FINISH_FAILURE; 
						return res;
					}
				}
			}
		}
	}
	return res;
}

//This function runs OneStage for each player in the tree InOrder
void playersTurn(Tree *tr, PlayersList *activePlayersList, PlayersList *winnersList)
{
	playersTurnRecInOrder(tr->root, activePlayersList, winnersList);
}

//This function runs OneStage for each player in the tree InOrder
void playersTurnRecInOrder(TreeNode *root, PlayersList *activePlayersList, PlayersList *winnersList)
{
	int row, col; 
	int res; 
	if (!root) {
		return;
	}
	else
	{
		playersTurnRecInOrder(root->left, activePlayersList, winnersList);
		if (root->data)
		{
			res = OneStage(root->data->player->board, root->data->player->PossibleDigits, &row, &col); 
		    if (res == NOT_FINISH)
			{
				printf("%9s's Board: \n", root->data->player->name);
				printSudokoBoard(root->data->player->board);
				playerSelection(root->data, row, col);
				if ((!checkBoardByRow(root->data->player->board, root->data->player->board[row][col], row)) ||
					(!checkBoardByCol(root->data->player->board, root->data->player->board[row][col], col)) || 
					(!checkBoardBySquare(root->data->player->board, root->data->player->board[row][col], row, col))) {
					res = FINISH_FAILURE;
				}
			}
			else if (res == FINISH_SUCCESS) 
			{
				printf("%s's board filled successfully\n", root->data->player->name);
				insertPlayerDataToEndList(winnersList, root->data->player);
				deletePlayeNodeFromList(activePlayersList, root->data, false); //delete no free
				root->data = NULL;
			}
			
			if (res == FINISH_FAILURE)
			{
				printf("%s's selections led to duplications \n \n", root->data->player->name);
				printSudokoBoard(root->data->player->board);
				deletePlayeNodeFromList(activePlayersList, root->data, true); //delete & free
				root->data = NULL;
			}
		}
		playersTurnRecInOrder(root->right, activePlayersList, winnersList);
	}
}

//This function prints to the user all the possible digits for the cell, scans for his input and updates the board according to it 
void playerSelection(PlayerListNode *player, int row, int col)
{
	int input;
	printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", row, col);
	printPossibleDigitsArr(player->player->PossibleDigits, row, col);
	scanf("%d", &input);
	while ((input < 0) || (input > 9)) {
		printf("Invalid input. Type again: \n");
		scanf("%d", &input);
	}
	player->player->board[row][col] = input;
	printf("Updating cell [%d,%d] with value %d\n\n", row, col, input);
	upatePossibleDigits(player->player->board, player->player->PossibleDigits, row, col);
}

//This function prints the possible digits array of the cell [row,col] that it gets
void printPossibleDigitsArr(Array ***possibilities, int row, int col)
{
	int i, size;
	if (possibilities[row][col])
	{
		size = possibilities[row][col]->size;
		for (i = 0; i < size; i++)
		{
			printf("%d| %d \n", i + 1, possibilities[row][col]->arr[i]);
		}
	}
}

//This function prints winners list to screen
void PrintWinners(PlayersList *lst)
{
	printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	PlayerListNode *curr = lst->head;
	printf("Winners List:\n \n");
	while (curr)
	{
		printf("Player Name: %s \n", curr->player->name);
		printf("Player Board:\n");
		printSudokoBoard(curr->player->board);
		curr = curr->next;
	}
	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
}
