#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

#define YES cout << "YES\n";
#define NO cout << "NO\n";


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
    vector<vi> g(n+1);
    vi indeg(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        if (x > y) {
            g[v].push_back(u);
            ++indeg[u];
        } else {
            g[u].push_back(v);
            ++indeg[v];
        }
    }
    deque<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) q.push_back(i);
    }
    vi vert(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        vert.push_back(u);
        for (int v : g[u]) {
            if (--indeg[v] == 0) {
                q.push_back(v);
            }
        }
    }
    vi p(n+1);
    for (int i = 1; i <= n; ++i) {
        p[vert[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        cout << (i > 1 ? " " : "") << p[i];
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

