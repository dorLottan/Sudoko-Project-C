#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FINISH 0
#define FINISH_FAILURE -1
#define FINISH_SUCCESS  1
#define DIVIDER "-----------------------"
#define MAX_NAME_LENGTH 100
#define ROWSIZE 9
#define COLSIZE 9


typedef struct _Array
{
	short *arr;
	unsigned short size;
} Array;

typedef struct player
{
	char *name;
	short board[COLSIZE][ROWSIZE];
	Array ***PossibleDigits;
} Player;

typedef struct playerListNode
{
	Player *player;
	struct playerListNode *next;
	struct playerListNode *prev;
} PlayerListNode;

typedef struct playersList
{
	PlayerListNode *head;
	PlayerListNode *tail;
} PlayersList;

typedef struct treeNode {
	PlayerListNode *data;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

typedef struct tree {
	TreeNode *root;
}Tree;

typedef struct cellPlace
{
	int R;
	int C;
} CellPlace;

typedef struct possibleCellsListNode
{
	CellPlace place;
	struct possibleCellsListNode *next;
	struct possibleCellsListNode *prev;
} PossibleCellsListNode;

typedef struct possibleCellsList
{
	PossibleCellsListNode *head;
	PossibleCellsListNode *tail;
	int size;
} PossibleCellsList;
