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

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);


void preprocess() {

}

void solve() {
    int n;
    cin >> n;
    map<ll, ll> mp;
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        ++mp[x];
    }
    ll allp = 0;
    ll pc = 0;
    ll mxp = 0;
    vll single;
    for (auto& [k, c] : mp) {
        if (c >= 2) {
            allp += 2 * (c / 2) * k;
            pc += c / 2;
            mxp = max(mxp, k);
        }
        if (c & 1) single.push_back(k);
    }
    sort(single.rbegin(), single.rend());
    ll ans = 0;
    if (pc > 1) {
        ans = allp;
    }
    if (pc >= 1) {
        for (ll s: single) {
            ll t = s + allp;
            ll mx = max(mxp, s);
            if (t > 2 * mx) {
                ans = max(ans, t);
            }
        }
        for (int i = 0; i + 1 < single.size(); ++i) {
            ll s1 = single[i];
            ll s2 = single[i+1];
            ll t = allp + s1 + s2;
            ll mx = max(mxp, s1);
            if (t > 2 * mx) {
                ans = max(ans, t);
            }
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