#include <bits/stdc++.h>

using namespace std;
namespace rgs = std::ranges;

#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...)                                    \
    __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))

#define FOR_EACH_HELPER(macro, a1, ...)                         \
    macro(a1)                                                   \
    __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))

#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define DEBUG_PART(x) std::cout << " " #x ":" << (x);

#define DEBUG(...)                                              \
    do {                                                        \
        std::cout << "[DEBUG]:";                                \
        FOR_EACH(DEBUG_PART, __VA_ARGS__)                       \
        std::cout << std::endl;                                 \
    } while (0)

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using ld = long double;
using vld = vector<long double>;
using pii = pair<int, int>;

#define YES cout << "YES\n"
#define NO cout << "NO\n"
constexpr int inf   = 1'000'000'000;
// constexpr ll  infLL = 0xffffffffLL;
constexpr ll  infLL = 1'000'000'000'000LL;
constexpr int MOD = 998244353;
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template<class K, class Q>
std::ostream& operator<<(std::ostream& os, const std::pair<K, Q>& v);
template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);

class Fenwick {
    int n;
    std::vector<ll> tree;
public:
    Fenwick(int N) : n(N), tree(n+2, 0) {}

    void add(int i, ll x) {
        while (i <= n) {
            tree[i] = max(tree[i], x);
            i += i & -i;
        }
    }

    ll query(int i) {
        ll s = 0;
        while (i > 0) {
            s  = max(tree[i], s);
            i -= i & -i;
        }
        return s;
    }
};

long long qpow(long long a, int n) {
    long long res = 1LL;
    while (n) {
        if (n & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        n >>= 1;
    }
    return res % MOD;
}

constexpr int N = 52;
vi f(N, 1);
vi inv(N, 1);
void fac() {
    for (int i = 2; i < N; ++i) {
        f[i] = 1LL * f[i-1] * i % MOD;
        inv[i] = qpow(f[i], MOD-2);
    }
}

void preprocess() {

}

int A(int n, int m) {
    return 1LL * f[n] * inv[n-m] % MOD;
}

int C(int n, int m) {
    return 1LL * f[n] * inv[m] % MOD * inv[n - m] % MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<vi> g(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vi p(n+1);
    vi depth(n+1), depthsz(n+1);
    vector<set<int>> depthpar(n+1);
    vector<vi> layer(n+1);
    
    function<void(int, int)> dfs = [&](int x, int fa){
        p[x] = fa;
        depth[x] = depth[fa] + 1;
        depthsz[depth[x]]++;
        depthpar[depth[x]].insert(fa);
        layer[depth[x]].push_back(x);
        for (int y: g[x]) {
            if (y == fa) continue;
            dfs(y, x);
        }
    };
    dfs(1, 0);
    int k = 1;
    for (int d = 2; d <= n; ++d) {
        if (depthpar[d].size() == 1) {
            k = max(depthsz[d] + 1, k);
        } else {
            k = max(depthsz[d], k);
        }
    }
    cout << k << endl;
    return;

    vector<int> color(n + 1, 0);
    color[1] = 0;
    vector<vi> group(k);
    group[0].push_back(1);
    vector<int> bad(k, -1);
    for (int d = 2; d <= n && !layer[d].empty(); ++d) {
        auto &nodes = layer[d];
        int m = (int)nodes.size();

        sort(nodes.begin(), nodes.end(), [&](int a, int b) {
            return color[p[a]] < color[p[b]];
        });

        for (int i = 0; i < m; ++i) {
            int f = color[p[nodes[i]]];
            int badDelta = ((f - i) % k + k) % k;
            bad[badDelta] = d;
        }

        int delta = 0;
        while (bad[delta] == d) {
            ++delta;
        }

        for (int i = 0; i < m; ++i) {
            color[nodes[i]] = (i + delta) % k;
            group[(i + delta) % k].push_back(nodes[i]);
        }
    }

    for (auto& gg: group) {
        cout << gg.size() << " " << gg << endl;
    }
}

int main() {
    preprocess();
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

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

template<class K, class Q>
std::ostream& operator<<(std::ostream& os, const std::pair<K, Q>& v) {
    os << "(" << v.first << ", " << v.second << ")";
    return os;
}