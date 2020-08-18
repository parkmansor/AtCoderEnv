#include "stdafx.h"
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
#define INF						2e9
#define MOD						(1000 * 1000 * 1000 + 7)
#define Ceil(x, n)				(((((x))+((n)-1))/n))		/* Nの倍数に切り上げ割り算 */
#define CeilN(x, n)				(((((x))+((n)-1))/n)*n)		/* Nの倍数に切り上げ */
#define FloorN(x, n)			((x)-(x)%(n))				/* Nの倍数に切り下げ */
#define IsOdd(x)				(((x)&0x01UL) == 0x01UL)			
#define IsEven(x)				(!IsOdd((x)))						
#define	BitSetV(Val,Bit)		((Val) |= (Bit))			
#define	BitTstV(Val,Bit)		((Val) & (Bit))				
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
	int	from;
	int	to;
	ll	dist;
	Edge(){}
	Edge(int from, int to, ll dist): from(from), to(to), dist(dist){}
};

// ベルマンフォード
template<class D, D intDist, class E>
struct BellmanFord
{
	// res[i] = sからiまでの最短距離
	vector<D> dist;
	vector<E> edgeList;
	bool update;
	int nodeMax;

	// 各節の最短経路を算出
	BellmanFord(int argNodeMax, const vector<E> &argEdgeList, int startPos) 
	{
		edgeList = argEdgeList;
		nodeMax = argNodeMax;
		dist = vector<D>(nodeMax, intDist);
		dist[startPos] = 0;

		for (int i = 0; i < nodeMax; i++) {
			update = false;
			for (E edge : edgeList) {
				D nextDist = dist[edge.from] + edge.dist;
				if (dist[edge.to] > nextDist) {
					dist[edge.to] = nextDist;
					update = true;
				}
			}
			if (!update) {
				break;
			}
		}
	}

	// まだ更新が可能かどうか
	bool isNegative(int nodeNo) 
	{
		vector<D> distTmp(nodeMax, intDist);
		distTmp = dist;
		vector<bool> negativeList(nodeMax, false);
		for (int i = 0; i < nodeMax; i++) {
			update = false;
			for (E edge : edgeList) {
				if (distTmp[edge.from] != intDist) {
					D nextDist = distTmp[edge.from] + edge.dist;
					if (distTmp[edge.to] > nextDist) {
						distTmp[edge.to] = nextDist;
						negativeList[edge.to] = true;
						update = true;
					}
				}
			}
			if (!update) {
				break;
			}
		}

		return negativeList[nodeNo];
	}
};


int main()
{
	int N, M;
	cin >> N >> M;
	
	vector<Edge> edgeList;
	REP(i, M) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		c = c * (-1);	// 最大値なので反転
		edgeList.emplace_back(Edge(a, b, c));
	}

	BellmanFord<ll, (ll)10e15, Edge> res(N, edgeList, 0);

	if (!res.isNegative(N - 1)) {
		cout << res.dist[N - 1] * (-1) << endl;
	} else {
		cout << "inf" << endl;
	}
	return 0;
}
