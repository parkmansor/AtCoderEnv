// 枝定義
struct Edge
{
	ll	to;
	ll	dist;
	Edge(){}
	Edge(int to, ll dist) : to(to), dist(dist){}
};
 
// グラフ定義(二次元配列)
template <class E>
using Graph = vector<vector<E>>;
 
// ダイクストラ
class Dijkstra
{
public:
	// res[i] = sからiまでの最短距離
	vector<ll> res;
 
	// 復元パス
	//	vector<int> pathList;
 
	vector<ll> pathRev;
	const ll inf = 1e15;
 
public:
	template<class E>
	Dijkstra(const Graph<E> &G, int startFrom)
	{
		int V = (int)G.size();
		res = vector<ll>(V, inf);
		pathRev.resize(V, -1);
 
		using P = pair<ll, int>;
		priority_queue<P, vector<P>, greater<P>> que;
		que.push(P(0, startFrom));
		res[startFrom] = 0;
 
		while (!que.empty()) {
			P p = que.top(); que.pop();
			int egdeFrom = p.second;
 
			// 違う最短距離がキューにあるのでスキップ
			if (res[egdeFrom] < p.first) {
				continue;
			}
 
			// 最短距離を更新
			for (E edge : G[egdeFrom]) {
				ll nextDist = p.first + edge.dist;
				if (nextDist < res[edge.to]) {
					res[edge.to] = nextDist;
					pathRev[edge.to] = egdeFrom;
					que.push(P(nextDist, edge.to));
				}
			}
		}
	}
 
	// 経路を取得する
	vector<ll> getPath(ll dstPos)
	{
		vector<ll> pathList;
 
		while (dstPos != -1) {
			pathList.push_back(dstPos);
			dstPos = pathRev[dstPos];
		}
		reverse(pathList.begin(), pathList.end());
		return pathList;
	}
};
 
// 処理
void Solve()
{
	int N, M;
	cin >> N >> M;
	Graph<Edge>	G(N);
	REP(i, M) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[a].emplace_back(Edge(b, 1));
		G[b].emplace_back(Edge(a, 1));
	}
 
	Dijkstra dijk(G, 0);
	if (0 ==  count_if(ALL(dijk.res), [](ll one ){ return one == INF;})) {
		cout << "Yes" << endl;
		REPN(i, 1, N) {
			cout << dijk.pathRev[i] + 1 << endl;
		}
	} else {
		cout << "No" << endl;
	}
}
 
