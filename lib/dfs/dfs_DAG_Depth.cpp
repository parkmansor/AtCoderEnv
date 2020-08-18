vector<vector<int>>	G;
vector<bool>		isVisited;
vector<int>			depth;
int dfs(int from, int to)
{
	if (isVisited[to]) {
		return depth[to];
	}

	int depthRes = 1;
	isVisited[to] = true;
	for (auto nextTo : G[to]) {
		if (from != nextTo) {
			int depthOne = dfs(to, nextTo);
			if (depthOne == -1) {
				// 閉路あり
				return -1;
			}
			depthRes = max(depthOne + 1, depthRes);
		}
	}

	depth[to] = depthRes;
	return depthRes;
}

int main()
{
	int N;
	cin >> N;

	vector<vector<int>> A(N, vector<int>(N - 1));
	REP(i, N) {
		REP(j, N - 1) {
			cin >> A[i][j];
			A[i][j]--;
		}
	}

	int id = 0;
	vector<vector<int>> path(N, vector<int>(N, -1));
	REP(from, N) {
		REP(to, N) {
			if (from != to) {
				if (path[from][to] == -1) {
					path[from][to] = id;
					path[to][from] = id;
					id++;
				}
			}
		}
	}

	int totalV = N * (N - 1) / 2;
	G.resize(totalV);
	REP(from, N) {
		REP(j, N - 2) {
			int prev = path[from][A[from][j]];
			int next = path[from][A[from][j + 1]];
			G[prev].emplace_back(next);
		}
	}

	int ans = 0;
	isVisited.resize(totalV, false);
	depth.resize(totalV, -1);
	REP(i, totalV) {
		int ansOne = dfs(-1, i);
		if (ansOne == -1) {
			ans = -1;
			break;
		} else {
			ans = max(ans, ansOne);
		}
	}

	cout << ans << endl;
	return 0;
}
