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
constexpr ll MOD = 998244353LL;
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template<class K, class Q>
std::ostream& operator<<(std::ostream& os, const std::pair<K, Q>& v);
template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);


void preprocess() {

}

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

void solve() {
    int n;
    cin >> n;
    vector<vi> g(n+1);
    for (int i = 0; i < n-1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    string s, t;
    cin >> s >> t;
    vi depth(n+1);
    bool valid = true;
    ll ans = 0;

    vll pow2(n, -1);
    pow2[0] = 1;
    vi kd(n, -1);
    function<void(int, int, int)> dfs = [&](int x, int fa, int c) {
        if (!valid) return;
        if (pow2[depth[x]] == -1) {
            pow2[depth[x]] = 2 * pow2[depth[fa]] % MOD; 
        }
        int sd = s[x-1] - '0';
        int td = t[x-1] - '0';
        int d = sd ^ td ^ c;
        c = (sd + c + d > 1);
        if (kd[depth[x]] == -1) {
            kd[depth[x]] = d;
            ans = (ans + d * pow2[depth[x]]) % MOD;
        } else if (kd[depth[x]] != d) {
            valid = false;
            return;
        }
        for (int y: g[x]) {
            if (y == fa) continue;
            depth[y] = 1 + depth[x];
            dfs(y, x, c);
        }
    };
    dfs(1, -1, 0);

    if (!valid) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
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