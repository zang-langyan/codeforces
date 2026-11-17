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

template <typename T>
std::string bin(T v) {
    return std::bitset<64>(static_cast<unsigned long long>(v)).to_string();
}

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using ld = long double;
using vld = vector<long double>;
using pii = pair<int, int>;

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template<>
std::ostream& operator<<(std::ostream& os, const std::vector<char>& v);
template<class K, class Q>
std::ostream& operator<<(std::ostream& os, const std::pair<K, Q>& v);
template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);

#define YES cout << "YES\n"
#define NO cout << "NO\n"
constexpr int inf   = 1'000'000'000;
// constexpr ll  infLL = 0xffffffffLL;
constexpr ll  infLL = 1'000'000'000'000LL;
constexpr int MOD = 998244353;

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
    int n, m;
    cin >> n >> m;
    vi a(n), b(m), cnt(n+m+1), cb(n+m+1);
    for (int& x: a) {
        cin >> x;
        ++cnt[x];
    }
    for (int& x: b) {
        cin >> x;
        ++cb[x];
    }
    vi c(n + m + 1);
    for (int i = 1; i <= n+m; ++i) {
        if (!cnt[i]) continue;
        for (int j = 1; i * j <= n+m; ++j) {
            c[i * j] += cnt[i];
        }
    }
    ll alice = 0, bob = 0, common = 0;
    for (int i = 1; i <= n+m; ++i) {
        if (!cb[i]) continue;
        if (c[i] == n) alice += cb[i];
        else if (c[i] == 0) bob += cb[i];
        else common += cb[i];
    }
    if (common & 1) {
        ++alice;
    }
    if (alice > bob) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
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

template<>
std::ostream& operator<<(std::ostream& os, const std::vector<char>& v) {
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
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