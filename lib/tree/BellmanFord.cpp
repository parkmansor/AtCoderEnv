// 枝定義
struct Edge
{
	int	from;
	int	to;
	ll	dist;
	Edge(){}
	Edge(int from, int to, ll dist) : from(from), to(to), dist(dist){}
};

// ベルマンフォード
struct BellmanFord
{
	// res[i] = sからiまでの最短距離
	vector<ll> dist;
	vector<Edge> edgeList;
	bool update;
	int nodeMax;
	const ll inf = 1e14;

	// 各節の最短経路を算出
	BellmanFord(int argNodeMax, const vector<Edge> &argEdgeList, int startPos)
	{
		nodeMax = argNodeMax;
		edgeList = argEdgeList;
		dist = vector<ll>(nodeMax, inf);
		dist[startPos] = 0;

		for (int i = 0; i < nodeMax; i++) {
			update = false;
			for (Edge edge : edgeList) {
				ll nextDist = dist[edge.from] + edge.dist;
				if (dist[edge.to] > nextDist) {
					dist[edge.to] = nextDist;
					update = true;
				}
			}
			if (!update) {
				break;
			}
		}
	}

	// まだ更新が可能かどうか
	bool isNegative(int nodeNo)
	{
		vector<ll> distTmp(nodeMax, inf);
		distTmp = dist;
		vector<bool> negativeList(nodeMax, false);
		for (int i = 0; i < nodeMax; i++) {
			update = false;
			for (Edge edge : edgeList) {
				if (distTmp[edge.from] != inf) {
					ll nextDist = distTmp[edge.from] + edge.dist;
					if (distTmp[edge.to] > nextDist) {
						distTmp[edge.to] = nextDist;
						negativeList[edge.to] = true;
						update = true;
					}
				}
			}
			if (!update) {
				break;
			}
		}

		return negativeList[nodeNo];
	}
};

void Solve()
{
	ll N, M;
	cin >> N >> M;

	vector<Edge> edgeList;
	REP(i, M) {
		ll a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		c = c * (-1);
		edgeList.emplace_back(Edge(a, b, c));
	}

	BellmanFord res(N, edgeList, 0);
	if (res.isNegative(N - 1)) {
		cout << "inf" << endl;
	} else {
		cout << res.dist[N - 1] * (-1) << endl;
	}
}
