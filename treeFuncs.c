#include "treeFuncs.h"
#include "helperFuncs.h"

//This function frees tree
void freeTree(Tree tr)
{
	freeTreeRec(tr.root);
}

//This function frees tree
void freeTreeRec(TreeNode *root)
{
	if (!root) {
		return;
	}
	else
	{
		freeTreeRec(root->left);
		freeTreeRec(root->right);
		free(root);
	}
}
//This function creats a new tree from the array it gets
Tree BuildTreeFromArray(PlayerListNode **arr, int size)
{
	Tree res;
	Tree left;
	Tree right;
	res.root = (TreeNode *)malloc(sizeof(TreeNode));
	checkAllocation(res.root, "Failed to allocate tree node to memory");
	if (size == 1)
	{
		res.root->data = arr[0];
		res.root->left = res.root->right = NULL;
	}
	else
	{
		res.root->data = arr[size / 2];
		if (arr[size / 4] != -1)
		{
			left = BuildTreeFromArray(arr, size / 2);
			res.root->left = left.root;
		}
		else
		{
			res.root->left = NULL;
		}

		if (arr[((size / 2) + (size / 4)) + 1] != -1)
		{
			right = BuildTreeFromArray((arr + size / 2) + 1, size / 2);
			res.root->right = right.root;
		}
		else
		{
			res.root->right = NULL;
		}
	};
	return res;
}

