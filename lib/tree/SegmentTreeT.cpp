
// セグメントツリー
template <typename T>
class SegmentTree
{
private:
	vector<T> data;
	int segDataMax;
	function<T(T, T)> joinExec;

public:
	SegmentTree(int N, function<T(T, T)> arg) : joinExec(arg)
	{
		ll shiftVal = 1;
		ll shiftNum = 1;
		while (shiftVal < N) {
			shiftVal *= 2;
			shiftNum++;
		}
		data.resize((ll)1 << shiftNum, T(1, 0));
		segDataMax = (ll)1 << (shiftNum - 1);
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
		if ((dataEnd <= rangeL) || (rangeR <= dataSt)) {
			return T(0, 0);
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

// ベクターを値とインデックスのマップに圧縮
template <class T>
map<T, int> compressVectorToMap(vector<T> vect)
{
	int cmpIdx = 0;
	map<T, int> idxTblMap;

	// 重複削除
	sort(vect.begin(), vect.end());
	vect.erase(unique(vect.begin(), vect.end()), vect.end());

	// 昇順にインデックスを割り当て
	for (auto one : vect) {
		idxTblMap[one] = cmpIdx;
		cmpIdx++;
	}

	return idxTblMap;
}

typedef pair<double, double>   PD;
void Solve()
{
	ll N, M;
	cin >> N >> M;
	VL P(M);
	vector<PD> ab(M);
	REP(i, M) cin >> P[i] >> ab[i].first >> ab[i].second, P[i]--;
	
	map<ll, int> no2idx = compressVectorToMap<ll>(P);

	// r[i + 1] = a[i] * r[i] + b[i] 
	// r[i + 2] = a[i + 1] * r[i + 1] + b[i + 1] 
	// r[i + 2] = a[i + 1] * a[i] * r[i] + a[i + 1] * b[i] + b[i + 1] 
	auto join = [](const PD &left, const PD &right)
	{
		PD	res;
		res.first = left.first * right.first;
		res.second = left.second * right.first + right.second;
		return res;
	};

	double ansMin = 1;
	double ansMax = 1;
	SegmentTree<PD> segTree((int)no2idx.size(), join);
	REP(i, M) {
		ll idx = no2idx[P[i]];
		segTree.Add(idx, ab[i]);
		PD allParam = segTree.GetAllRangeData();
		double ansOne = allParam.first + allParam.second;
		ansMin = min(ansOne, ansMin);
		ansMax = max(ansOne, ansMax);
	}

	cout << ansMin << endl;
	cout << ansMax << endl;
}
