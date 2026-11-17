#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

#define YES cout << "YES\n"
#define NO cout << "NO\n"


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
    ll n, m;
    cin >> n >> m;
    if (m < n || n * (n+1) / 2 < m) {
        cout << -1 << endl;
        return;
    }
    if (m == n) {
        cout << 1 << endl;
        for (ll i = 2; i <= n; ++i) {
            cout << 1 << " " << i << endl; 
        }
        return;
    }
    if (m == n * (n+1) / 2) {
        cout << n << endl;
        for (ll i = 1; i < n; ++i) {
            cout << n << " " << i << endl; 
        }
        return;
    }
    // \sum subseq + n - len(subseq) = m
    // \sum subseq{1,n-1} = m-n
    ll k = m - n;
    vll b;
    for (ll i = n-1; i >= 1; --i) {
        if (i <= k) {
            k -= i;
            b.push_back(i+1);
        }
    }
    cout << b[0] << endl;
    unordered_set<ll> seen;
    seen.insert(b[0]);
    for (int i = 1; i < b.size(); ++i) {
        cout << b[0] << " " << b[i] << endl;
        seen.insert(b[i]);
    }
    cout << b[0] << " " << 1 << endl;
    for (int i = 2; i <= n; ++i) {
        if (!seen.contains(i)) {
            cout << 1 << " " << i << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

