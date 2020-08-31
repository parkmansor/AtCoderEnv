/* 最大公約数 */
ll gcd(ll a, ll b) 
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

/* 最小公倍数 */
ll lcm(ll a, ll b) 
{
	ll gcdRes = gcd(a, b);
	return (a * (b / gcdRes));
}

/* 素数判定 */
bool isPrime(ll p) 
{
	for (ll i = 2; i <= sqrt(p); i++) if (p % i == 0) return false;
	return p > 1;
}

/* 素因数分解 */
map<ll, ll> factMap;
void primeFactor(ll n)
{
	if ((n % 2) == 0){
		while((n % 2) == 0) {
			factMap[2]++;
			n = n / 2;
		}
	}

	for(ll i = 3; i <= sqrt(n); i += 2){
		while ((n % i) == 0){
			factMap[i]++;
			n = n / i;
		}
	}

	if (n != 1) {
		factMap[n]++;
	}
}

/* 約数の列挙 */
vector<ll> divisorExec(ll n)
{
	vector<ll> res;
    for(ll i = 1; i <= sqrt(n); i++){
		if ((n % i) == 0) {
			res.push_back(i);
			if ((i * i) != n) {
				res.push_back(n / i);
			}
		}
	}
	sort(res.begin(), res.end());
	return res;
}

/* 素数の列挙 */
vector<int> Eratosthenes(int N)
{
    std::vector<bool> is_prime(N + 1);
    for(int i = 0; i <= N; i++) {
        is_prime[i] = true;
    }

    std::vector<int> res;
    for(int i = 2; i <= N; i++ ) {
        if (is_prime[i]) {
            for(int j = 2 * i; j <= N; j += i) {
                is_prime[j] = false;
            }
            res.emplace_back(i);
        }
    }
    return res;
}
