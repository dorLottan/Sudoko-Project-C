#include "playersListsFuncs.h"
#include "helperFuncs.h"

//This function creats an empty players list
void makeEmptyPlayersList(PlayersList *lst)
{
	lst->head = lst->tail = NULL;
}

//This function checks if the list is empty
bool isPlayersListEmpty(PlayersList *lst)
{
	return (!lst->head);
}


//This function copies the pointers of the list nodes into an array
void createActivePlayersPointersArr(PlayersList *lst, PlayerListNode **arr, int size)
{
	PlayerListNode *curr = lst->head;
	int i = 0;
	while((i < size) && (curr))
	{
		arr[i] = curr;
		i++;
		curr = curr->next;
	}
}

//This function deletes the player node from the list
void deletePlayeNodeFromList(PlayersList *lst, PlayerListNode *node, bool toFree) {

	if (lst->head == node && lst->tail == node) //only
	{
		lst->head = lst->tail = NULL;
	}
	else if (lst->head == node) //head
	{
		lst->head = node->next;
		lst->head->prev = NULL;
	}
	else if (lst->tail == node) //last
	{
		lst->tail = node->prev;
		lst->tail->next = NULL;
	}
	else //mid
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	if (toFree) {
		freePlayersListNode(node);
	}
}



//This function inserts the player node to the end of list.
void insertPlayerDataToEndList(PlayersList *lst, Player *player)
{
	PlayerListNode *newTail;
	newTail = createNewPlayersListNode(player);
	insertPlayerNodeToEndList(lst, newTail);
}

//This function inserts the player node to the end of list.
void insertPlayerNodeToEndList(PlayersList *lst, PlayerListNode *newTail)
{
	if (isPlayersListEmpty(lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		newTail->prev = lst->tail;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

//This function creates a new player list node.
PlayerListNode* createNewPlayersListNode(Player *player)
{
	PlayerListNode *res = (PlayerListNode*)malloc(sizeof(PlayerListNode));
	checkAllocation(res, "Failed to allocate new player node to memory");
	res->player = player;
	res->next = res->prev = NULL;
	return res;
}

//This function frees the players list
void freePlayersListNode(PlayerListNode *node)
{
	free(node->player->name);
	FreePD(node->player->PossibleDigits);
	free(node->player);
	free(node);
}

//this function free this PLAYERSList.
void freePlayersList(PlayersList *lst)
{
	PlayerListNode *curr = lst->head, *temp;
	while (curr)
	{
		temp = curr->next;
		freePlayersListNode(curr);
		curr = temp;
	}
	free(lst);
}

void printPlayersList(PlayerListNode **arr, int size) {
	int i;
	printf("\n");
	for (i = 0; i < size; i++) {
		printf("\n %d| name: %s", i, arr[i]->player->name);
	}
	printf("\n");
}
