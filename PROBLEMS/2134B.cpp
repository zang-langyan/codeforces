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
    int n, k;
    cin >> n >> k;
    vll a(n);
    ll g = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        g = gcd(a[i], g);
    }
    if (g > 1) {
        cout << a;
        return;
    }
    if (k & 1) {
        for (auto x : a) {
            if (x & 1) {
                cout << x + k << " ";
            } else {
                cout << x << " ";
            }
        }
        cout << '\n';
        return;
    }
    for (auto x : a) {
        cout << x + k * (x % (k + 1)) << " ";
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

