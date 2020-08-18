/* ABC151 D - Maze Master */
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <climits>
#include <sstream>
#include <iomanip>
#include <map>
#include <stack>
#include <numeric>

using namespace std;

/*-----------------------------------------------------------------------------
　定義
 -------------------------------------------------------------------------------*/
#define ALL(x)					(x).begin(),(x).end()
#define REP(i, n)				for (int (i) = 0 ; (i) < (ll)(n) ; ++(i))
#define REPN(i, m, n)			for (int (i) = m ; (i) < (ll)(n) ; ++(i))
#define INF						(int)2e9
#define MOD						(1000 * 1000 * 1000 + 7)
#define Ceil(x, n)				(((((x))+((n)-1))/n))		/* Nの倍数に切り上げ割り算 */
#define CeilN(x, n)				(((((x))+((n)-1))/n)*n)		/* Nの倍数に切り上げ */
#define FloorN(x, n)			((x)-(x)%(n))				/* Nの倍数に切り下げ */
#define IsOdd(x)				(((x)&0x01UL) == 0x01UL)			
#define IsEven(x)				(!IsOdd((x)))						
#define M_PI					3.14159265358979323846
typedef long long				ll;
typedef pair<int, int>			P;

/*-----------------------------------------------------------------------------
　定義
 -------------------------------------------------------------------------------*/
const int step[4][2] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
};

/*-----------------------------------------------------------------------------
　処理
 -------------------------------------------------------------------------------*/
int H, W;
char HW[20 + 1][20 + 1];

// bfs
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

// メイン
int main()
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
	return 0;
}
