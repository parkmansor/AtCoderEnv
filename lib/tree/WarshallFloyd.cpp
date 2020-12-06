
// 枝定義
struct Edge
{
	int from;
	int	to;
	ll	dist;
	Edge(){}
	Edge(int from, int to, ll dist) : from(from), to(to), dist(dist){}
};

// ワーシャルフロイド
class WarshallFloyd
{
public:
	// distList[i][j] = iからjまでの最短距離
	vector<vector<ll>> distList;
	const ll inf = 1e14;

public:
	WarshallFloyd(int nodeNum, const vector<Edge> &edgeList)
	{
		distList.resize(nodeNum, vector<ll>(nodeNum, inf));
		for (const auto &edgeOne : edgeList) {
			distList[edgeOne.from][edgeOne.to] = edgeOne.dist;
		}

		for (int nodeCnt = 0; nodeCnt < nodeNum; nodeCnt++) {
			for (int i = 0; i < nodeNum; i++) {
				for (int j = 0; j < nodeNum; j++) {
					distList[i][j] = min(distList[i][j], distList[i][nodeCnt] + distList[nodeCnt][j]);
				}
			}
		}
	}
};

void Solve()
{
	// 入力
	int N;
	cin >> N;

	vector<Edge> edgeList;
	REP(i, N) {
		string S;
		cin >> S;
		REP(j, N) {
			if (S[j] == '1') {
				edgeList.emplace_back(Edge(i, j, 1));
			}
		}
	}

	// ワーシャルフロイド
	WarshallFloyd res(N, edgeList);

	double ans = 0;
	REP(i, N) {
		double attacker = 0;
		REP(j, N) {
			if (i == j) continue;
			if (res.distList[j][i] != res.inf) {
				attacker++;
			}
		}
		ans += 1 / (attacker + 1);
	}

	cout << ans << endl;
}
