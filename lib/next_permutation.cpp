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

using namespace std;

/*-----------------------------------------------------------------------------
　定義
 -------------------------------------------------------------------------------*/
#define ALL(x)					(x).begin(),(x).end()
#define REP(i, n)				for (int (i) = 0 ; (i) < (ll)(n) ; ++(i))
#define REPN(i, m, n)			for (int (i) = m ; (i) < (ll)(n) ; ++(i))
#define INF						(int)2e9
#define MOD						(1000 * 1000 * 1000 + 7)
#define Ceil(x, n)				(((((x))+((n)-1))/n))		/* Nの倍数に切り上げ割り算 */
#define CeilN(x, n)				(((((x))+((n)-1))/n)*n)		/* Nの倍数に切り上げ */
#define FloorN(x, n)			((x)-(x)%(n))				/* Nの倍数に切り下げ */
#define IsOdd(x)				(((x)&0x01UL) == 0x01UL)			
#define IsEven(x)				(!IsOdd((x)))						
#define M_PI					3.14159265358979323846
typedef long long				ll;
typedef pair<ll, ll>			P;

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
int main()
{
	int N;
	cin >> N;
	vector<int> P(N), Q(N);
	REP(i, N) cin >> P[i];
	REP(i, N) cin >> Q[i];

	// idx
	vector<int> pemiVal(N);
	REP(i, N) pemiVal[i] = i + 1;

	// 順列
	int idx = 1;
	int pNo = 0;
	int qNo = 0;
	do {
		if (P == pemiVal) pNo = idx;
		if (Q == pemiVal) qNo = idx;
		idx++;
	} while (next_permutation(pemiVal.begin(), pemiVal.end()));

	cout << abs(pNo - qNo) << endl;
	return 0;
}
