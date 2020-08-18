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
#include <cstdint>

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
#define	BitSetV(Val,Bit)		((Val) |= (Bit))			
#define	BitTstV(Val,Bit)		((Val) & (Bit))				
#define ArrayLength(x)			(sizeof( x ) / sizeof( x[ 0 ]))
#define	MAX_QWORD				((QWORD)0xFFFFFFFFFFFFFFFF)
#define M_PI					3.14159265358979323846
typedef long long				ll;
typedef unsigned long long int	QWORD;
typedef unsigned long long		SQWORD;
typedef pair<ll, ll>			P;

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
// 枝定義
struct Edge
{
	int from;
	int	to;
	int	dist;
	Edge(){}
	Edge(int from, int to, int dist): from(from), to(to), dist(dist){}
};

// ワーシャルフロイド
template<class T>
class WarshallFloyd
{
public:
	// distList[i][j] = iからjまでの最短距離
	vector<vector<T>> distList;

public:
	WarshallFloyd(int nodeNum, const vector<Edge> &edgeList)
	{
		distList.resize(nodeNum, vector<T>(edgeList.size(), (T)1e9));
		for (auto edgeOne : edgeList) {
			distList[edgeOne.from][edgeOne.to] = edgeOne.dist;
			distList[edgeOne.to][edgeOne.from] = edgeOne.dist;
		}

		for (int nodeCnt = 0; nodeCnt < nodeNum; nodeCnt++) {
			for (int i = 0; i < nodeNum; i++) {
				for (int j = 0; j < nodeNum; j++) {
					distList[i][j] = min(distList[i][j], distList[i][nodeCnt] + distList[nodeCnt][j]);
				}
			}
		}
	}
};


int main()
{
	// 入力
	int N, M, R;
	cin >> N >> M >> R;
	
	vector<int> pathList;
	REP(i, R) {
		int r;
		cin >> r;
		r--;
		pathList.emplace_back(r);
	}

	vector<Edge> edgeList;
	REP(i, M) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		edgeList.emplace_back(Edge(a, b, c));
		edgeList.emplace_back(Edge(b, a, c));
	}

	// ワーシャルフロイド
	WarshallFloyd<int> res(N, edgeList);

	// 順列
	ll ans = INF;
	sort(pathList.begin(), pathList.end());
	do {
		ll totalCost = 0;
		int from = pathList[0];
		for (int i = 1; i < pathList.size(); i++) {
			int to = pathList[i];
			totalCost += res.distList[from][to];
			from = to;
		}
		ans = min(ans, totalCost);
	} while (next_permutation(pathList.begin(), pathList.end()));

	cout << ans << endl;
	return 0;
}
