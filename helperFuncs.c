#include "helperFuncs.h"

//This function swaps between the 2 args that it gets 
void swap(short *a, short *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//This function return a random number between 1 to x
unsigned int getRandomNumber(int x)
{
	srand(time(NULL));
	int res = 1 + rand() % x;
	return res;
}

//This function expands the active players array size according to the instructions in question
PlayerListNode** expandActivePlayersArr(PlayerListNode **activePlayersArr, int *numPlayers)
{
	int power = ceil(log(*(numPlayers)+1) / log(2));
	int newSize = pow(2, power) - 1;

	activePlayersArr = (PlayerListNode**)realloc(activePlayersArr, newSize * sizeof(PlayerListNode*));
	checkAllocation(activePlayersArr, "Faild to realloc active players arr to memory");

	int i;
	for (i = *numPlayers; i < newSize; i++)
	{
		activePlayersArr[i] = NULL;
	}

	*numPlayers = newSize;
	return activePlayersArr;
}

//This function sorts the players by the number of their filled cells in the board and if they have the same number it sorts them by their names
//via mergsort algorithm
void mergeSort(PlayerListNode **pointers, int size)
{
	PlayerListNode **tempArr;
	if (size <= 1) {
		return;
	}
	mergeSort(pointers, size / 2);
	mergeSort(pointers + size / 2, size - size / 2);
	tempArr = (PlayerListNode**)malloc(size * sizeof(PlayerListNode*));
	checkAllocation(tempArr, "Faild to allocated temp arr to memory");

	merge(pointers, size / 2, pointers + (size / 2), size - (size / 2), tempArr);

	copyArr(pointers, tempArr, size);
	free(tempArr);

}

//This function sorts the players by the number of their filled cells in the board and if they have the same number it sorts them by their names
//via mergsort algorithm
void merge(PlayerListNode **a1, int size1, PlayerListNode **a2, int size2, PlayerListNode **res)
{
	int ind1 = 0, ind2 = 0, resInd = 0;
	int *a1FilledCells = createFilledCellsNumOfPlayerArray(a1, size1);
	int *a2FilledCells = createFilledCellsNumOfPlayerArray(a2, size2);

	while ((ind1 < size1) && (ind2 < size2)) {
		if (a1FilledCells[ind1] > a2FilledCells[ind2])
		{
			res[resInd] = a1[ind1];
			ind1++;
		}
		else if (a1FilledCells[ind1] < a2FilledCells[ind2])
		{
			res[resInd] = a2[ind2];
			ind2++;
		}
		else if (strcmp(a1[ind1]->player->name, a2[ind2]->player->name) < 0)
		{
			res[resInd] = a1[ind1];
			ind1++;
		}
		else
		{
			res[resInd] = a2[ind2];
			ind2++;
		}
		resInd++;
	}

	while (ind1 < size1)
	{
		res[resInd] = a1[ind1];
		ind1++;
		resInd++;
	}
	while (ind2 < size2)
	{
		res[resInd] = a2[ind2];
		ind2++;
		resInd++;
	}

	free(a1FilledCells);
	free(a2FilledCells);
}

//This function copies the first array that it gets to the second
void copyArr(PlayerListNode **pointers, PlayerListNode **temp, int size) {
	int i;
	for (i = 0; i < size; i++) {
		pointers[i] = temp[i];
	}
}

//This function creates and returns an array of all the filled cells
int* createFilledCellsNumOfPlayerArray(PlayerListNode **arr, int size)
{
	int i;
	int *res;
	if (size == 0) {
		return NULL;
	}
	else
	{
		res = (int*)malloc(size * sizeof(int));
		checkAllocation(res, "Faild to allocated res to memory");
		for (i = 0; i < size; i++)
		{
			res[i] = getFilledCellsNumOfPlayer(arr[i]);
		}
	}
	return res;
}

//This function returns the number of the filled cells on the board
int getFilledCellsNumOfPlayer(PlayerListNode *player)
{
	int res = 0, row, col;
	for (row = 0; row < ROWSIZE; row++)
	{
		for (col = 0; col < COLSIZE; col++)
		{
			if (player->player->board[row][col] != -1) {
				res++;
			}
		}
	}
	return res;
}

//This function frees possible digits arr
void FreePD(Array ***possibilities)
{
	int row, col;
	for (row = 0; row < ROWSIZE; row++)
	{
		for (col = 0; col < COLSIZE; col++)
		{
			free(possibilities[row][col]);
		}
		free(possibilities[row]);
	}
	free(possibilities);
}

//This function deletes the value num from possible digits arr that it receives
void deleteDigitFromPossibleDigitsArr(Array *cell, int num) {

	int possibilitiesArrInd;
	cell->size--;
	for (possibilitiesArrInd = 0; possibilitiesArrInd < cell->size; possibilitiesArrInd++)
	{
		if (cell->arr[possibilitiesArrInd] == num) {
			swap(&cell->arr[possibilitiesArrInd], &cell->arr[possibilitiesArrInd + 1]);
		}
	}

	cell->arr = realloc((short*)cell->arr, cell->size * sizeof(short));
	if (cell->size > 0)
	{
		checkAllocation(cell->arr, "Faild to realloc possibilities arr");
	}
}

//This function checks if the number that is gets exist in the possible digits array  
bool isDigitExsistInPossibleDigitsArr(Array *cell, int num)
{
	int i;
	for (i = 0; i < cell->size; i++)
	{
		if (cell->arr[i] == num) {
			return true;
		}
	}
	return false;
}

//This function checks if the memory has been allocated successfully
void checkAllocation(void* item, char* str)
{
	if (item == NULL) {
		printf("%s", str);
		exit(1);
	}
}
