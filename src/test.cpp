#include <bits/stdc++.h>
#include "ast_serial.h"

using namespace std;

vector<Array> dsChiMucNguoc;

int main()
{
    freopen("test.inp", "r", stdin);
    int n, m;
    dsChiMucNguoc.begin = new int[4];
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

    // postfix query
    string s;
    cin >> s;
    auto root = postfixQueryToTree(s);

    vector<int> res = getListIndex(root, 0, 2, dsChiMucNguoc);
    for (auto idx : res)
        cout << idx << " ";
}
