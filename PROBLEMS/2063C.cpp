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

/* ------------------ overloads ------------------ */
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template<>
std::ostream& operator<<(std::ostream& os, const std::vector<char>& v);
template<class K, class Q>
std::ostream& operator<<(std::ostream& os, const std::pair<K, Q>& v);
template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b);


/* ------------------ Memoize --------------------- */
// function_traits
template <typename T, typename = void>
struct function_traits;

// function pointer
template <typename R, typename... Args>
struct function_traits<R(*)(Args...), void> {
    using return_type = R;
    using args_tuple  = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

// function type (i.e. decltype(f) = R(Args...) )
template <typename R, typename... Args>
struct function_traits<R(Args...), void> {
    using return_type = R;
    using args_tuple  = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

// std::function
template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>, void> {
    using return_type = R;
    using args_tuple  = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

// lambda / struct with operator()
template <typename F>
struct function_traits<F, std::void_t<decltype(&F::operator())>>
    : function_traits<decltype(&F::operator())> {};

// TupleHash
inline void hash_combine(std::size_t& seed, std::size_t v) {
    seed ^= v + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}

inline std::size_t fmix64(std::size_t k) {
    k ^= k >> 33;
    k *= 0xff51afd7ed558ccdULL;
    k ^= k >> 33;
    k *= 0xc4ceb9fe1a85ec53ULL;
    k ^= k >> 33;
    return k;
}

template <typename Tuple, std::size_t... I>
std::size_t tuple_hash_impl(const Tuple& t, std::index_sequence<I...>) {
    std::size_t seed = 0;
    (hash_combine(seed,
        std::hash<std::tuple_element_t<I, Tuple>>{}(std::get<I>(t))), ...);
    return fmix64(seed);
}

struct TupleHash {
    template <typename... Ts>
    std::size_t operator()(const std::tuple<Ts...>& t) const {
        return tuple_hash_impl(t, std::index_sequence_for<Ts...>{});
    }
};

// Memoized Class
template <typename F>
class Memoized {
    using Traits    = function_traits<F>;
    using R         = std::decay_t<typename Traits::return_type>;
    using ArgsTuple = typename Traits::args_tuple;

    // make (i.e. const std::string&) decay to (std::string)
    template <typename T> struct decay_tuple;
    template <typename... Args>
    struct decay_tuple<std::tuple<Args...>> {
        using type = std::tuple<std::decay_t<Args>...>;
    };
    using KeyType = typename decay_tuple<ArgsTuple>::type;

    F func_;
    std::unordered_map<KeyType, R, TupleHash> cache_;

    template <std::size_t... I, typename... CallArgs>
    KeyType make_key(std::index_sequence<I...>, CallArgs&&... args) const {
        return KeyType{
            static_cast<std::decay_t<std::tuple_element_t<I, ArgsTuple>>>(
                std::forward<CallArgs>(args))...
        };
    }

public:
    explicit Memoized(F f) : func_(std::move(f)) {}

    template <typename... CallArgs>
    R operator()(CallArgs&&... args) {
        static_assert(sizeof...(CallArgs) == Traits::arity,
                      "Argument count mismatch");

        if constexpr (std::is_void_v<R>) {
            func_(std::forward<CallArgs>(args)...);
        } else {
            KeyType key = make_key(
                std::index_sequence_for<CallArgs...>{},
                std::forward<CallArgs>(args)...);

            if (auto it = cache_.find(key); it != cache_.end()) {
                return it->second;
            }

            R result = func_(std::forward<CallArgs>(args)...);
            auto [it, ok] = cache_.emplace(std::move(key), std::move(result));
            return it->second;
        }
    }

    void clear()             { cache_.clear(); }
    std::size_t size() const { return cache_.size(); }
    const std::unordered_map<KeyType, R, TupleHash>& get_cache() const {
        return cache_;
    }
};

template <typename F>
auto memoize(F f) {
    return Memoized<std::decay_t<F>>(std::move(f));
}

/* ---------------------- Macros ----------------------- */
#define YES cout << "YES\n"
#define NO cout << "NO\n"
constexpr int inf   = 1'000'000'000;
// constexpr ll  infLL = 0xffffffffLL;
constexpr ll  infLL = 1'000'000'000'000LL;
constexpr int NEG = -1'000'000'000;
constexpr int MOD = 998244353;

/* ---------------------- Data Structures -------------------- */
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
        // active = vector<char>(N, false);
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
        
        // t -= cnt(pRoot) + cnt(qRoot);
        if (sz[pRoot] < sz[qRoot]) {
            id[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
            // t += cnt(qRoot);
        } else {
            id[qRoot] = pRoot; 
            sz[pRoot] += sz[qRoot];
            // t += cnt(pRoot);
        }

        --N_components;
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
    vector<vi> g(n+1);
    for (int i = 0; i < n-1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<array<array<int,2>,3>> f(n + 1);
    function<void(int,int)> dfs = [&](int x, int fa) {
        for (int j = 0; j <= 2; ++j) {
            for (int s = 0; s <= 1; ++s) {
                f[x][j][s] = NEG;
            }
        }

        f[x][0][0] = 0;
        f[x][1][1] = (int)g[x].size();

        for (int y : g[x]) {
            if (y == fa) continue;
            dfs(y, x);

            array<array<int,2>,3> nf;
            for (int j = 0; j <= 2; ++j) {
                for (int s = 0; s <= 1; ++s) {
                    nf[j][s] = NEG;
                }
            }

            for (int j1 = 0; j1 <= 2; ++j1) {
                for (int s = 0; s <= 1; ++s) {
                    if (f[x][j1][s] == NEG) continue;
                    for (int j2 = 0; j1 + j2 <= 2; ++j2) {
                        for (int t = 0; t <= 1; ++t) {
                            if (f[y][j2][t] == NEG) continue;
                            int val = f[x][j1][s] + f[y][j2][t] - (s & t);
                            nf[j1 + j2][s] = max(nf[j1 + j2][s], val);
                        }
                    }
                }
            }
            for (int j = 0; j <= 2; ++j) {
                for (int s = 0; s <= 1; ++s){
                    f[x][j][s] = nf[j][s];
                }
            }
        }
    };
    dfs(1, 0);
    cout << max(f[1][2][0], f[1][2][1]) - 1 << endl;
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
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