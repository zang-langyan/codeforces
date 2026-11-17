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

ll findzero(ll x, ll r) {
    ll mask = (1 << (__lg(r) + 1)) - 1;
    return (~x) & mask; 
}

void solve() {
    ll n, l, r, k;
    cin >> n >> l >> r >> k;
    if (n == 2) {
        cout << -1 << endl;
        return;
    }
    if (n & 1) {
        cout << l << endl;
        return;
    }
    ll cand = 1LL << (__lg(l) + 1LL);
    if (cand > r) {
        cout << -1 << endl;
        return;
    }

    if (k < n-1) {
        cout << l << endl;
    } else {
        cout << cand << endl;
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

