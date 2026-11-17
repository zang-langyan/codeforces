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
    fac();
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
    vi a(n+1);
    int s = 0;
    for (int& x: a){
        cin >> x;
        s += x;
    }
    int k = s / n;
    int c = 0;
    for (int i = 1; i <= n; ++i) {
        a[0] += min(0, a[i] - k);
        a[i] = max(0, a[i] - k);
        if (a[i] == 0) {
            ++c;
        }
        if (a[0] < 0 || a[i] > 1) {
            cout << 0 << endl;
            return;
        }
    }
    if (c - a[0] < 0) {
        cout << 0 << endl;
        return;
    }
    cout << 1LL * f[c] * f[n-c+a[0]] % MOD * inv[a[0]] % MOD << endl;
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