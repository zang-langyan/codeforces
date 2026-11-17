#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

#define YES cout << "YES\n"
#define NO cout << "NO\n"
const int inf   = 10e9;
const ll  infLL = 0xffffffffLL;

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
    vi a(n);
    int mx = 0, g = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mx = max(a[i], mx);
        g = gcd(g, a[i]);
    }

    int cnt = 0;
    for (int e : a) {
        if (e == g) ++cnt;
    }
    if (cnt > 0) {
        cout << n - cnt << endl;
        return;
    }
    unordered_set<int> st(a.begin(), a.end());
    unordered_map<int, int> f;
    priority_queue<int> pq;
    for (int x: st) {
        f[x] = 0;
        pq.push(x);
    }
    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();
        for (int y : st) {
            int gxy = gcd(x,y);
            if (gxy == x) continue;
            if (!f.count(gxy) || f[gxy] > f[x] + 1) {
                f[gxy] = f[x] + 1;
                pq.push(gxy);
            }
        }
    }
    cout << f[g] + n - 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

