#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <climits>
#include <sstream>
#include <iomanip>
#include <map>
#include <stack>
#include <numeric>
#include <functional>

using namespace std;
#define ALL(x)              (x).begin(),(x).end()
#define REP(i, n)           for (int (i) = 0 ; (i) < (ll)(n) ; ++(i))
#define REPN(i, m, n)       for (int (i) = m ; (i) < (ll)(n) ; ++(i))
#define INF                 (int)2e9
#define MOD                 (1000 * 1000 * 1000 + 7)
#define Ceil(x, n)          (((((x))+((n)-1))/n))
#define CeilN(x, n)         (((((x))+((n)-1))/n)*n)
#define FloorN(x, n)        ((x)-(x)%(n))
#define IsOdd(x)            (((x)&0x01UL) == 0x01UL)
#define IsEven(x)           (!IsOdd((x)))
#define M_PI                3.14159265358979323846
typedef long long           ll;
typedef pair<ll, ll>	    P;
#define fi                  first
#define se                  second

/*-----------------------------------------------------------------------------
　処理
 -----------------------------------------------------------------------------*/
class BinaryIndexedTree {
private:
	int n;
	vector<ll> bit;

public:
	BinaryIndexedTree(int num)
	{
		// 0は番兵
		n = num + 1;
		bit.assign(n + 1, 0);
	}

	// idx is 1-indexed
	void add(int idx, ll val)
	{
		while (idx <= n) {
			bit[idx] += val;
			idx += idx & -idx;
		}
	}

	// [1, idx) idx is 1-indexed
	ll sum(int idx)
	{
		ll sum = 0;
		while (0 < idx) {
			sum += bit[idx];
			idx -= idx & (-idx);
		}
		return sum;
	}
	
	// [a, b) idx is 1-indexed
	ll range(int a, int b)
	{
		return (sum(b) - sum(a));
	}

	// val-th number (val is 0-indexed)
	int lower_bound(ll val)
	{
		int idx = 0;
		int k = 1;
		while (2 * k <= n) {
			k <<= 1;
		}
		for (; 0 < k; k >>= 1) {
			if (idx + k < n && bit[idx + k] < val) {
				val -= bit[idx + k];
				idx += k;
			}
		}
		return idx + 1;
	}
};

int main()
{
	ll N, K;
	cin >> N >> K;
	vector<ll> t(N);
	vector<ll> d(N);
	REP(i, N) {
		cin >> t[i] >> d[i];
		t[i]--;
	};

	vector<P> netaMax(N, { 0, 0 });
	REP(i, N) {
		auto &netaOne = netaMax[t[i]];
		if (netaOne.first < d[i]) {
			netaOne.first = d[i];
			netaOne.second = i;
		}
	}
	sort(netaMax.rbegin(), netaMax.rend());

	ll typeMax = 0;
	REP(i, N) {
		auto netaOne = netaMax[i];
		if (netaOne.first == 0) {
			break;
		}
		d[netaOne.second] = 0;
		typeMax++;
	}
	sort(d.rbegin(), d.rend());

	ll nokoriMax = N - typeMax;
	BinaryIndexedTree bitType(typeMax);
	BinaryIndexedTree bitNokori(nokoriMax);
	REP(i, typeMax) {
		bitType.add(i + 1, netaMax[i].first);
	}
	REP(i, nokoriMax) {
		bitNokori.add(i + 1, d[i]);
	}

	ll ans = 0;
	REPN(i, 1, K + 1) {
		ll ansOne;
		ll typeNum = min(typeMax, (ll)i);
		ll nokoriNum = min(nokoriMax, K - typeNum);
		if (K != typeNum + nokoriNum) continue;

		ansOne = typeNum * typeNum;
		ansOne += bitType.sum(typeNum);
		ansOne += bitNokori.sum(nokoriNum);
		ans = max(ans, ansOne);
	}

	cout << ans << endl;
	return 0;
}
