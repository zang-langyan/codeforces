#include <bits/stdc++.h>

using namespace std;

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

#define YES cout << "YES\n"
#define NO cout << "NO\n"
constexpr int inf   = 1'000'000'000;
constexpr ll  infLL = 0xffffffffLL;


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
    ll n, k;
    string s;
    cin >> n >> k >> s;
    vll a(n);
    ll last0 = -1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (s[i] == '0') {
            a[i] = -1e13;
            last0 = i;
        }
    }
    ll mx = 0, cur = 0;
    for (int i = 0; i < n; ++i) {
        cur = max(cur + a[i] , a[i]);
        mx = max(mx, cur);
    }
    if (mx > k || (mx != k && last0 == -1) ) {
        NO;
        return;
    }
    if (last0 != -1) {
        ll pre = 0, suf = 0, c = 0;
        for (int i = last0 + 1; i < n; ++i) {
            c += a[i];
            pre = max(pre, c);
        }
        c = 0;
        for (int i = last0 - 1; i >= 0; --i) {
            c += a[i];
            suf = max(suf, c);
        }
        a[last0] = k - pre - suf;
    }
    YES;
    cout << a << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}

