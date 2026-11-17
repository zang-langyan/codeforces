#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        os << (i > 0 ? " " : "") << v[i];
    }
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
    vi b(n);
    unordered_map<int, int> mp; 
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        ++mp[b[i]];
    }
    for (auto [k, c] : mp) {
        if (c % k) {
            cout << -1 << endl;
            return;
        }
    }
    unordered_map<int, pair<int, vi>> cand;
    int ai = 1;
    for (auto [k, c] : mp) {
        vi u;
        for (int j = 0; j < c / k; ++j, ++ai) {
            u.push_back(ai);
        }
        cand[k] = {0, u};
    }
    vi a(n);
    for (int i = 0; i < n; ++i) {
        int k = b[i];
        auto& [j, u] = cand[k];
        a[i] = u[j / k];
        ++j;
    }
    cout << a << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

