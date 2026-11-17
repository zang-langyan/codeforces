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
    ll n, m;
    cin >> n >> m;
    map<ll, vll> f;
    for (int i = 0; i < m; ++i) {
        ll x;
        cin >> x;
        f[x/100].push_back(x);
    }
    vector<vll> fs;
    for (auto& [k, v]: f) {
        fs.push_back(v);
    }
    ll i = 0, j = fs.size()-1;
    vll fi(j+1);
    for (ll gi = 0; gi < n; gi+=2) {
        ll f1 = fs[i][fi[i]], f2 = fs[j][fi[j]];
        if (f1 == f2 && fi[i]+1 < fs[i].size()) {
            f2 = fs[i][fi[i]+1];
        }
        for (int _ = 0; _ < 3; ++_) {
            cout << (_ > 0 ? " " : "") << f1 << " " << f2; 
        }
        cout << endl;
        if (gi+1 == n) {
            break;
        }
        for (int _ = 0; _ < 3; ++_) {
            cout << (_ > 0 ? " " : "") << f2 << " " << f1; 
        }
        cout << endl;
        if (i == j) {
            fi[i] += 2;
            if (fi[i] >= fs[i].size()) {
                ++i;
            }
        } else {
            if (++fi[i] >= fs[i].size()) {
                ++i;
            }
            if (++fi[j] >= fs[j].size()) {
                --j;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

