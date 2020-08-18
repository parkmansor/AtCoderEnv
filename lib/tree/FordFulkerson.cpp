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
#define REP(i, n)				for (int (i) = 0 ; (i) < (int)(n) ; ++(i))
#define REPN(i, m, n)			for (int (i) = m ; (i) < (int)(n) ; ++(i))
#define INF						(ll)2e9
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
// 枝定義
struct Edge
{
	int	toIdx;
	int	revIdx;
	ll	cap;
	Edge(){}
	Edge(int to, int rev, ll capArg): toIdx(to), revIdx(rev), cap(capArg){}
};

// グラフ定義(二次元配列)
using Graph = vector<vector<Edge>>;
 
// フォード・ファルカーソン
class FordFulkerson 
{
private:
	int V;
	Graph G;
	vector<bool> isUsed;

private:
	ll dfs(int from, int sinkPos, ll flow)
	{
		if (from == sinkPos) {
			return flow;
		}

		ll flowOne = 0;
		isUsed[from] = true;
		for (Edge &edge : G[from]) {
			int to = edge.toIdx;
			if (!isUsed[to]) {
				if (0 < edge.cap) {
					flowOne = dfs(to, sinkPos, min(flow, edge.cap));
					if (0 < flowOne) {
						edge.cap -= flowOne;
						G[to][edge.revIdx].cap += flowOne;
						break;
					}
				}
			}
		}
		return flowOne;
	}

public:
	FordFulkerson(int N)
	{
		G.resize(N);
	}

	// 枝を追加
	void AddEdge(int from, int to, ll cap)
	{
		int revIdxTo = G[to].size();
		int revIdxFrom = G[from].size();
		G[from].emplace_back(to, revIdxTo, cap);
		G[to].emplace_back(from, revIdxFrom, 0);
	}

	// 最大フローを求める
	ll GetMaxFlow(int startPos, int endPos)
	{
		ll maxFlow = 0;
		V = (int)G.size();
		isUsed.resize(V);
		for (;;) {
			fill(isUsed.begin(), isUsed.end(), false);
			ll flowOne = dfs(startPos, endPos, INF);
			if (flowOne == 0) {
				break;
			}
			maxFlow += flowOne;
		}
		return maxFlow;
	}
};


int main()
{
	int N;
	cin >> N;
	vector<ll> a(N);
	REP(i, N) {
		cin >> a[i];
	}
	
	ll plusSum = 0;
	REP(i, N) {
		if (0 <= a[i]) {
			plusSum += a[i];
		}
	}
	
	FordFulkerson fordFulk(N + 2);
	
	// 始点→i(残す)
	int start = 0;
	REP(i, N) {
		if (a[i] <= 0) {
			fordFulk.AddEdge(start, i + 1, a[i] * -1);
		} else {
			fordFulk.AddEdge(start, i + 1, 0);
		}
	}
	
	// i→終点（たたく)
	int end = N + 1;
	REP(i, N) {
		if (0 < a[i]) {
			fordFulk.AddEdge(i + 1, end, a[i]);
		} else {
			fordFulk.AddEdge(i + 1, end, 0);
		}
	}
	
	// i→j（たたく組み)
	for (int i = 1; i <= N; i++) {
		for (int j = 2 * i; j <= N; j += i) {
			fordFulk.AddEdge(i, j, INF);
		}
	}

	// 最大流量
	ll ans = fordFulk.GetMaxFlow(start, end);
	cout << plusSum - ans << endl;
	return 0;
}

