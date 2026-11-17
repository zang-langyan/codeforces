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
    ll n;
    cin >> n;
    vll b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    ll g = 0, l = 1;
    for (int i = n-1; i >= 0; --i) {
        g = gcd(b[i], g);
        l = lcm(b[i] / g, l);
    }
    cout << l << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

