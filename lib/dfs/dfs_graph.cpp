// 枝定義
struct Edge
{
	int	from;
	int	to;
	Edge(){}
	Edge(int a, int b) : from(a), to(b){}
};

// dfs
vector<vector<int>>	G;
vector<bool>		isUsed;
bool dfs(int from, int to)
{
	for (auto nextTo : G[to]) {
		if (from != nextTo) {
			if (!isUsed[nextTo]) {
				isUsed[nextTo] = true;
				if (!dfs(to, nextTo)) {
					return false;
				}
			} else {
				return false;
			}
		}
	}

	return true;
}

// 処理
void Solve()
{
	int N, M;
	cin >> N >> M;
	vector<Edge>	edgeList;
	REP(i, M) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		edgeList.emplace_back(a, b);
	}

	// グラフ作成
	G.clear();
	G.resize(N);
	for (auto one : edgeList) {
		G[one.from].emplace_back(one.to);
		G[one.to].emplace_back(one.from);
	}

	int ans = 0;
	isUsed.clear();
	isUsed.resize(N, false);
	REP(i, N) {
		if (!isUsed[i]) {
			isUsed[i] = true;
			if (dfs(-1, i)) {
				ans++;
			}
		}
	}

	cout << ans << endl;
}
