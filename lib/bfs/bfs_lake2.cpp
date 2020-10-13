const int step[4][2] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
};

// bfs
int H, W;
char HW[20 + 1][20 + 1];
int bfs(int sx, int sy)
{
	vector<vector<int>> dist(H, vector<int>(W, INF));

	// 開始位置で初期化
	queue<P> que;
	que.push(P{sx, sy});
	dist[sx][sy] = 0;

	// 全てへの距離
	while (que.size()) {
		P now = que.front();
		que.pop();
		// if ((now.first == gx)&&(now.second == gy)) {
		// 	break;
		// }
		for (int i = 0; i < 4; i++) {
			int xNext = now.first + step[i][0];
			int yNext = now.second + step[i][1];
			if (!((0 <= xNext && xNext < H) && (0 <= yNext && yNext < W))) {
				continue;
			}
			char nextPos = HW[xNext][yNext];
			if ((dist[xNext][yNext] == INF) && (HW[xNext][yNext] != '#')) {
				dist[xNext][yNext] = dist[now.first][now.second] + 1;
				que.push(P{xNext, yNext});
			}
		}
	}

	// 一番遠い距離
	int res = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (dist[i][j] != INF) {
				res = max(res, dist[i][j]);
			}
		}
	}

	return res;
}

void Solve()
{
	// 入力
	cin >> H >> W;
	REP(i, H) REP(j, W) cin >> HW[i][j];

	// dfs
	int ans = 0;
	REP(i, H) {
		REP(j, W) {
			if (HW[i][j] == '.') {
				int res = bfs(i, j);
				if (res != INF) {
					ans = max(ans, res);
				}
			}
		}
	}

	// 結果
	cout << ans << endl;
}
