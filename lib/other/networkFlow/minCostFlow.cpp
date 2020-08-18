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
#include <assert.h>
#include <functional>
#include <unordered_map>

using namespace std;

/*-----------------------------------------------------------------------------
　定義
 -------------------------------------------------------------------------------*/
#define REP(i, n)				for (int (i) = 0 ; (i) < (int)(n) ; ++(i))
#define REPN(i, m, n)			for (int (i) = m ; (i) < (int)(n) ; ++(i))
#define INF						(int)2e9
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
// 枝定義
struct Edge
{
	int	toIdx;
	int	revIdx;
	int	cost;
	int	cap;
	Edge(){}
	Edge(int to, int rev, int costArg, int capArg): toIdx(to), revIdx(rev), cost(costArg), cap(capArg){}
};
 
// 最小費用流
class MinCostFlow 
{
private:
	vector<vector<Edge>> G;
	vector<int> dist;
	vector<int> prevV;
	vector<int> prevE;
	int nodeMax;

	// 各節の最短経路を算出
	void BellmanFord(int startPos, int endPos, int flow) 
	{
		fill(dist.begin(), dist.end(), INF);
		dist[startPos] = 0;

		bool update = true;
		while (update) {
			update = false;
			for (int v = 0; v < nodeMax; v++) {
				if (dist[v] == INF) continue;
				for (int i = 0; i < (int)G[v].size(); i++) {
					Edge &edge = G[v][i];
					if (0 < edge.cap) {
						int to = edge.toIdx;
						int nextDist = dist[v] + edge.cost;
						if (dist[to] > nextDist) {
							dist[to] = nextDist;
							prevV[to] = v;
							prevE[to] = i;
							update = true;
						}
					}
				}
			}
		}
	}

public:
	MinCostFlow(int N)
	{
		G.resize(N);
		dist.resize(N);
		prevV.resize(N);
		prevE.resize(N);
	}

	// 枝を追加
	void AddEdge(int from, int to, int cap, int cost)
	{
		int revIdxTo = G[to].size();
		int revIdxFrom = G[from].size();
		G[from].emplace_back(to, revIdxTo, cost, cap);
		G[to].emplace_back(from, revIdxFrom, -cost, 0);
	}

	// 最小費用流を求める
	int GetMinCostFlow(int startPos, int endPos, int totalFlow)
	{
		int remainFlow;
		int totalCost = 0;

		remainFlow = totalFlow;
		nodeMax = (int)G.size();
		while (0 < remainFlow) {
			BellmanFord(startPos, endPos, remainFlow);
			if (dist[endPos] == INF) {
				return -1;
			}

			// 流せる最大量
			int flowOne = remainFlow;
			for (int v = endPos; v != startPos; v = prevV[v]) {
				flowOne = min(flowOne, G[prevV[v]][prevE[v]].cap);
			}
			remainFlow -= flowOne;
			totalCost += flowOne * dist[endPos];

			// 枝の状態を更新
			for (int v = endPos; v != startPos; v = prevV[v]) {
				Edge &edge = G[prevV[v]][prevE[v]];
				edge.cap -= flowOne;
				G[v][edge.revIdx].cap += flowOne;
			}
		}

		return totalCost;
	}
};

int main()
{
	int takaraNum, keyNum, shopNum;
	cin >> takaraNum >> keyNum >> shopNum;
	
	vector<int> keyCostList;
	vector<vector<int>> shopHaveKeyNoList(shopNum);
	vector<vector<int>> keyMatchTakaraNo(keyNum);
	REP(i, keyNum) {
		int c, s, k;
		cin >> c >> s >> k;
		s--;
		keyCostList.emplace_back(c);
		shopHaveKeyNoList[s].emplace_back(i);
		REP(j, k) {
			int a; cin >> a; a--;
			keyMatchTakaraNo[i].emplace_back(a);
		}
	}
	vector<int> shopCostUpList(shopNum);
	REP(i, shopNum) cin >> shopCostUpList[i];

	// 始点→店集合→鍵集合→宝箱集合→終点
	int startIdx = 0;
	int shopTopIdx = startIdx + 1;
	int keyTopIdx = shopTopIdx + shopNum;
	int takaraTopIdx = keyTopIdx + keyNum;
	int endIdx = takaraTopIdx + takaraNum;
	MinCostFlow res(endIdx + 1);
	
	// 始点→店集合
	// 値段アップにかかるコストより多いキーは買うことができない
	// 多いキーを買わなければコストアップしてこない、capで表現
	REP(i, shopNum) {
		res.AddEdge(startIdx, shopTopIdx + i, shopCostUpList[i], 0);
	}

	// 店集合→鍵集合
	// 鍵の値段をコストで表現
	REP(i, shopNum) {
		for (auto keyNo : shopHaveKeyNoList[i]) {
			res.AddEdge(shopTopIdx + i, keyTopIdx + keyNo, 1, keyCostList[keyNo]);
		}
	}

	// 鍵集合→宝箱集合
	REP(i, keyNum) {
		for (auto takaraNo : keyMatchTakaraNo[i]) {
			res.AddEdge(keyTopIdx + i, takaraTopIdx + takaraNo, 1, 0);
		}
	}
	
	// 宝箱集合→終点
	REP(i, takaraNum) {
		res.AddEdge(takaraTopIdx + i, endIdx, 1, 0);
	}

	int ans = res.GetMinCostFlow(startIdx, endIdx, takaraNum);
	if (ans < takaraNum) {
		cout << -1 << endl;
	} else {
		cout << ans << endl;
	}
	return 0;
}
