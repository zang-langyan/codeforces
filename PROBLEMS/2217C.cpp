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
    // Theorem 2.32 
    // gcd(a, n) = 1 <=> 0,a,2a,...,(n-1)a is mod n's complete residue system
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if (gcd(n,a) == 1 && gcd(m,b) == 1 && gcd(n,m) <= 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int t;
    cin >> t;
    while (t--) solve();
}
