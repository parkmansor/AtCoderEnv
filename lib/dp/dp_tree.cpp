template <class E>
using Graph = vector<vector<E>>;

// dfs
const int black = 1;
const int white = 0;
Graph<int>	G;
void dfs(int from, int to, vector<vector<ll>> &dp)
{
	ll bCnt = 1;
	ll wCnt = 1;
	for (auto nextTo : G[to]) {
		if (nextTo != from) {
			dfs(to, nextTo, dp);
			bCnt *= dp[nextTo][white]; 
			bCnt %= MOD;
			wCnt *= (dp[nextTo][white] + dp[nextTo][black]);
			wCnt %= MOD;
		}
	}
	dp[to][black] = bCnt; 
	dp[to][white] = wCnt;
}

// メイン
int main()
{
	ll N;
	cin >> N;
	G.resize(N);
	REP(i, N - 1) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}

	vector<vector<ll>> dp(N, vector<ll>(2, 0));
	dfs(-1, 0, dp);
	cout << (dp[0][black] + dp[0][white]) % MOD << endl;
	return 0;
}
