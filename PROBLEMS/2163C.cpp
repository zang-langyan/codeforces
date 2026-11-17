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
template<class K, class Q>
std::ostream& operator<<(std::ostream& os, const std::pair<K, Q>& v);
template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);


void preprocess() {

}

void solve() {
    int n;
    cin >> n;
    vi a[2];
    a[0].resize(n);
    a[1].resize(n);
    for (int& x: a[0]) {
        cin >> x;
    }
    for (int& x: a[1]) {
        cin >> x;
    }
    vector<pii> pre(n), suf(n);
    pre[0] = {a[0][0], a[0][0]};
    suf[n-1] = {a[1][n-1], a[1][n-1]};
    for (int i = 1, j = n-2; i < n; ++i, --j) {
        pre[i] = {min(pre[i-1].first, a[0][i]), max(pre[i-1].second, a[0][i])};
        suf[j] = {min(suf[j+1].first, a[1][j]), max(suf[j+1].second, a[1][j])};
    }

    vi cand(2*n+1, inf);
    for (int i = 0; i < n; ++i) {
        int mi = min(pre[i].first, suf[i].first);
        int mx = max(pre[i].second, suf[i].second);
        cand[mi] = min(cand[mi], mx);
    }
    ll ans = 0;
    int r = inf;
    for (int l = 2 * n; l >= 1; --l) {
        r = min(r, cand[l]);
        if (r < inf) {
            ans += 2 * n - r + 1;
        }
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

template<class K, class Q>
std::ostream& operator<<(std::ostream& os, const std::pair<K, Q>& v) {
    os << "(" << v.first << ", " << v.second << ")";
    return os;
}