#include "vector"
#include "ast_tree.h"

using namespace std;

struct Array
{
	int *begin;
	int length;
};

int current(AstBaseNode *node, vector<Array> dsChiMucNguoc)
{
	if (node->isLeaf)
	{
		auto *nd = (AstLeafNode *)node;
		auto &chiMucNguoc = dsChiMucNguoc[nd->wordId];

		if (nd->idx == -1)
			return -2;
		if (chiMucNguoc.length <= nd->idx)
			return -1;
		return chiMucNguoc.begin[nd->idx];
	}
	else
	{
		auto *nd = (AstInnerNode *)node;
		return nd->val;
	}
}

int next(AstBaseNode *node, vector<Array> dsChiMucNguoc)
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

vector<int> getListIndex(AstBaseNode *root, int begin, int length, vector<Array> dsChiMucNguoc)
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

// [12][32]&[5][4][123]|[89]&|
AstBaseNode *postfixQueryToTree(string str)
{
	stack<AstBaseNode *> st;
	int wordId = 0;
	for (auto c : str)
	{
		if ('0' <= c && c <= '9')
			wordId = wordId * 10 + c - '0';
		else if (c == '[')
			wordId = 0;
		else if (c == ']')
		{
			auto node = (AstBaseNode *)new AstLeafNode(wordId);
			st.push(node);
		}
		else
		{
			auto right = st.top();
			st.pop();
			auto left = st.top();
			st.pop();
			auto node = new AstInnerNode((OP)c);
			node->left = left;
			node->right = right;

			st.push((AstBaseNode *)node);
		}
	}
	return st.top();
}