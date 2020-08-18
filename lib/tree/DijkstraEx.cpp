// 枝定義
struct Edge
{
	ll to;
	ll cost;
	Edge(){}
	Edge(ll to, ll cost) : to(to), cost(cost){}
};

struct queParam
{
	ll v;
	ll cost;
	ll status;
	queParam(ll v, ll cost, ll status) : v(v), cost(cost), status(status){}
	bool operator<(const queParam &a) const {
		return cost > a.cost;
	}
};

// グラフ定義(二次元配列)
template <class E>
using Graph = vector<vector<E>>;

// 拡張ダイクストラ
class ExDijkstra
{
private:
	const ll statusNum = 3;

public:
	// res[i] = sからiまでの最短距離
	const ll InfVal = 1e18;
	vector<vector<ll>> res;

public:
	ExDijkstra(const Graph<Edge> &G, int startPos, ll initStatus)
	{
		int V = (int)G.size();
		res = vector<vector<ll>>(V, vector<ll>(statusNum, InfVal));

		priority_queue<queParam> que;
		que.emplace(startPos, 0, initStatus);
		res[startPos][initStatus] = 0;
		
		while (!que.empty()) {
			queParam qOne = que.top(); que.pop();

			// 違う最短距離がキューにあるのでスキップ
			if (res[qOne.v][qOne.status] < qOne.cost) {
				continue;
			}

			// 最短距離を更新
			for (Edge e : G[qOne.v]) {
				ll nextStatus = (qOne.status + 1) % 3;
				ll &nowCost = res[e.to][nextStatus];
				ll newCost = res[qOne.v][qOne.status] + e.cost;
				if (nowCost > newCost) {
					nowCost = newCost;
					que.emplace(e.to, newCost, nextStatus);
				}
			}
		}
	}
};

void Solve()
{
	int N, M;
	cin >> N >> M;
	Graph<Edge>	G(N);
	REP(i, M) {
		ll u, v;
		cin >> u >> v;
		u--, v--;
		G[u].emplace_back(Edge(v, 1));
	}

	int S, T;
	cin >> S >> T;
	S--; T--;

	ExDijkstra dijk(G, S, 0);

	ll ans = -1;
	if (dijk.res[T][0] != dijk.InfVal) {
		ans = dijk.res[T][0] / 3;
	}
	cout << ans << endl;
	return 0;
}
