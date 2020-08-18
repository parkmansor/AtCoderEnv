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
typedef pair<ll, ll>			P;

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
// 星空木
template <typename T>
class StarrySkyTree
{
private:
	vector<T> dataChildRes;
	vector<T> dataAdd;
	int segDataMax;
	function<T(T, T)> joinChildData;

public:
	StarrySkyTree(int K, T init, function<T(T, T)> arg) : joinChildData(arg)
	{
		dataChildRes.resize(1 << K, init);
		dataAdd.resize(1 << K, init);
		segDataMax = 1 << (K - 1);
	}

	// 特定の区間に反映
	void AddDataRange(int dataSt, int dataEnd, int nodeNo, int rangeL, int rangeR, T addVal)
	{
		// この区間にはない
		if ((dataEnd <= rangeL) || (rangeR <= dataSt)) {
			return;
		}

		// 区間に入ってる
		// 区間に入ってるところのデータだけ更新、この後、親へ反映していく
		if ((dataSt <= rangeL) && (rangeR <= dataEnd)) {
			dataAdd[nodeNo] += addVal;
			return;
		}

		// 子更新
		int rangeM = (rangeL + rangeR) / 2;
		int downNodeNoL = nodeNo * 2 + 1;
		int downNodeNoR = nodeNo * 2 + 2;
		AddDataRange(dataSt, dataEnd, downNodeNoL, rangeL, rangeM, addVal);
		AddDataRange(dataSt, dataEnd, downNodeNoR, rangeM, rangeR, addVal);

		// 親更新、子の分を反映
		T dataL = dataChildRes[downNodeNoL] + dataAdd[downNodeNoL];
		T dataR = dataChildRes[downNodeNoR] + dataAdd[downNodeNoR];
		dataChildRes[nodeNo] = joinChildData(dataL, dataR);
	}

	// 全区間に反映
	void AddDataAll(int dataSt, int dataEnd, T addVal)
	{
		AddDataRange(dataSt, dataEnd, 0, 0, segDataMax, addVal);
	}


	// セグメントツリーのデータ数取得
	ll GetSegDataNum()
	{
		return segDataMax;
	}

	// セグメントツリーからデータ取得(特定区間)
	T GetRangeData(int dataSt, int dataEnd, int nodeNo, int rangeL, int rangeR)
	{
		// この範囲にはない
		if ((dataEnd <= rangeL) || (rangeR <= dataSt)) {
			return;
		}

		// 範囲に入ってる
		if ((dataSt <= rangeL) && (rangeR <= dataEnd)) {
			return dataAdd[nodeNo] + dataChildRes[nodeNo];
		}

		int rangeM = (rangeL + rangeR) / 2;
		int downNodeNoL = nodeNo * 2 + 1;
		int downNodeNoR = nodeNo * 2 + 2;
		T vl = GetRangeData(dataSt, dataEnd, downNodeNoL, rangeL, rangeM);
		T vr = GetRangeData(dataSt, dataEnd, downNodeNoR, rangeM, rangeR);
		T vlr = joinChildData(vl, vr) + dataAdd[nodeNo];
		return vlr;
	}

	// 全区間のデータ取得
	T GetAllRangeData(void)
	{
		return dataChildRes[0] + dataAdd[0];
	}
};

int main()
{
	int N;
	cin >> N;
	vector<int> S(N, 0), T(N, 0);
	REP(i, N) {
		cin >> S[i] >> T[i]; 
	}

	// 子供の大きいほうを親に反映
	auto joinChildData = [](ll left, ll right){ return max(left, right); };
	StarrySkyTree<ll> skyTree(18, 0, joinChildData);

	//　全部反映
	REP(i, N) {
		skyTree.AddDataAll(S[i], T[i], 1);
	}
	
	// 1個ずつ減らしてもとに戻して
	ll ans = skyTree.GetAllRangeData();
	REP(i, N) {
		skyTree.AddDataAll(S[i], T[i], -1);
		ans = min(ans, skyTree.GetAllRangeData());
		skyTree.AddDataAll(S[i], T[i], 1);
	}
	cout << ans << endl;
	return 0;
}
