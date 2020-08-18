#include "bits/stdc++.h"
using namespace std;

// ’è‹`
typedef long long         ll;
typedef pair<ll, ll>      P;
#define ALL(x)            (x).begin(),(x).end()
#define REP(i, n)         for(ll i = 0 ; i < (ll)n ; ++i)
#define REPN(i, m, n)     for(ll i = m ; i < (ll)n ; ++i)
#define REVREP(i, n)      for(ll i = n - 1; i >= 0 ; i--)
#define VL                vector<ll>
#define VVL               vector<vector<ll>>
#define VVVL              vector<vector<vector<ll>>>
#define VC                vector<char>
#define VVC               vector<vector<char>>
#define INF               (ll)2e9
#define INF_LL            1LL<<60
//#define MOD             998244353
#define MOD               1000000007

ll Ceil(ll val, ll div)   { return (val + div - 1) / div; }
ll CeilN(ll val, ll div)  { return Ceil(val, div) * div; }
ll FloorN(ll x, ll n)     { return (x - x % n); }
bool IsOdd(ll x)          { return ((x & 1) == 1); }
bool IsEven(ll x)         { return ((x & 1) == 0); }
template<class T> bool chmax(T& a, T b) { if (a <= b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, T b) { if (a >= b) { a = b; return 1; } return 0; }

void Solve()
{
	ll N, K;
	cin >> N >> K;
	VL P(N), C(N);
	REP(i, N) {
		cin >> P[i];
		P[i]--;
	}
	REP(i, N) cin >> C[i];

	ll nokori;
	ll sum = accumulate(ALL(C), ll(0));
	if (N < K) {
		ll cycle = max((ll)0, (K / N - 1));
		if (0 < sum) {
			sum *= cycle;
			nokori = K - cycle * N;
		} else {
			sum = 0;
			nokori = N;
		}
	} else {
		nokori = K;
		sum = 0;
	}

	ll ans = -2e14;
	for (ll startPos = 0; startPos < N; startPos++) {
		ll ansOne = -2e14;
		ll nowVal = sum;
		ll idx = startPos;
		REP(i, nokori) {
			nowVal += C[idx];
			ansOne = max(ansOne, nowVal);
			idx = P[idx];
		}
		ans = max(ansOne, ans);
	}

	cout << ans << endl;
}

// ƒƒCƒ“
int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(15);
	Solve();
	return 0;
}
