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
		segDataMax = 1;
		while (segDataMax < K) segDataMax *= 2;
		data.resize(2 * segDataMax - 1, 0);
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
	T GetRangeData(int dataSt, int dataEnd, int nodeNo = 0, int rangeL = 0, int rangeR = -1)
	{
		// この範囲にはない
		if (rangeR == -1) rangeR = segDataMax;
		if ((dataEnd <= rangeL) || (rangeR <= dataSt)) {
			return 0;
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
