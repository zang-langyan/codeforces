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
    int n, l, r;
    cin >> n >> l >> r;
    vll pre(n+1);
    iota(pre.begin(), pre.end(), 0);
    pre[l-1] = pre[r] = n+1;
    vll ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = pre[i+1] ^ pre[i];
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int t;
    cin >> t;
    while (t--) solve();
}
