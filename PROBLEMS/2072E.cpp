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
    ll k;
    cin >> k;
    if (k == 0) {
        cout << 0 << endl;
        return;
    }
    vll ms;
    ll cnt = 0;
    while (k) {
        ll l = 1, r = 500;
        while (l < r) {
            ll mid = l + (r - l) / 2;
            if (mid * (mid - 1) <= 2 * k) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        ms.push_back(l-1);
        ll m = ms.back();
        k -= m * (m - 1) / 2;
        cnt += m;
    }
    
    cout << cnt << endl;
    ll y = 0;
    ll offset = 0;
    for (ll m : ms) {
        for (ll x = 0; x < m; ++x) {
            cout << x + offset << " " << y << endl; 
        }
        ++y;
        offset += m;
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