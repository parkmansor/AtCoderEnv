
// MODのべき乗(n の p乗)
ll powMod(ll n, ll p)
{
	ll res = 1;
	while (p) {
		if (p & 1) (res *= n) %= MOD;
		(n *= n) %= MOD;
		p >>= 1;
	}
	return res;
}

// MODの2のべき乗
ll powMod2(ll p)
{
	return powMod(2, p);
}

// MODの逆元
ll invMod(ll n)
{
	return powMod(n, MOD - 2);
}

/* コンビネーション */
ll CombinationMod(ll n, ll r)
{
	if (n <= 0) {
		return 1;
	}

	ll sum = 1;
	ll maxR = min(n - r, r);
	for (ll j = 0; j < maxR; j++) {
		sum *= (n - j);
		sum %= MOD;
		sum *= invMod(maxR - j);
		sum %= MOD;
	}

	return sum;
}

// テーブルを作る前処理
const int MAX = 2 * 1000 * 1000 + 5;
long long fac[MAX], finv[MAX], inv[MAX];
void CombInit()
{
	fac[0] = fac[1] = 1;
	finv[0] = finv[1] = 1;
	inv[1] = 1;
	for (int i = 2; i < MAX; i++){
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
		finv[i] = finv[i - 1] * inv[i] % MOD;
	}
}

// 二項係数計算(nCk)
long long CombExec(int n, int k)
{
	if (n < k) return 0;
	if (n < 0 || k < 0) return 0;
	return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

const int mod = MOD;
class mint {
public:
	long long x;
	mint(long long x = 0) : x((x % mod + mod) % mod) {}
	mint operator-() const {
		return mint(-x);
	}
	mint& operator+=(const mint& a) {
		if ((x += a.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator-=(const mint& a) {
		if ((x += mod - a.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator*=(const  mint& a) {
		(x *= a.x) %= mod;
		return *this;
	}
	mint operator+(const mint& a) const {
		mint res(*this);
		return res += a;
	}
	mint operator-(const mint& a) const {
		mint res(*this);
		return res -= a;
	}
	mint operator*(const mint& a) const {
		mint res(*this);
		return res *= a;
	}
	mint pow(ll t) const {
		if (!t) return 1;
		mint a = pow(t >> 1);
		a *= a;
		if (t & 1) a *= *this;
		return a;
	}
	mint inv() const {
		return pow(mod - 2);
	}
	mint& operator/=(const mint& a) {
		return (*this) *= a.inv();
	}
	mint operator/(const mint& a) const {
		mint res(*this);
		return res /= a;
	}
};
