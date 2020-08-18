// 一次元累積和
template<class T>
class Ruiseki
{
private:
	int num;

public:
	vector<T> sumVal;
	Ruiseki(const vector<T> &srcVal)
	{
		num = srcVal.size();
		sumVal.resize(num + 1, 0);
		for (int i = 0; i < num; i++) {
			sumVal[i + 1] = sumVal[i] + srcVal[i];
		}
	}

	T GetSumAll()
	{
		return sumVal[num];
	}

	// [start, endIdx) ※endIdxは含まない
	T GetSumRange(int startIdx, int endIdx)
	{
		return sumVal[endIdx] - sumVal[startIdx];
	}

	// [0, endIdx) ※endIdxは含まない
	T GetSumFromTop(int endIdx)
	{
		return sumVal[endIdx] - sumVal[0];
	}

	// [startIdx, N] ※startIdxは含む
	T GetSumFromEnd(int startIdx)
	{
		return sumVal[num] - sumVal[startIdx];
	}
};

// 二次元累積和
template<class T>
class Ruiseki2D
{
private:
	ll xNum, yNum;

public:
	vector<vector<T>> sumVal;
	Ruiseki2D(const vector<vector<T>> &srcVal)
	{
		xNum = srcVal.at(0).size();
		yNum = srcVal.size();
		sumVal.resize(yNum + 1, vector<T>(xNum + 1));
		for (ll i = 0; i < yNum; i++) {
			for (ll j = 0; j < xNum; j++) {
				sumVal[i + 1][j + 1] = sumVal[i][j + 1] + sumVal[i + 1][j] - sumVal[i][j] + srcVal[i][j];
			}
		}
	}

	T GetSumAll()
	{
		return sumVal[yNum][xNum];
	}

	T GetSumRange(ll startIdxX, ll startIdxY, ll endIdxX, ll endIdxY)
	{
		return sumVal[endIdxY][endIdxX] - sumVal[startIdxY][endIdxX] - sumVal[endIdxY][startIdxX] + sumVal[startIdxY][startIdxX];
	}

	T GetSumFromTop(ll endIdxX, ll endIdxY)
	{
		return GetSumRange(0, 0, endIdxX, endIdxY);
	}

	T GetSumFromEnd(ll startIdxX, ll startIdxY)
	{
		return GetSumRange(startIdxX, startIdxY, xNum, yNum);
	}
};

// 処理
void Solve()
{
	ll H, W;
	cin >> H >> W;
	VLL C(H, VL(W));
	REP(i, H) REP(j, W) cin >> C[i][j];
	REP(i, H) REP(j, W) if (IsOdd(i + j)) C[i][j] *= -1;
	Ruiseki2D<ll> ruiseki(C);

	auto execBody = [&](ll hLen, ll wLen) {
		REP(i, H - hLen + 1) {
			REP(j, W - wLen + 1) {
				ll endX = j + wLen;
				ll endY = i + hLen;
				ll sum = ruiseki.GetSumRange(j, i, endX, endY);
				if (sum == 0) return true;
			}
		}
		return false;
	};

	ll ans = 0;
	REPN(i, 1, H + 1) {
		REPN(j, 1, W + 1) {
			ll masu = i * j;
			if (ans < masu) {
				if (execBody(i, j)) {
					ans = masu;
				}
			}
		}
	}

	cout << ans << endl;
}
