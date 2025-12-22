#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 1; i <= n; i++) a.push_back(i);
    reverse(a.begin(), a.end());
    do {
        for (int i = 0; i < (int)a.size(); i++) {
            cout << a[i];
            if (i != (int)a.size() - 1) cout << " ";
        }
        cout << endl;
    } while (prev_permutation(a.begin(), a.end()));
    return 0;
}