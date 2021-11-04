#pragma once
#include "auxiliary.h"

bool checkPlayerName(PlayersList *lst, char *name);
Player *createNewPlayer(PlayersList *activePlayersList, int num);
char* getPlayerName(int num);
int getPlayers(PlayersList *activePlayersList);
