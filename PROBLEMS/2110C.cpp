#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

#define YES cout << "YES\n"
#define NO cout << "NO\n"
constexpr int inf   = 1'000'000'000;
constexpr ll  infLL = 0xffffffffLL;

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
    int n;
    cin >> n;
    vi d(n+1), l(n+1), r(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    bool valid = true;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
        if (l[i] > i || r[i] < l[i-1]) {
            valid = false;
        }
    }

    if (!valid) {
        cout << -1 << endl;
        return;
    }
    
    int left = 0;
    vi cand;
    for (int i = 1; i <= n; ++i) {
        if (d[i] == -1) {
            cand.push_back(i);
        } else {
            left += d[i];
        }
        while (left < l[i]) {
            if (cand.empty()) {
                cout << -1 << endl;
                return;
            }
            d[cand.back()] = 1;
            ++left;
            cand.pop_back();
        }
        while (left + cand.size() > r[i]) {
            if (cand.empty()) {
                cout << -1 << endl;
                return;
            }
            d[cand.back()] = 0;
            cand.pop_back();
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << max(d[i], 0) << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

