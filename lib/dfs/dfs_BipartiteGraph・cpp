// 枝定義
struct Edge
{
	int	to;
	ll	dist;
	Edge(){}
	Edge(int to, ll dist) : to(to), dist(dist){}
};

template <class E>
using Graph = vector<vector<E>>;

// dfs
Graph<Edge>		G;
vector<int>		color;
bool dfs(int from, int fromCol)
{
	color[from] = fromCol;
	for (auto next : G[from]) {
		if (color[next.to] == 0) {
			if (!dfs(next.to, fromCol * (-1))) {
				return false;
			}
		} else if (color[next.to] == fromCol) {
			return false;
		} else {
			// すでに塗ってる
		}
	}

	return true;
}

// メイン
int main()
{
	ll N, M;
	cin >> N >> M;
	G.resize(N);
	color.resize(N, 0);
	REP(i, M) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[a].emplace_back(Edge(b, 1));
		G[b].emplace_back(Edge(a, 1));
	}

	ll ans;
	if (dfs(0, 1)) {
		ll white = 0;
		ll block = 0;
		REP(i, N) {
			if (color[i] == 1) {
				white++;
			} else {
				block++;
			}
		}
		ans = white * block - M;
	} else {
		ans = N * (N - 1) / 2 - M;
	}

	cout << ans << endl;
	return 0;
}
