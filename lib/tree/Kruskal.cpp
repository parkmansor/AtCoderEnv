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
template<class T>
class UnionFind
{
private:
	vector<T> parentNo;
	vector<T> parentRank;
	vector<T> parentSize;

public:
	// コンストラクタ
	UnionFind(int n) 
	{
		parentNo.resize(n);
		parentRank.resize(n, 0);
		parentSize.resize(n, 1);
		for (int i = 0; i < n; i++) {
			// 始めは全部ROOT
			parentNo[i] = i;
		}
	}

	int root(T x) 
	{
		if (parentNo[x] == x) {
			return x;
		} else {
			T rootParentNo = root(parentNo[x]);
			parentNo[x] = rootParentNo;
			return rootParentNo;
		}
	}

	bool same(T x, T y) 
	{
		return root(x) == root(y);
	}

	int size(T x) 
	{
		return parentSize[root(x)];
	}

	void unite(T xc, T yc) 
	{
		T xr = root(xc);
		T yr = root(yc);
		if (xr == yr) {
			return;
		}
		if (parentRank[xr] < parentRank[yr]) {
			parentNo[xr] = yr;
			parentSize[yr] += parentSize[xr];
		} else {
			parentNo[yr] = xr;
			parentSize[xr] += parentSize[yr];
			if (parentRank[xr] == parentRank[yr]) {
				parentRank[xr]++;
			}
		}
	}
};

// 枝定義
struct Edge
{
	int from;
	int	to;
	ll	cost;
	Edge(){}
	Edge(int from, int to, ll cost): from(from), to(to), cost(cost){}
};

bool distCmp(const Edge &a, const Edge &b) { return a.cost < b.cost; };

// クラスカル
ll Kruskal(int nodeNum, vector<Edge> edgeList)
{
	ll totalCost = 0;
	sort(edgeList.begin(), edgeList.end(), distCmp);

	UnionFind<int> uFind(nodeNum);
	for (auto edgeOne : edgeList) {
		if (!uFind.same(edgeOne.from, edgeOne.to)) {
			uFind.unite(edgeOne.from, edgeOne.to);
			totalCost += edgeOne.cost;
		}
	}
	return totalCost;
}

int main()
{
	// 入力
	int N;
	cin >> N;
	
	vector<pair<ll, int>> xList;
	vector<pair<ll, int>> yList;
	REP(i, N) {
		ll a, b;
		cin >> a >> b;
		xList.emplace_back(pair<ll, int>{a, i});
		yList.emplace_back(pair<ll, int>{b, i});
	}
	sort(xList.begin(), xList.end());
	sort(yList.begin(), yList.end());

	vector<Edge> edgeList;
	REP(i, N - 1) {
		ll cost;
		int from, to;
		pair<ll, int> *pList;
		pList = &xList[i];
		cost = abs(pList[1].first - pList[0].first);
		to = pList[1].second;
		from = pList[0].second;
		edgeList.emplace_back(Edge{from, to, cost});

		pList = &yList[i];
		cost = abs(pList[1].first - pList[0].first);
		to = pList[1].second;
		from = pList[0].second;
		edgeList.emplace_back(Edge{from, to, cost});
	}

	// クラスカル
	ll ans = Kruskal(N, edgeList);
	cout << ans << endl;
	return 0;
}
