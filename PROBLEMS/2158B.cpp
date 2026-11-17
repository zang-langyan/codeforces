#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << " ";
    }
    os << '\n';
    return os;
}

template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    if (a.size() != b.size()) return {};
    vector<T> res(a.size());
    for (int i = 0; i < a.size(); ++i) {
        res[i] = a[i] + b[i];
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    unordered_map<int, int> mp;
    for (int i = 0; i < 2 * n; ++i) {
        int x;
        cin >> x;
        ++mp[x];
    }
    int o = 0, mod2 = 0, mod0 = 0;
    for (auto& [_, c]: mp) {
        if (c & 1) {
            ++o;
        } else if (c % 4 == 0) {
            ++mod0;
        } else if (c % 4 == 2) {
            ++mod2;
        }
    }
    if (o == 0 && mod0 & 1) {
        cout << o + 2 * mod2 + 2 * mod0 - 2 << endl;
    } else {
        cout << o + 2 * mod2 + 2 * mod0 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

