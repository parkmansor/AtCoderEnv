int main()
{
	int N, M;
	cin >> N >> M;

	vector<int> a(M), b(M);
	vector<vector<int>> c(M);
	REP(i, M) {
		cin >> a[i] >> b[i];
		REP(j, b[i]) {
			int tmp; 
			cin >> tmp;
			tmp--;
			c[i].emplace_back(tmp);
		}
	}

	int bitMax = 1 << N;
	vector<vector<int>> dp(M + 1, vector<int>(bitMax, INF));
	dp[0][0] = 0;
	REP(i, M) {
		int bitPtn = 0;
		for (auto one : c[i]) {
			bitPtn |= (0x1 << one);
		}

		REP(j, bitMax) {
			if (dp[i][j] != INF) {
				int nextBitPtn = j | bitPtn;
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
				dp[i + 1][nextBitPtn] = min(dp[i + 1][nextBitPtn], dp[i][j] + a[i]);
			}
		}
	}

	if (dp[M][bitMax - 1] == INF) {
		cout << -1 << endl;
	} else {
		cout << dp[M][bitMax - 1] << endl;
	}
	return 0;
}
