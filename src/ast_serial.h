#include "vector"
#include "ast_tree.h"

using namespace std;

vector<vector<int>> dsChiMucNguoc;

int current(AstBaseNode *node, vector<vector<int>> dsChiMucNguoc)
{
	if (node->isLeaf)
	{
		auto *nd = (AstLeafNode *)node;
		vector<int> &chiMucNguoc = dsChiMucNguoc[nd->wordId];

		if (nd->idx == -1)
			return -2;
		if (chiMucNguoc.size() <= nd->idx)
			return -1;
		return chiMucNguoc[nd->idx];
	}
	else
	{
		auto *nd = (AstInnerNode *)node;
		return nd->val;
	}
}

int next(AstBaseNode *node, vector<vector<int>> dsChiMucNguoc)
{

	if (current(node, dsChiMucNguoc) == -1)
		return -1;
	node->idx++;
	if (node->isLeaf)
	{
		auto *nd = (AstLeafNode *)node;
		return current(node, dsChiMucNguoc);
	}
	else
	{
		auto *nd = (AstInnerNode *)node;
		auto left = nd->left;
		auto right = nd->right;

		if (nd->operatorr == AND)
		{
			int nextLeft = next(left, dsChiMucNguoc);
			int nextRight = next(right, dsChiMucNguoc);
			while (true)
			{
				if (nextLeft == -1 || nextRight == -1)
				{
					nd->val = -1;
					return -1;
				}
				if (nextLeft == nextRight)
				{
					nd->val = nextLeft;
					return nd->val;
				}
				if (nextLeft > nextRight)
					nextRight = next(right, dsChiMucNguoc);
				else
					nextLeft = next(left, dsChiMucNguoc);
			}
		}

		if (nd->operatorr == OR)
		{

			int curLeft = current(left, dsChiMucNguoc);
			int curRight = current(right, dsChiMucNguoc);

			if (curLeft == curRight)
			{
				curLeft = next(left, dsChiMucNguoc);
				curRight = next(right, dsChiMucNguoc);
			}
			else if (curLeft < curRight || curRight == -1)
				curLeft = next(left, dsChiMucNguoc);
			else if (curRight < curLeft || curLeft == -1)
				curRight = next(right, dsChiMucNguoc);

			if (curLeft == -1)
			{
				nd->val = curRight;
				return curRight;
			}

			if (curRight == -1)
			{
				nd->val = curLeft;
				return curLeft;
			}

			if (curRight <= curLeft)
			{
				nd->val = curRight;
				return curRight;
			}

			if (curLeft < curRight)
			{
				nd->val = curLeft;
				return curLeft;
			}
		}
	}
	return -1;
}

void clearTree(AstBaseNode *node)
{
	node->idx = -1;
	if (!node->isLeaf)
	{
		auto *nd = (AstInnerNode *)node;
		nd->val = -2;
		if (nd->left != nullptr)
			clearTree(nd->left);
		if (nd->right != nullptr)
			clearTree(nd->right);
	}
}

vector<int> getListIndex(AstBaseNode *root, int begin, int length, vector<vector<int>> dsChiMucNguoc)
{
	clearTree(root);
	vector<int> res;
	for (int i = 0; i < begin + length; i++)
	{
		int idx = next(root, dsChiMucNguoc);
		if (idx == -1)
			break;
		if (i >= begin)
			res.push_back(idx);
	}
	return res;
}
