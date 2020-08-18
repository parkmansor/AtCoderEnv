int H, W;
char HW[500 + 1][500 + 1];

// dfs
bool dfs(int iArg, int jArg)
{
	const int step[4][2] = {
		{1, 0},
		{-1, 0},
		{0, 1},
		{0, -1},
	};

	// 一度きたところはもう来ない
	HW[iArg][jArg] = '#';

	// 4方向へ進む
	REP (cnt, 4) {
		int iNext = iArg + step[cnt][0];
		int jNext = jArg + step[cnt][1];
		if (!((0 <= iNext && iNext < H) && (0 <= jNext && jNext < W))) {
			continue;
		}

		if (HW[iNext][jNext] == 'g') {
			return true;
		} else if (HW[iNext][jNext] == '.') {
			if (dfs(iNext, jNext)) {
				return true;
			}
		} else {
			// '#'
		}
	}

	return false;
}

// メイン
void Solve()
{
	// 入力
	cin >> H >> W;
	REP(i, H) REP(j, W) cin >> HW[i][j];

	// dfs
	string ans = "No";
	REP(i, H) {
		REP(j, W) {
			if (HW[i][j] == 's') {
				if (dfs(i, j)) {
					ans = "Yes";
					break;
				}
			}
		}
	}

	// 結果
	cout << ans << endl;
}
