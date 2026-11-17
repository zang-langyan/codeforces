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
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;
    if (s[0] != t[0]) {
        cout << -1 << endl;
        return;
    }
    vector<vi> pos(26);
    for (int i = 0; i < n; ++i) {
        pos[s[i] - 'a'].push_back(i);
    }

    auto getLast = [&](int c, int lim) -> int {
        if (lim < 0) return -1;
        auto &v = pos[c];
        auto it = upper_bound(v.begin(), v.end(), lim);
        if (it == v.begin()) return -1;
        return *(it-1);
    };
    vi d(n);
    int mx = 0, l = n;
    for (int i = n-1; i >= 0; --i) {
        int c = t[i] - 'a';
        int p = getLast(c, min(l, i));
       
        if (p == -1) {
            cout << -1 << endl;
            return;
        }
        d[i] = i - p;
        if (d[i] > k) {
            cout << -1 << endl;
            return;
        }
        l = min(l, p);
        mx = max(mx, d[i]);
    }
    string ss = s;
    cout << mx << endl;
    for (int i = 0; i < mx; ++i) {
        for (int j = n-1; j >= 0; --j) {
            if (d[j] > 0) {
                --d[j];
                ss[j] = ss[j-1];
            }
        }
        cout << ss << endl;
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