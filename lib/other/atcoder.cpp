#include "bits/stdc++.h"
using namespace std;

// ’è‹`
typedef long long         ll;
typedef pair<ll, ll>      P;
#define ALL(x)            (x).begin(),(x).end()
#define REP(i, n)         for(ll i = 0 ; i < (ll)n ; ++i)
#define REPN(i, m, n)     for(ll i = m ; i < (ll)n ; ++i)
#define VL                vector<ll>
#define VVL               vector<vector<ll>>
#define VVVL              vector<vector<vector<ll>>>
#define VC                vector<char>
#define VVC               vector<vector<char>>
#define INF               (ll)2e9
#define INF_LL            1LL<<60
#define MOD             998244353
//#define MOD               1000000007

ll Ceil(ll val, ll div)   { return (val + div - 1) / div; }
ll CeilN(ll val, ll div)  { return Ceil(val, div) * div; }
ll FloorN(ll x, ll n)     { return (x - x % n); }
bool IsOdd(ll x)          { return ((x & 1) == 1); }
bool IsEven(ll x)         { return ((x & 1) == 0); }

void Solve()
{
	double P;
	cin >> P;

	auto calc = [&](double year) {
		double speed = pow(2, (year / 1.5));
		double totalYear = year + P / speed;
		return totalYear;
	};

	double lb = 0;
	double lu = 92;
	REP(i, 121) {
		double c1 = (lb * 2 + lu) / 3;
		double c2 = (lb + lu * 2) / 3;
		double val1 = calc(c1);
		double val2 = calc(c2);
		if (val1 <= val2) {
			lu = c2;
		} else {
			lb = c1;
		}
	}

	cout << calc(lu) << endl;
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
