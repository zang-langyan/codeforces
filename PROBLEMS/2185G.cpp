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

class UF{
public:
    int n;
    vector<int> id;
    int N_components;
    vector<int> sz;
    ll t = 0LL;
    vector<char> active;

    UF(int N) : n(N), N_components(N){
        id.resize(N);
        active = vector<char>(N, false);
        sz = vector<int>(N,1);
        for (int i = 0; i < N; i++){
            id[i] = i;
        }
    };
    ll cnt(int g) {
        return 1LL * sz[g] * (sz[g] + 1) / 2;
    }
    void insert_union(int p, int q){
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) return;
        
        t -= cnt(pRoot) + cnt(qRoot);
        if (sz[pRoot] < sz[qRoot]) {
            id[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
            t += cnt(qRoot);
        } else {
            id[qRoot] = pRoot; 
            sz[pRoot] += sz[qRoot];
            t += cnt(pRoot);
        }

        N_components--;
    };

    void activate(int i) {
        active[i] = true;
        t += 1;

        if (i > 0 && active[i - 1]) {
            insert_union(i, i - 1);
        }
        if (i < n && active[i + 1]) {
            insert_union(i, i + 1);
        }
    }

    int find(int p){
        while(p != id[p]) p = id[p];
        return p;
    };

    bool connected(int p, int q){ return find(p) == find(q);};
    
    int count(){
        return N_components;
    };

    void print(){
        for (int i = 0; i < n; i++){
            cout << i << "->" << id[i] << endl;
        }
    };
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

constexpr int N = 32;
vi f(N, 1);
vi inv(N, 1);
void fac() {
    for (int i = 2; i < N; ++i) {
        f[i] = 1LL * f[i-1] * i % MOD;
        inv[i] = qpow(f[i], MOD-2);
    }
}

int A(int n, int m) {
    return 1LL * f[n] * inv[n-m] % MOD;
}

int C(int n, int m) {
    return 1LL * f[n] * inv[m] % MOD * inv[n - m] % MOD;
}

void preprocess() {
}

void solve() {
    int n;
    cin >> n;
    vector<unordered_map<int, ll>> as(n);
    vi mex(n), nxt(n), len(n);
    ll total = 0;
    unordered_map<int, ll> cnt;
    ll takeout = 0;
    for (int i = 0; i < n; ++i) {
        unordered_map<int, ll>& a = as[i];
        int l;
        cin >> l;
        len[i] = l;
        total += 1LL * l * (n-1);
        int m = 0;
        for (int j = 0; j < l; ++j) {
            int x;
            cin >> x;
            ++cnt[x];
            ++a[x];
        }
        while (a.contains(m)) {
            ++m;
        }
        mex[i] = m;
        ++m;
        while (a.contains(m)) {
            ++m;
        }
        nxt[i] = m;

        for (int x = 0; x < mex[i]; ++x) {
            if (a[x] == 1)
                takeout += mex[i] - x;
        }
    }
    ll base = reduce(mex.begin(), mex.end(), 0LL);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += 1LL * (nxt[i] - mex[i]) * cnt[mex[i]];
    }
    cout << ans + 1LL * base * total - 1LL * takeout * (n-1) << endl;
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