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
#include <functional>
#include <climits>
#include <sstream>
#include <iomanip>
#include <map>
#include <stack>
#include <tuple>
#include <numeric>
#include <assert.h>
#include <functional>

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
#define MAX_DWORD				(0xFFFFFFFF)
#define	MAX_SDWORD				((SDWORD)0x7FFFFFFF)
#define	MIN_SDWORD				((SDWORD)0x80000000)
#define	MAX_QWORD				((QWORD)0xFFFFFFFFFFFFFFFF)
#define	MIN_QWORD				((QWORD)0x0000000000000000)
#define	MAX_SQWORD				((SQWORD)0x7FFFFFFFFFFFFFFF)
#define	MIN_SQWORD				((SQWORD)0x8000000000000000)
#define M_PI					3.14159265358979323846

typedef long					SDWORD;
typedef long long				SQWORD;
typedef unsigned long			DWORD;
typedef unsigned long long int	QWORD;
typedef long long ll;
typedef pair<double, double>	P;

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
#define N_MAX	(200 * 1000)
#define K_MAX	(10)
#define M_MAX	(10)
#define Q_MAX	(10)
#define H_MAX	(1000)
#define W_MAX	(1000)

// セグメントツリー
template <typename T>
class SegmentTree
{
private:
	vector<T> data;
	int segDataMax;
	function<T(T, T)> joinExec;

public:
	SegmentTree(int K, function<T(T, T)> arg) : joinExec(arg)
	{
		data.resize(1 << K, P(1, 0));
		segDataMax = 1 << (K - 1);
	}

	void Add(int index, T addData)
	{
		// 末端更新
		index += segDataMax - 1;
		data[index] = addData;

		// 親へ反映
		while (index != 0) {
			index = (index - 1) / 2;
			int downNodeNoL = index * 2 + 1;
			int downNodeNoR = index * 2 + 2;
			data[index] = joinExec(data[downNodeNoL], data[downNodeNoR]);
		}
	}

	// セグメントツリーのデータ数取得
	ll GetSegDataNum()
	{
		return segDataMax;
	}

	// セグメントツリーからデータ取得
	T GetRangeData(int dataSt, int dataEnd, int nodeNo, int rangeL, int rangeR)
	{
		// この範囲にはない
		if ((dataEnd <= rangeL) || (rangeR <= dataSt)) {
			return P(0, 0);
		}

		// 範囲に入ってる
		if ((dataSt <= rangeL) && (rangeR <= dataEnd)) {
			return data[nodeNo];
		}

		int rangeM = (rangeL + rangeR) / 2;
		int downNodeNoL = nodeNo * 2 + 1;
		int downNodeNoR = nodeNo * 2 + 2;
		T vl = GetRangeData(dataSt, dataEnd, downNodeNoL, rangeL, rangeM);
		T vr = GetRangeData(dataSt, dataEnd, downNodeNoR, rangeM, rangeR);
		T vlr = joinExec(vl, vr);
		return vlr;
	}

	// 全区間のデータ取得
	T GetAllRangeData(void)
	{
		return data[0];
	}
};

P joinSegTree(const P &left, const P &right)
{
	P	joinRes;
	joinRes.first = left.first * right.first;
	joinRes.second = left.second * right.first + right.second;
	return joinRes;
}

struct ParamInfo {
	ll	boxNo;
	P	param;
};

int main()
{
	ll N;
	int M;
	cin >> N >> M;
	vector<ll> boxNoList;
	vector<ParamInfo> paramList;
	REP(i, M) {
		ParamInfo paramOne;
		cin >> paramOne.boxNo >> paramOne.param.first >> paramOne.param.second;
		paramList.push_back(paramOne);
		boxNoList.push_back(paramOne.boxNo);
	}

	// 箱の番号をインデックスに圧縮
	int idx = 0;
	sort(boxNoList.begin(), boxNoList.end());
	boxNoList.erase(unique(boxNoList.begin(), boxNoList.end()), boxNoList.end());
	map<ll, int> boxNoToIdx;
	for (auto boxNoOne : boxNoList) {
		boxNoToIdx[boxNoOne] = idx;
		idx++;
	}

	// 一個づつ更新
	double ansMax = 1;
	double ansMin = 1;
	SegmentTree<P> segTree(18, joinSegTree);
	for (auto paramOne : paramList) {
		idx = boxNoToIdx[paramOne.boxNo];
		segTree.Add(idx, paramOne.param);
		P param = segTree.GetAllRangeData();
		double nowRes = param.first + param.second;
		ansMax = max(nowRes, ansMax);
		ansMin = min(nowRes, ansMin);
	}
	printf("%lf\n", ansMin);
	printf("%lf\n", ansMax);
	return 0;
}
