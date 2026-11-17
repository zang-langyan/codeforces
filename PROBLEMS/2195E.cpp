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

#define YES cout << "YES\n"
#define NO cout << "NO\n"
constexpr int inf   = 1'000'000'000;
constexpr ll  infLL = 0xffffffffLL;
constexpr ll MOD = 1'000'000'007;

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);

template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);


void preprocess() {

}


void solve() {
    ll n;
    cin >> n;
    vll l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        --l[i];
        --r[i];
    }
    vll f(n);
    function<ll(int)> dfs = [&](int x) -> ll {
        if (l[x] == -1) {
            f[x] = 1;
            return 1;
        }
        f[x] = (dfs(l[x]) + dfs(r[x]) + 3) % MOD;
        return f[x];
    };
    dfs(0);

    function<void(int)> dfs1 = [&](int x) -> void {
        if (l[x] == -1) {
            return;
        }
        f[l[x]] = (f[l[x]] + f[x]) % MOD;
        f[r[x]] = (f[r[x]] + f[x]) % MOD;
        dfs1(l[x]);
        dfs1(r[x]);
    };
    dfs1(0);
    for (int i = 0; i < n; ++i) {
        cout << (i > 0 ? " " : "") << f[i];
    }
    cout << endl;
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