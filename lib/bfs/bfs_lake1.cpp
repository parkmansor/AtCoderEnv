#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <string>
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
#define	BitSetV(Val,Bit)		((Val) |= (Bit))			
#define	BitTstV(Val,Bit)		((Val) & (Bit))				
#define M_PI					3.14159265358979323846
typedef long long				ll;
typedef pair<ll, ll>			P;

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
// 枝定義
struct Edge
{
	int	from;
	int	to;
	Edge(){}
	Edge(int a, int b): from(a), to(b){}
};

// グラフ定義(二次元配列)
template <class E>
using Graph = vector<vector<E>>;

int main()
{
	int N, A, B, M;
	cin >> N >> A >> B >> M;
	A--; B--;
	
	Graph<Edge>	G(N);
	REP(i, M) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[a].emplace_back(a, b);
		G[b].emplace_back(b, a);
	}

	// bfs
	vector<ll> pathCnt(N, 0);
	vector<ll> dist(N, INF);
	queue<int> que;

	// 初期化
	que.push(A);
	pathCnt[A] = 1;
	dist[A] = 0;
	
	// bfs
	while (!que.empty()) {
		int nodeNo = que.front();
		que.pop();
		const auto &edge = G[nodeNo];

		for (auto edgeOne : edge) {
			if (dist[edgeOne.to] > dist[edgeOne.from] + 1) {
				// 新しい最短経路
				dist[edgeOne.to] = dist[edgeOne.from] + 1;
				pathCnt[edgeOne.to] = pathCnt[edgeOne.from];
				que.push(edgeOne.to);
			} else if (dist[edgeOne.to] == dist[edgeOne.from] + 1) {
				pathCnt[edgeOne.to] += pathCnt[edgeOne.from];
				pathCnt[edgeOne.to] %= MOD;
			}
		}
	}

	cout << pathCnt[B] << endl;
	return 0;
}
