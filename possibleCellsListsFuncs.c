#include "possibleCellsListsFuncs.h"
#include "helperFuncs.h"

//This function deletes the possible cells node from the list
void deletePossibleCellsNodeFromList(PossibleCellsList *lst, PossibleCellsListNode *node)
{
	if (lst->head == node && lst->tail == node) //only
	{
		lst->head = lst->tail = NULL;
	}
	else if (lst->head == node) //head
	{
		lst->head = node->next;
		lst->head->prev = NULL;
	}
	else if (lst->tail == node) //tail
	{
		lst->tail = node->prev;
		lst->tail->next = NULL;
	}
	else //mid
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	lst->size--;
}

//This function creats an empty possible cells list
void makeEmptyPossibleCellsList(PossibleCellsList *lst)
{
	lst->size = 0;
	lst->head = lst->tail = NULL;
}

//This function creates a new possible cells list node.
PossibleCellsListNode *createNewPossibleCellsListNode(CellPlace cellPlace)
{
	PossibleCellsListNode *res = (PossibleCellsListNode*)malloc(sizeof(PossibleCellsListNode));
	checkAllocation(res, "Failed to allocate list node to memory");
	res->place = cellPlace;
	res->next = res->prev = NULL; 
	return res; 
}

//This function checks if the list is empty
bool isPossibleCellsListEmpty(PossibleCellsList *lst)
{
	return (!lst->head);
}


//This function inserts the possible cells node to the end of list.
void insertPossibleCellsDataToEndList(PossibleCellsList *lst, CellPlace cellPlace)
{
	PossibleCellsListNode *newTail; 
	newTail = createNewPossibleCellsListNode(cellPlace);
	insertPossibleCellsNodeToEndList(lst, newTail); 
}

//This function inserts the possible cells node to the end of list.
void insertPossibleCellsNodeToEndList(PossibleCellsList *lst, PossibleCellsListNode *newTail)
{
	if (isPossibleCellsListEmpty(lst))
	{
		lst->head = lst->tail = newTail;
	}
	else 
	{
		lst->tail->next = newTail;
		newTail->prev = lst->tail;
		lst->tail = newTail;
	}
	lst->size++;
}

//This function returns the the possible cells node of the cell it gets
PossibleCellsListNode *getPossibleCellsListNode(PossibleCellsList *lst, int cellNum)
{
	PossibleCellsListNode *curr = lst->head;
	if ((isPossibleCellsListEmpty(lst)) || (cellNum > lst->size)) {
		return NULL;
	}
	else
	{
		while (cellNum > 0)
		{
			cellNum--;
			curr = curr->next;
		}
	}
	return curr;
}

//This function frees the list
void freePossibleCellsList(PossibleCellsList *lst)
{ 
	PossibleCellsListNode *curr = lst->head, *temp;
	while (curr)
	{
		temp = curr->next;
		free(curr);
		curr = temp;
		lst->size--;
	}
}

//This function creats a new possible cells list of all the board
void createPossibleCellsList(PossibleCellsList *lst)
{
	int i, j; 
	CellPlace cellPlace; 
	for (i = 0; i < COLSIZE; i++) 
	{
		for (j = 0; j < ROWSIZE; j++) 
		{
			cellPlace.R = i; 
			cellPlace.C = j;
			insertPossibleCellsDataToEndList(lst, cellPlace);
		}
	}
}
