void Solve()
{
	ll N;
	cin >> N;

	VL x(N), y(N), z(N);
	REP(i, N) cin >> x[i] >> y[i] >> z[i];

	VVL cost(N, VL(N));
	REP(i, N) {
		REP(j, N) {
			ll costOne = abs(x[i] - x[j]) + abs(y[i] - y[j]) + max((ll)0, (z[j] - z[i]));
			cost[i][j] = costOne;
		}
	}

	ll bitMax = (ll)1 << N;
	static ll dp[200000][20];
	REP(i, bitMax + 1) {
		REP(j, N + 1) {
			dp[i][j] = INF;
		}
	}

	dp[0][0] = 0;
	REP(bitCnt, bitMax) {
		REP(i, N) {
			ll nowCost = dp[bitCnt][i];
			if (nowCost == INF) continue;
			REP(j, N) {
				if (i == j) continue;
				ll bitPtn = (ll)1 << j;
				ll nextBitPtn = bitCnt | bitPtn;
				ll nextCost = nowCost + cost[i][j];
				dp[nextBitPtn][j] = min(dp[nextBitPtn][j], nextCost);
			}
		}
	}
	
	ll ans = dp[bitMax - 1][0];
	REP(j, N) {
		ll nextCost = dp[bitMax - 1][j] + cost[j][0];
		ans = min(ans, nextCost);
	}

	cout << ans << endl;
}
