#include "auxiliary.h"
#include "playersFuncs.h"
#include "playersListsFuncs.h"
#include "sudokoBoardFuncs.h"
#include "helperFuncs.h"

//This function checks if the name that it gets doesn't already exist in the players list
bool checkPlayerName(PlayersList *lst, char *name) {
	PlayerListNode *curr = lst->head;
	while (curr)
	{
		if (strcmp(curr->player->name, name) == 0) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

//This function creates a new player
Player* createNewPlayer(PlayersList *activePlayersList, int num)
{
	Player* res = (Player*)malloc(sizeof(Player));
	checkAllocation(res, "Faild to allocated new player to memory");
	res->name = getPlayerName(num);
	while (checkPlayerName(activePlayersList, res->name)) {
		printf("The name of the player alrady exsist. \n");
		res->name = getPlayerName(num);
	}
	createEmptySudokoBoard(res->board);
	res->PossibleDigits = randomFillSudokoBoard(res->board);
	return res;
}

//This function scans from the user the name of the player
char* getPlayerName(int num)
{
	int nameLen = 0;
	char* name = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
	checkAllocation(name, "Faild to allocated name to memory");

	printf("Please enter the name of player number %d: \n", num);
	char ch;
	ch = getchar();
	while ((ch != '\n') && (nameLen < MAX_NAME_LENGTH))
	{
		name[nameLen] = ch;
		nameLen++;
		ch = getchar();
	}
	name[nameLen] = '\0';
	nameLen++;
	name = realloc(name, nameLen * sizeof(char));
	checkAllocation(name, "Faild to realloc name");
	return name;
}

//This function scans the number of players from the user, creates them and adds them to the end of players list 
int getPlayers(PlayersList *activePlayersList) {
	int i, numPlayers;
	printf("Please enter the number of the players: \n");
	char c = getchar();
	numPlayers = c - '0';
	char enter = getchar();
	for (i = 0; i < numPlayers; i++)
	{
		Player* newPlayer = createNewPlayer(activePlayersList, i + 1);
		insertPlayerDataToEndList(activePlayersList, newPlayer);
	}
	return numPlayers;
}
