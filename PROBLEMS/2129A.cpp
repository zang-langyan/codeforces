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

ll findzero(ll x, ll r) {
    ll mask = (1 << (__lg(r) + 1)) - 1;
    return (~x) & mask; 
}

void solve() {
    ll n;
    cin >> n;
    vector<vll> S(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        S[i] = {a, b};
    }
    vll index(n);
    iota(index.begin(), index.end(), 0);

    sort(index.begin(), index.end(), [&](auto x, auto y){
        return S[x][0] < S[y][0] || (S[x][0] == S[y][0] && S[x][1] > S[y][1]);
    });
    ll l = 0, r = 0;
    vll pick(n, 1);
    ll k = n;
    for (int i : index) {
        ll a = S[i][0];
        ll b = S[i][1];
        if (a >= l && b <= r) {
            --k;
            pick[i] = 0;
        } else {
            if (a >= r) {
                l = a, r = b;
            } else {
                r = b;
            }
        }
    }
    cout << k << endl;
    for (int i = 0; i < n; ++i) {
        if (pick[i]) {
            cout << i+1 << " ";
        }
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

