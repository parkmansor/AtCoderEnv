/* 2の乗未満か */
ll degree(ll n){
	ll degCnt = 0;
	while (n != 0) {
		n /= 2;
		degCnt++;
	}
	return degCnt;
}

/* 桁数を返す */
ll getDigitNum(ll n)
{
	ll digit = 0;

	while(n) {
		n /= 10;
		digit++;
	}
	return digit;
}

/* 桁を返す */
ll getDigitVal(ll N, int digitPos)
{
	REP(i, digitPos) {
		N /= 10;
	}
	return N % 10;
}

/* 階乗を求める(MOD付) */
ll factorial(ll kaijou)
{
	ll sumRes = 1;
	for (ll i = 1; i <= kaijou; i++) {
		ll sumPrev = sumRes % MOD;
		ll sumNext = sumPrev * (i % MOD);
		sumRes = sumNext % MOD;
	}
	return sumRes;
}

/* Nがbaseの何乗かを求める */
template<class T>
int getExponet(T N, int base)
{
	int res = 0;
	while (N) {
		N /= base;
		if (N != 0) {
			res++;
		}
	}
	return res;
}

/* baseのべき乗を求める */
template<class T>
T getPower(int exponet, int base)
{
	T ans = 1;
	for (int i = 0; i < exponet; i++) {
		ans *= base;
	}
	return ans;
}

/* 繰り返し二乗法 (xのy乗) */
ll binpow(ll x, ll y)
{
	ll res = 1LL;
	x %= MOD;
	while (y) {
		if (y & 1) res = (res * x) % MOD;
		y >>= 1;
		x = (x * x) % MOD;
	}
	return res;
}

/* コンビネーションのサムを求める(nC0 + nC1 + nC2...nCn) */
ll CombinationSum(ll n)
{
	if (n <= 0) {
		return 1;
	}
	
	ll ans = 0;
	for (ll i = 0; i <= n; i ++) {
		ll sum = 1;
		for (ll j = 0; j < i; j++) {
			sum *= (n - j);
			sum /= (1 + j);
		}
		ans += sum;
	}

	return ans;
}

const int step[8][2] = {
	{ -1, -1 },
	{ -1, 0 },
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
	{ 1, -1 },
	{ 0, -1 },
};

int H, W;
bool masuCheck(int sx, int sy)
{
	for (int i = 0; i < 8; i++) {
		int xNext = sx + step[i][0];
		int yNext = sy + step[i][1];
		if (!((0 <= xNext && xNext < H) && (0 <= yNext && yNext < W))) {
			continue;
		}
	}

	return true;
}

// Combination Table
ll C[51][51]; // C[n][k] -> nCk
void comb_table(int N){
	for (int i = 0; i <= N; ++i){
		for (int j = 0; j <= i; ++j){
			if (j == 0 || j == i){
				C[i][j] = 1LL;
			} else{
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]);
			}
		}
	}
}

