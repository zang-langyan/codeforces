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
    int w, h, a, b;
    int x, y, u, v;
    cin >> w >> h >> a >> b;
    cin >> x >> y >> u >> v;

    if (x == u) {
        if ((y - v) % b) NO;
        else YES;
        return;
    }
    if (y == v) {
        if ((x - u) % a) NO;
        else YES;
        return;
    }
    if ((y - v) % b && (x - u) % a) NO;
    else YES;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

