#pragma once
#include "auxiliary.h"

void swap(short *a, short *b);
unsigned int getRandomNumber(int x);
PlayerListNode** expandActivePlayersArr(PlayerListNode **activePlayersArr, int *numPlayers);
void mergeSort(PlayerListNode **pointers, int size);
void merge(PlayerListNode **a1, int size1, PlayerListNode **a2, int size2, PlayerListNode **res);
void copyArr(PlayerListNode **pointers, PlayerListNode **temp, int size) ;
int* createFilledCellsNumOfPlayerArray(PlayerListNode **arr, int size);
int getFilledCellsNumOfPlayer(PlayerListNode *player);
void FreePD(Array ***possibilities);
void deleteDigitFromPossibleDigitsArr(Array *cell, int num) ;
bool isDigitExsistInPossibleDigitsArr(Array *cell, int num);
void checkAllocation(void* item, char* str);
