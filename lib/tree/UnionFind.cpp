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

void Solve()
{
	ll N, M;
	cin >> N >> M;
	VL a(M), b(M);
	REP(i, M) {
		cin >> a[i] >> b[i];
		a[i]--; b[i]--;
	}

	UnionFind<int> uFindR(N);
	REP(i, M) {
		uFindR.unite(a[i], b[i]);
	}

	map<ll, ll> mp;
	REP(i, N) {
		mp[uFindR.root(i)]++;
	}

	cout << mp.size() - 1 << endl;
}
