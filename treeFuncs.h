#pragma once
#include "auxiliary.h"

void freeTree(Tree tr);
void freeTreeRec(TreeNode *root);
Tree BuildTreeFromArray(PlayerListNode **arr, int size);
