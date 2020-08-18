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
 -----------------------------------------------------------------------------*/
#define ALL(x)					(x).begin(),(x).end()
#define REP(i, n)				for (int (i) = 0 ; (i) < (ll)(n) ; ++(i))
#define REPN(i, m, n)			for (int (i) = m ; (i) < (ll)(n) ; ++(i))
#define INF						(int)2e9
#define MOD						(1000 * 1000 * 1000 + 7)
#define Ceil(x, n)				(((((x))+((n)-1))/n))		/* Nの倍数に切り上げ割り算 */
#define CeilN(x, n)				(((((x))+((n)-1))/n)*n)		/* Nの倍数に切り上げ */
#define FloorN(x, n)			((x)-(x)%(n))				/* Nの倍数に切り下げ */
#define IsOdd(x)				(((x)&0x01UL) == 0x01UL)			
#define IsEven(x)				(!IsOdd((x)))						
#define M_PI					3.14159265358979323846
typedef long long				ll;
typedef unsigned long			ul;
typedef unsigned long long		ull;
typedef pair<int, int>			P;

/*-----------------------------------------------------------------------------
　処理
 -----------------------------------------------------------------------------*/
// 接尾辞配列(Manber＆Myers)
class SuffixArray {

public:
	int m_strLen;
	vector<int> sa;			// 順番 → インデックス
	vector<int> idxToOrder;	// インデックス → 順番

private:
	string srcStr;
	vector<int> rank;
	int m_i;

public:
	SuffixArray(const string &s)
	{
		// i 元の文字列Sの位置i S[i:]
		// j 元の文字列Sの位置j S[j:]
		auto compare_sa = [&](int i, int j)	{
			int rnkA = rank[i];
			int rnkB = rank[j];
			if (rnkA != rnkB) {
				return (rnkA < rnkB);
			} else {
				int iIdx = i + m_i;
				int jIdx = j + m_i;
				int ri = (iIdx <= m_strLen) ? rank[iIdx] : -1;
				int rj = (jIdx <= m_strLen) ? rank[jIdx] : -1;
				return ri < rj;
			}
		};

		// 最初は1文字
		srcStr = s;
		m_strLen = s.size();
		sa.resize(m_strLen + 1);
		for (int i = 0; i <= m_strLen; i++) {
			sa[i] = i;
		}

		// ランクは文字コード
		rank.resize(m_strLen + 1);
		for (int i = 0; i < m_strLen; i++) {
			rank[i] = s[i];
		}
		rank[m_strLen] = -1;	// 空文字
	
		// i文字についてソートされてるところから2*i文字でソートする
		for (m_i = 1; m_i <= m_strLen; m_i *= 2) {
			sort(sa.begin(), sa.end(), compare_sa);
			
			auto nextRank = rank;
			nextRank[sa[0]] = 0;
			for (int j = 1; j <= m_strLen; j++) {
				nextRank[sa[j]] = nextRank[sa[j - 1]];
				if (compare_sa(sa[j - 1], sa[j])) {
					nextRank[sa[j]]++;
				}
			}
			rank = nextRank;
		}

		// 逆引き用
		idxToOrder.resize(m_strLen + 1);
		for (int i = 0; i <= m_strLen; i++) {
			idxToOrder[sa[i]] = i;
		}
	}

	// 文字列検索
	bool contain(const string &contStr)
	{
		int contStrLen = contStr.length();
		int lb = 0;
		int lu = m_strLen + 1;
		int mid = 0;
		while ((lb + 1) != lu) {
			mid = (lb + lu) / 2;
			if (srcStr.compare(sa[mid], contStrLen, contStr) < 0) {
				lb = mid;
			} else {
				lu = mid;
			}
		}
		return (srcStr.compare(sa[lu], contStrLen, contStr) == 0);
	}

	// ダンプ用
	void dumpSaStr()
	{
		int idx = 0;
		for (auto strIdx : sa) {
			cout<<  idx++ << " " << strIdx << " " << srcStr.substr(strIdx) << endl;
		}
	}
};

bool compExec(SuffixArray &sa, int orderMax, int K, int subStrLen)
{
	int strCnt = 0;
	
	for (int strIdx = 0; strIdx < sa.m_strLen; ) {
		strCnt++;
		if ((strIdx + subStrLen) <= sa.m_strLen) {
			if (sa.idxToOrder[strIdx] <= orderMax) {
				strIdx += subStrLen;
			} else {
				strIdx += (subStrLen - 1);
			}
		} else {
			break;
		}
	}

	return (strCnt <= K);
}

int main()
{
	int K;
	string S;
	cin >> K >> S;
	K++;
	int n = S.size();

	// くぎりなし
	if (K == 1) {
		cout << S << endl;	
		return 0;
	}

	// 1文字
	if (K == n) {
		char c = '1';
		REP(i, n) c = max(c, S[i]);
		cout << c << endl;	
		return 0;
	}

	// SA計算
	int subStrLen = Ceil(n, K);
	SuffixArray SA(S);
	// SA.dumpSaStr();

	// 候補を2分探索
	int lb = 0;
	int lu = n;
	while (lb + 1 != lu) {
		int mid = (lb + lu) / 2;
		if (!compExec(SA, mid, K, subStrLen)) {
			lb = mid;
		} else {
			lu = mid;
		}
	}

	cout << S.substr(SA.sa[lu], subStrLen) << endl;	
	return 0;
}
