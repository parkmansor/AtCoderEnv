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
#define REP(i, n)				for (int (i) = 0 ; (i) < (int)(n) ; ++(i))
#define REPN(i, m, n)			for (int (i) = m ; (i) < (int)(n) ; ++(i))
#define INF						(ll)2e9
#define EPS						(double)1e-9
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
template<typename T>
struct Edge
{
	int	toIdx;
	int	revIdx;
	T	cap;
	Edge(){}
	Edge(int to, int rev, T capArg): toIdx(to), revIdx(rev), cap(capArg){}
};

// ディニック
template<typename T>
class Dinic  
{
private:
	using Graph = vector<vector<Edge<T>>>;
	int V;
	Graph G;
	vector<T>	minCost;
	vector<int>	iter;

private:
	bool bfs(int from, int sinkPos) 
	 {
		minCost.assign(V, - 1);
		queue<int> que;
		minCost[from] = 0;
		que.push(from);
		while(!que.empty() && minCost[sinkPos] == -1) {
			int p = que.front();
			que.pop();
			for(auto &edge : G[p]) {
				if((0 < edge.cap) && (minCost[edge.toIdx] == -1)) {
					minCost[edge.toIdx] = minCost[p] + 1;
					que.push(edge.toIdx);
				}
			}
		}
		return (minCost[sinkPos] != -1);
	}
	
	T dfs(int from, int sinkPos, T flow)
	{
		if (from == sinkPos) {
			return flow;
		}

		for(int i = iter[from]; i < (int)G[from].size(); i++) {
			auto &edge = G[from][i];
			if(0 < edge.cap && (minCost[from] < minCost[edge.toIdx])) {
				T flowOne = dfs(edge.toIdx, sinkPos, min(flow, edge.cap));
				if(0 < flowOne) {
					edge.cap -= flowOne;
					G[edge.toIdx][edge.revIdx].cap += flowOne;
					return flowOne;
				}
			}
		}
		return 0;
	}

public:
	Dinic(int N)
	{
		G.resize(N);
	}

	// 枝を追加
	void AddEdge(int from, int to, T cap)
	{
		int revIdxTo = G[to].size();
		int revIdxFrom = G[from].size();
		G[from].emplace_back(to, revIdxTo, cap);
		G[to].emplace_back(from, revIdxFrom, 0);
	}

	// 最大フローを求める
	T GetMaxFlow(int startPos, int endPos)
	{
		T maxFlow = 0;
		V = (int)G.size();
		while (bfs(startPos, endPos)) {
			iter.assign(V, 0);
			while (true) {
				T flowOne = dfs(startPos, endPos, INF);
				if (flowOne == 0) {
					break;
				}
				maxFlow += flowOne;
			}
		}
		return maxFlow;
	}
};

// 1回実行
bool execOne(double rate, int N, int M, vector<vector<int>> &A, vector<double> &S, vector<double> &T)
{
	// 始点→アイテム(M)→経験(N)→終点
	// 始点→アイテム	買う場合のコスト
	// アイテム→経験	買わなかったらここがつながり、アイテム→終点を切るしかない	
	// 経験→終点		買わなかった場合の損失
	int start = 0;
	int item = start + 1;
	int keiken = item + M;
	int end = keiken + N;
	Dinic<double> dinic(M + N + 2);

	// 始点→アイテム
	REP(i, M) {
		dinic.AddEdge(start, item + i, T[i] * rate);
	}

	// アイテム→経験→終点
	REP(i, N) {
		for (auto oneItem : A[i]) {
			dinic.AddEdge(oneItem, keiken + i, INF);
		}
		dinic.AddEdge(keiken + i, end, S[i]);
	}


	// 最小カット(費用＋経験の損失)
	double totalLoss = dinic.GetMaxFlow(start, end);
	double totalKeiken = accumulate(ALL(S), 0);
	return totalLoss < totalKeiken;
}

// メイン
int main()
{
	int N, M;
	cin >> N >> M;
	vector<double> S(N), T(M);
	REP(i, N) cin >> S[i];
	REP(i, M) cin >> T[i];
	vector<vector<int>> A(N);
	REP(i, N) {
		int k;
		cin >> k;
		REP(j, k) {
			int a;
			cin >> a;
			A[i].emplace_back(a);
		}
	}

	double lb = 0;
	double lu = 100 * 100 * 10;
	double mid;
	REP(i, 100) {
		mid = (lb + lu) / 2;
		if (execOne(mid, N, M, A, S, T)) {
			lb = mid;
		} else {
			lu = mid;
		}
	}

	cout << setprecision(10) << mid << endl;
	return 0;
}

