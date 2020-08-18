#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <string>
#include <cstring>
#include <climits>
#include <sstream>
#include <iomanip>
#include <map>
#include <stack>
#include <tuple>
#include <numeric>
#include <functional>
#include <unordered_map>

using namespace std;

/*-----------------------------------------------------------------------------
　定義
 -------------------------------------------------------------------------------*/
#define REP(i, n)				for (int (i) = 0 ; (i) < (int)(n) ; ++(i))
#define REPN(i, m, n)			for (int (i) = m ; (i) < (int)(n) ; ++(i))
#define INF						2e9
#define MOD						(1000 * 1000 * 1000 + 7)
#define Ceil(x, n)				(((((x))+((n)-1))/n))		/* Nの倍数に切り上げ割り算 */
#define CeilN(x, n)				(((((x))+((n)-1))/n)*n)		/* Nの倍数に切り上げ */
#define FloorN(x, n)			((x)-(x)%(n))				/* Nの倍数に切り下げ */
#define IsOdd(x)				(((x)&0x01UL) == 0x01UL)			
#define IsEven(x)				(!IsOdd((x)))						
#define ArrayLength(x)			(sizeof( x ) / sizeof( x[ 0 ]))
#define	MAX_QWORD				((QWORD)0xFFFFFFFFFFFFFFFF)
#define M_PI					3.14159265358979323846
typedef long long				ll;
typedef unsigned long long int	QWORD;
typedef pair<ll, ll>			P;

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
// 二部マッチング
static const int pairNothing = -1;
class BipartiteMatching
{
private:
	vector<vector<int>> G;
	vector<bool> isUsed;
	vector<int> match;

public:
	int V;

private:
	bool dfs(int nodeNo)
	{
		isUsed[nodeNo] = true;
		for (int i = 0; i < (int)G[nodeNo].size(); i++) {
			int to = G[nodeNo][i];
			int matchNodeNo = match[to];
			
			// ペアなし
			if (pairNothing == matchNodeNo) {
				match[nodeNo] = to;
				match[to] = nodeNo;
				return true;
			}

			// ペアあるが未チェック
			if (!isUsed[matchNodeNo]) {
				if (dfs(matchNodeNo)) {
					match[nodeNo] = to;
					match[to] = nodeNo;
					return true;
				}
			}
		}

		return false;
	}

public:
	BipartiteMatching(int N)
	{
		G.resize(N);
		isUsed.resize(N);
		V = N;
	}

	// 枝を追加
	void AddEdge(int from, int to)
	{
		G[from].emplace_back(to);
		G[to].emplace_back(from);
	}

	int GetMatchingPairNum()
	{
		int res = 0;
		match.resize(V, pairNothing);
		for (int nodeNo= 0; nodeNo < V; nodeNo++) {
			if (match[nodeNo] == pairNothing) {
				if (0 < G[nodeNo].size()) {
					fill(isUsed.begin(), isUsed.end(), false);
					if (dfs(nodeNo)) {
						res++;
					}
				}
			}
		}

		return res;
	}

};

void makeFundoList(vector<pair<int, int>> &fundouList, vector<int> &volToIdxTbl, int volume, int henLenMax)
{
	for (int i = 1; i < henLenMax; i++) {
		int fundou1 = (volume * i) / henLenMax;
		int fundou2 = (volume - fundou1);
		fundouList.emplace_back(fundou1, fundou2);
		volToIdxTbl.emplace_back(fundou1);
		volToIdxTbl.emplace_back(fundou2);
	}
}

int main()
{
	int N;
	cin >> N;
	vector<int> X, Y, Z;
	int maxAreaSize = 0;
	REP(i, N) {
		int a, b, c;
		cin >> a >> b >> c;
		X.emplace_back(a);
		Y.emplace_back(b);
		Z.emplace_back(c);
		maxAreaSize = max(maxAreaSize, a * b * c);
	}

	vector<int> volToIdxTbl;
	vector<pair<int, int>> fundouList;
	REP(i, N) {
		int volume = X[i] * Y[i] * Z[i];
		makeFundoList(fundouList, volToIdxTbl, volume, X[i]);
		makeFundoList(fundouList, volToIdxTbl, volume, Y[i]);
		makeFundoList(fundouList, volToIdxTbl, volume, Z[i]);
	}
	
	// 体積とインデックスの変換テーブル
	int cmpIdx = 0;
	map<int, int> volToIdxTblMap;
	sort(volToIdxTbl.begin(), volToIdxTbl.end());
	volToIdxTbl.erase(unique(volToIdxTbl.begin(), volToIdxTbl.end()), volToIdxTbl.end());
	for (auto one : volToIdxTbl) {
		volToIdxTblMap[one] = cmpIdx;
		cmpIdx++;
	}

	// 鉄塊を切ってできる分銅のペア
	BipartiteMatching res(volToIdxTblMap.size() * 2);
	for (auto one : fundouList) {
		res.AddEdge(volToIdxTblMap[one.first], volToIdxTblMap[one.second] + volToIdxTblMap.size());
	}

	// 全員の分銅合計 － 切ったペア両方が使える数　
	int ans = res.V - res.GetMatchingPairNum();
	cout << ans << endl;
	return 0;
}

