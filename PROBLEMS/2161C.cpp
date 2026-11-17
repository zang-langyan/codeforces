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
    int n, X;
    cin >> n >> X;
    vll a(n);
    ll sum = 0;
    ll ans = 0;
    vll seq;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a.begin(), a.end());
    
    int k = sum / X;
    ans = reduce(a.begin() + n - k, a.end());
    int r = 0;
    int i = 0;
    for (int j = n-k; j < n; ++j) {
        while (r + a[j] < X) {
            seq.push_back(a[i]);
            r += a[i];
            ++i;
        }
        seq.push_back(a[j]);
        r = (r + a[j]) % X;
    }
    for (; i < n-k; ++i) {
        seq.push_back(a[i]);
    }
    cout << ans << endl;
    cout << seq << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

