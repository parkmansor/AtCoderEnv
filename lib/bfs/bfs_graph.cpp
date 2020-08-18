
// 枝定義
struct Edge
{
	int	from;
	int	to;
	Edge(){}
	Edge(int a, int b) : from(a), to(b){}
};

// 処理
void Solve()
{
	int N;
	cin >> N;
	vector<Edge> edgeList;
	REP(i, N - 1) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		edgeList.emplace_back(a, b);
	}

	VL c(N);
	REP(i, N) cin >> c[i];
	sort(ALL(c), greater<ll>());

	vector<vector<int>>	G(N);
	for (auto one : edgeList) {
		G[one.from].emplace_back(one.to);
		G[one.to].emplace_back(one.from);
	}

	VL vAns(N, 0);
	ll idx = 0;
	ll ansAll = 0;
	vAns[0] = c[idx++];

	queue<ll> que;
	vector<bool> isUsed(N, false);
	que.push(0);
	isUsed[0] = true;
	while (!que.empty()) {
		ll next = que.front(); que.pop();
		for (auto nextTo : G[next]) {
			if (!isUsed[nextTo]) {
				isUsed[nextTo] = true;
				que.push(nextTo);
				vAns[nextTo] = c[idx];
				ansAll += c[idx];
				idx++;
			}
		}
	}

	cout << ansAll << endl;
	for(auto one : vAns) {
		cout << one << endl;
	}
}
