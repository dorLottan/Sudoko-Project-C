#pragma once
#include "auxiliary.h"

bool isPossibleCellsListEmpty(PossibleCellsList *lst);
void makeEmptyPossibleCellsList(PossibleCellsList *lst);
PossibleCellsListNode *createNewPossibleCellsListNode(CellPlace cellPlace);
void insertPossibleCellsDataToEndList(PossibleCellsList *lst, CellPlace cellPlace);
void insertPossibleCellsNodeToEndList(PossibleCellsList *lst, PossibleCellsListNode *newTail);
PossibleCellsListNode *getPossibleCellsListNode(PossibleCellsList *lst, int cellNum);
void deletePossibleCellsNodeFromList(PossibleCellsList *lst, PossibleCellsListNode *node);
void freePossibleCellsList(PossibleCellsList *lst);
void createPossibleCellsList(PossibleCellsList *lst);
