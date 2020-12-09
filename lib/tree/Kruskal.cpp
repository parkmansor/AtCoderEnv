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

// 枝定義
struct Edge
{
	int from;
	int	to;
	ll	cost;
	Edge(){}
	Edge(int from, int to, ll cost) : from(from), to(to), cost(cost){}
};

// クラスカル
bool compMin(const Edge &a, const Edge &b) { return a.cost < b.cost; };
ll Kruskal(int nodeNum, vector<Edge> &edgeList)
{
	ll totalCost = 0;
	sort(edgeList.begin(), edgeList.end(), [](const Edge &a, const Edge &b) { return a.cost < b.cost; });

	UnionFind<int> uFind(nodeNum);
	for (const auto &edgeOne : edgeList) {
		if (!uFind.same(edgeOne.from, edgeOne.to)) {
			uFind.unite(edgeOne.from, edgeOne.to);
			totalCost += edgeOne.cost;
		}
	}
	return totalCost;
}

// 処理
void Solve()
{
	ll N;
	cin >> N;
	vector<P> x(N);
	vector<P> y(N);

	REP(i, N) {
		ll a, b;
		cin >> a >> b;
		x[i] = { a, i };
		y[i] = { b, i };
	}
	sort(ALL(x));
	sort(ALL(y));

	vector<Edge> edge;
	auto makeEdge = [&](vector<P> &p) {
		REP(i, N - 1) {
			auto p1 = p[i];
			auto p2 = p[i + 1];
			ll cost = p2.first - p1.first;
			edge.emplace_back(Edge(p1.second, p2.second, cost));
		}
	};
	makeEdge(x);
	makeEdge(y);

	ll ans = Kruskal(N, edge);
	cout << ans << endl;
}
