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
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    int ans = 0;
    int mask = 0;
    unordered_set<int> seen;
    for (int b = 30; b >= 0; --b){
        seen.clear();
        mask |= 1 << b;
        int cand = ans | (1 << b);
        for (int x: a) {
            x &= mask;
            if (seen.contains(cand ^ x)) {
                ans = cand;
                break;
            }
            seen.insert(x);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int t;
    cin >> t;
    while (t--) solve();
}
