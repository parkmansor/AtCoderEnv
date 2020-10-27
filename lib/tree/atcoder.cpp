#include "bits/stdc++.h"
using namespace std;

// ��`
typedef long long         ll;
typedef pair<ll, ll>      P;
#define ALL(x)            (x).begin(),(x).end()
#define REP(i, n)         for(ll i = 0 ; i < (ll)n ; ++i)
#define REPN(i, m, n)     for(ll i = m ; i < (ll)n ; ++i)
#define VL                vector<ll>
#define VVL               vector<vector<ll>>
#define VVVL              vector<vector<vector<ll>>>
#define VC                vector<char>
#define VVC               vector<vector<char>>
#define INF               (ll)2e9
#define INF_LL            1LL<<60
#define MOD             998244353
//#define MOD               1000000007

ll Ceil(ll val, ll div)   { return (val + div - 1) / div; }
ll CeilN(ll val, ll div)  { return Ceil(val, div) * div; }
ll FloorN(ll x, ll n)     { return (x - x % n); }
bool IsOdd(ll x)          { return ((x & 1) == 1); }
bool IsEven(ll x)         { return ((x & 1) == 0); }

// �Z�O�����g�c���[
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
		segDataMax = 1;
		while (segDataMax < K) segDataMax *= 2;
		data.resize(2 * segDataMax - 1, 0);
	}

	void Add(int index, T addData)
	{
		// ���[�X�V
		index += segDataMax - 1;
		data[index] = addData;

		// �e�֔��f
		while (index != 0) {
			index = (index - 1) / 2;
			int downNodeNoL = index * 2 + 1;
			int downNodeNoR = index * 2 + 2;
			data[index] = joinExec(data[downNodeNoL], data[downNodeNoR]);
		}
	}

	// �Z�O�����g�c���[�̃f�[�^���擾
	ll GetSegDataNum()
	{
		return segDataMax;
	}

	// �Z�O�����g�c���[����f�[�^�擾
	T GetRangeData(int dataSt, int dataEnd, int nodeNo = 0, int rangeL = 0, int rangeR = -1)
	{
		// ���͈̔͂ɂ͂Ȃ�
		if (rangeR == -1) rangeR = segDataMax;
		if ((dataEnd <= rangeL) || (rangeR <= dataSt)) {
			return 0;
		}

		// �͈͂ɓ����Ă�
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

	// �S��Ԃ̃f�[�^�擾
	T GetAllRangeData(void)
	{
		return data[0];
	}
};

ll joinSegTree(ll left, ll right)
{
	return max(left, right);
}

void Solve()
{
	ll N, K;
	cin >> N >> K;
	VL A(N);
	REP(i, N) cin >> A[i];

	VL dp(300000 * 2 + 5, 0);
	SegmentTree<ll> segTree(300001, joinSegTree);
	REP(i, N) {
		ll a = A[i];
		ll l = max(a - K, (ll)0);
		ll r = a + K + 1;
		ll ret = segTree.GetRangeData(l, r);

		dp[a] = max(dp[a], (ll)ret + 1);
		segTree.Add(a, dp[a]);
	}

	sort(ALL(dp));
	cout << dp.back() << endl;
}

// ���C��
int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(15);
	Solve();
	return 0;
}
