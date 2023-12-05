#include <bits/stdc++.h>
#include "ast_serial.h"

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
                node[i] = (AstBaseNode *)new AstInnerNode(OP::AND);
            else if (op == 1)
                node[i] = (AstBaseNode *)new AstInnerNode(OP::OR);
        }
    }
    for (int i = 1; i <= m; i++)
        if (node[i]->isLeaf == false)
        {
            auto curNode = (AstInnerNode *)node[i];
            curNode->left = node[i * 2];
            curNode->right = node[i * 2 + 1];
        }
    vector<int> res = getListIndex(node[1], 0, 2, dsChiMucNguoc);
    for (auto idx : res)
        cout << idx << " ";
}
