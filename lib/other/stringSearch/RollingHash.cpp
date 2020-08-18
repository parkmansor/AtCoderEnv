/* ほぼ周期文字列 */
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
 -------------------------------------------------------------------------------*/
class RollingHash {
 
private:
	unsigned base = (unsigned)1e9 + 7;
	string hashStr;
	vector<ull> hashed;
	vector<ull> power;
 
public:
	// 文字列 s のハッシュテーブルを構築する。
	//	hash[i] = s[0] * base^i + s[1] * base^(i-1) … s[i - 1]
	RollingHash(const string &s) 
	{
		int strLen = (int)s.size();
		hashStr = s;
		hashed.assign(strLen + 1, 0);
		power.assign(strLen + 1, 0);
		power[0] = 1;
		for (int i = 0; i < strLen; i++) {
			power[i + 1] = power[i] * base;
			hashed[i + 1] = hashed[i] * base + s[i];
		}
	}
 
	// 区間 [l,r) のハッシュ値を求める。l文字目からr-1文字目。
	ull get(int l, int r) const 
	{
		//	hash[r] = s[0] * base^r-1 + … s[l - 1] * base^r-l-1 … s[r - 1]
		//	hash[l] = s[0] * base^l-1 + … s[l - 1]
		ull ret = hashed[r] - hashed[l] * power[r - l] + base;
		return ret;
	}
 
	// s1Posとs2Posの文字列を比較
	bool isSubStrSame(int s1Pos, int s2Pos, int strLen) const 
	{
		return (get(s1Pos, s1Pos + strLen) == get(s2Pos, s2Pos + strLen));
	}

    // 文字を変えたときのハッシュ
    ull getChgChar(int l, int r, int chgPos, char chgChar)
	{
		ull t1 = get(l, r);
		if ((l <= chgPos) && (chgPos < r)) {
			t1 += (chgChar - hashStr[chgPos]) * power[r - chgPos - 1];
		}
		return t1;
    }

	// ハッシュ値 h1 と, 長さ h2len のハッシュ値 h2 を結合する。
	ull connect(unsigned h1, int h2, int h2len) const 
	{
		ull ret = h1 * power[h2len] + h2;
		return ret;
	}
 
	// 区間[l1,r1) と, ハッシュテーブルが b からなる区間 [l2,r2) の文字列の最長共通接頭辞の長さを求める。
	int LCP(const RollingHash &b, int l1, int r1, int l2, int r2) 
	{
		int len = min(r1 - l1, r2 - l2);
		int low = -1, high = len + 1;
		while(high - low > 1) {
			int mid = (low + high) / 2;
			if (get(l1, l1 + mid) == b.get(l2, l2 + mid)) {
				low = mid;
			} else {
				high = mid;
			}
		}
		return (low);
	}
};
 
int main()
{
	string S;
	int Q;
	cin >> S >> Q;
	vector<int> l(Q), r(Q), t(Q);
	REP(i, Q) {
		cin >> l[i] >> r[i] >> t[i];
		l[i]--;
	}

	RollingHash rollHash(S);
	vector<string> ans(Q, "Yes");
	REP(i, Q) {
		int lPos = l[i];
		int rPos = l[i] + t[i];
		int strLenMax = r[i] - l[i] - t[i];
		if (strLenMax == 0) {
			continue;
		}

		int lb = 0;
		int lu = strLenMax;
		int mid = 0;
		while ((lb + 1) != lu) {
			mid = (lb + lu) / 2;
			if (rollHash.isSubStrSame(lPos, rPos, mid)) {
				lb = mid;
			} else {
				lu = mid;
			}
		}

		int lChgIdx = lPos + lb;
		int rChgIdx = rPos + lb;
		char lStr = S[lChgIdx];
		char rStr = S[rChgIdx];
		ull hash1_1 = rollHash.getChgChar(lPos, lPos + strLenMax, lChgIdx, rStr);
		ull hash1_2 = rollHash.getChgChar(rPos, rPos + strLenMax, lChgIdx, rStr);
		ull hash2_1 = rollHash.getChgChar(lPos, lPos + strLenMax, rChgIdx, lStr);
		ull hash2_2 = rollHash.getChgChar(rPos, rPos + strLenMax, rChgIdx, lStr);
		if ((hash1_1 != hash1_2)&&(hash2_1 != hash2_2)) {
			ans[i] = "No";
		}
	}

	REP(i, Q) {
		cout << ans[i] << endl;
	}
	return 0;
}
