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
    int p, q;
    cin >> p >> q;
    // 2nm + n + m = (2n+1)m + n = p + 2q
    for (int n = 1; n <= (int)sqrt((float)p/2 + q); ++n) {
        if ((p+2*q-n) > 0 && (p+2*q-n) % (2*n+1) == 0) {
            int m = (p+2*q-n) / (2*n+1);
            if (abs(m - n) <= p) {
                cout << n << " " << m << endl;
                return;
            }
        }
    }
    cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

