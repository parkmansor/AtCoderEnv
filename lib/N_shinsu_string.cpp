#include "stdafx.h"
#include <stdio.h>
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
#define ALL(a)					(a).begin(),(a).end()
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
typedef unsigned long long		SQWORD;
typedef pair<ll, ll>			P;

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
/* N進数の文字列取得(負にも対応) */
template<class T>
string getNumberBaseStr(T val, T base)
{
	string binStr;

	while (val != 0) {
		T amari = val % base;
		amari = abs(amari);
		binStr.push_back('0' + (int)amari);
		val -= amari;
		val /= base;
	}
	if (0 < binStr.size()) {
		reverse(binStr.begin(), binStr.end());
	} else {
		binStr.push_back('0');
	}
	return binStr;
}

int main()
{
	ll N;
	cin >> N;
	cout << getNumberBaseStr<ll>(N, -2) << endl;
	return 0;
}

