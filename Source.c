#include "auxiliary.h"
#include "playersListsFuncs.h"
#include "gameFuncs.h"
#include "treeFuncs.h"
#include "playersFuncs.h"
#include "helperFuncs.h"


void main()
{
	srand(12345);

	PlayersList *activePlayersList = (PlayersList*)malloc(sizeof(PlayersList));
	checkAllocation(activePlayersList, "Failed to allocate active list to memory");
	makeEmptyPlayersList(activePlayersList);

	PlayersList *winnersList = (PlayersList*)malloc(sizeof(PlayersList));
	checkAllocation(winnersList, "Failed to allocate winners list to memory");
	makeEmptyPlayersList(winnersList);

	int numPlayers = getPlayers(activePlayersList);
	
	PlayerListNode **activePlayersArr = (PlayerListNode**)malloc(numPlayers * sizeof(PlayerListNode*)); 
	checkAllocation(activePlayersArr, "Failed to allocate active arr to memory");

	createActivePlayersPointersArr(activePlayersList, activePlayersArr, numPlayers);

	//printPlayersList(activePlayersArr, numPlayers);
	mergeSort(activePlayersArr, numPlayers);
	//printPlayersList(activePlayersArr, numPlayers);

	activePlayersArr = expandActivePlayersArr(activePlayersArr, &numPlayers);

	Tree activePlayersTree = BuildTreeFromArray(activePlayersArr, numPlayers);

	while (!isPlayersListEmpty(activePlayersList))
	{
		playersTurn(&activePlayersTree, activePlayersList, winnersList);
	}

	if (winnersList->head) {
		PrintWinners(winnersList);
	}
	else {
		printf("No player won \n");
	}

	freePlayersList(activePlayersList);
	freePlayersList(winnersList);
	freeTree(activePlayersTree);
}
