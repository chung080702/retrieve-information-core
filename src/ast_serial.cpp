#include "ast_tree.h"
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dsChiMucNguoc;

int current(AstBaseNode *node)
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

int next(AstBaseNode *node)
{

	if (current(node) == -1)
		return -1;
	node->idx++;
	if (node->isLeaf)
	{
		auto *nd = (AstLeafNode *)node;
		return current(node);
	}
	else
	{
		auto *nd = (AstInnerNode *)node;
		auto left = nd->left;
		auto right = nd->right;

		if (nd->operatorr == AND)
		{
			int nextLeft = next(left);
			int nextRight = next(right);
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
					nextRight = next(right);
				else
					nextLeft = next(left);
			}
		}

		if (nd->operatorr == OR)
		{

			int curLeft = current(left);
			int curRight = current(right);

			if (curLeft == curRight)
			{
				curLeft = next(left);
				curRight = next(right);
			}
			else if (curLeft < curRight || curRight == -1)
				curLeft = next(left);
			else if (curRight < curLeft || curLeft == -1)
				curRight = next(right);

			if (curLeft == -1 && curRight == -1)
			{
				nd->val = -1;
				return -1;
			}

			if (curRight == -1 || curLeft < curRight)
			{
				nd->val = curLeft;
				return curLeft;
			}

			if (curLeft == -1 || curRight < curLeft)
			{
				nd->val = curRight;
				return curRight;
			}
		}
	}
	return -1;
}

AstBaseNode *node[20];

int main()
{
	freopen("test.inp", "r", stdin);
	int n, m;
	// danh sach chi muc nguoc
	cin >> n; // so luong word
	for (int i = 1; i <= n; i++)
	{
		int k;
		cin >> k; // so luong chi muc nguoc tuong ung wordid=i
		vector<int> v;
		// danh sach chi muc nguoc
		for (int j = 1; j <= k; j++)
		{
			int c;
			cin >> c;
			v.push_back(c);
		}

		dsChiMucNguoc.push_back(v);
	}

	// danh sach node
	// node1: left -> node2, right -> node3
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		bool isLeaf;
		cin >> isLeaf;
		if (isLeaf)
		{
			int wordId;

			cin >> wordId;
			node[i] = (AstBaseNode *)new AstLeafNode(wordId);
		}
		else
		{
			int op;
			cin >> op;
			if (op == 0)
				node[i] = (AstBaseNode *)new AstInnerNode(AND);
			else if (op == 1)
				node[i] = (AstBaseNode *)new AstInnerNode(OR);
		}
	}
	for (int i = 1; i <= m; i++)
		if (node[i]->isLeaf == false)
		{
			auto curNode = (AstInnerNode *)node[i];
			curNode->left = node[i * 2];
			curNode->right = node[i * 2 + 1];
		}
	cout << next(node[1]) << "\n";
	cout << next(node[1]) << "\n";
}
