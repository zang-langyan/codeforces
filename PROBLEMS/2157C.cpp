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
    int n, k, q;
    cin >> n >> k >> q;
    vector<pii> c1;
    vi a(n+1, -1), is1(n+1, false), is2(n+1, false);
    for (int _ = 0; _ < q; ++_) {
        int c, l, r;
        cin >> c >> l >> r;
        if (c == 1) {
            c1.push_back({l, r});
            for (int i = l; i <= r; ++i) {
                is1[i] = true;
            }
        } else {
            for (int i = l; i <= r; ++i) {
                is2[i] = true;
            }
        }
    }
    for (int i = 1, x = 0; i <= n; ++i) {
        if (!is1[i]) {
            a[i] = x++;
            if (x == k){
                x = 0;
            }
        }
    }
    rgs::sort(c1, [](const auto& x, const auto& y){
        if (x.second != y.second) return x.second < y.second;
        return x.first < y.first;
    });

    for (auto [l, r] : c1) {
        bool hask = false;
        for (int i = l; i <= r; ++i) {
            if (a[i] == k) {
                hask = true;
                break;
            }
        }
        if (hask) continue;
        int j = -1;
        for (int i = r; i >= l; --i) {
            if (!is2[i]) {
                j = i;
                break;
            }
        }
        if (j != -1) {
            a[j] = k;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1) {
            a[i] = k + 1;
        }
        cout << (i > 1 ? " " : "") << a[i];
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