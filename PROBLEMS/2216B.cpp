#include <bits/stdc++.h>
 
using namespace std;
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;

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
    ll t, h, u;
    cin >> t >> h >> u;
    if (t > 2 * h + u) {
        cout << 2LL * t + 3 * h + 2 * u + 1 << endl;
    } else {
        cout << 2LL * t + 3 * h + 3 * u - min(u,t) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int t;
    cin >> t;
    while (t--) solve();
}
