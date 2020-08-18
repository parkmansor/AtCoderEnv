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
typedef pair<int, int>      P;

/*-----------------------------------------------------------------------------
　処理
 -----------------------------------------------------------------------------*/
bool check(string &dst, string &src, char addChar)
{
	if (dst == "X") {
		return true;
	}
	if (dst.size() < src.size() + 1) {
		return true;
	} else if (dst.size() == src.size() + 1) {
		string srcJoin = src + addChar;
		if (dst < srcJoin) {
			return true;
		}
	}

	return false;
}

int main()
{
	const static int machiNum[10] = { 0, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

	int N, M;
	cin >> N >> M;
	vector<int> A(M);
	REP(i, M) cin >> A[i];

	vector<string> dp(N + 1, "X");
	dp[0] = "";
	REP(i, N + 1) {
		if (dp[i] == "X") continue;
		REP(j, M) {
			auto one = machiNum[A[j]];
			if (i + one <= N) {
				char addChar = A[j] + '0';
				if (check(dp[i + one], dp[i], addChar)) {
					dp[i + one] = dp[i] + addChar;
				}
			}
		}
	}

	cout << dp[N] << endl;
	return 0;
}
