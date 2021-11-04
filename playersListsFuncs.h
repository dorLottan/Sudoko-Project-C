#pragma once
#include "auxiliary.h"

void makeEmptyPlayersList(PlayersList *lst);
bool isPlayersListEmpty(PlayersList *lst);
void createActivePlayersPointersArr(PlayersList *lst, PlayerListNode **arr, int size);
void deletePlayeNodeFromList(PlayersList *lst, PlayerListNode *node, bool toFree);
void insertPlayerDataToEndList(PlayersList *lst, Player *player);
void insertPlayerNodeToEndList(PlayersList *lst, PlayerListNode *newTail);
PlayerListNode* createNewPlayersListNode(Player *player);
void freePlayersListNode(PlayerListNode *node);
void freePlayersList(PlayersList *lst);
void printPlayersList(PlayerListNode **arr, int size);
