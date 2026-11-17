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
constexpr ll  infLL = 0xffffffffLL;
constexpr ll MOD = 998244353LL;
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);


void preprocess() {

}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vi> g(n+1);
    for (int i = 0; i < n-1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vi op(m);
    for (int& o: op) {
        cin >> o;
    }
    vi depth(n+1);
    vector<vi> up(n+1, vi(20));
    function<void(int, int)> dfs = [&](int x, int fa) {
        up[x][0] = fa;
        for (int i = 1; i < 20; ++i) {
            up[x][i] = up[up[x][i-1]][i-1];
        }
        for (int y: g[x]) {
            if (y == fa) {
                continue;
            }
            depth[y] = depth[x] + 1;
            dfs(y, x);
        }
    };
    dfs(1, 0);
    auto lca = [&](int x, int y) {
        if (depth[x] < depth[y]) {
            swap(x, y);
        }
        int dis = depth[x] - depth[y];
        for (int i = 0; i < 20; ++i) {
            if (dis & (1 << i)) {
                x = up[x][i];
            }
        }
        if (x == y) {
            return y;
        }
        for (int i = 19; i >= 0; --i) {
            if (up[x][i] != up[y][i]) {
                x = up[x][i];
                y = up[y][i];
            }
        }
        return up[x][0];
    };
    int ans = depth[n];
    for (int o: op) {
        int fa = lca(o, n);
        if (fa == 1) {
            continue;
        }
        ans = max(ans, depth[o] + depth[n] - 2 * depth[fa] + 1);
    }
    cout << ans << endl;
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
