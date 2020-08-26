#include "bits/stdc++.h"
using namespace std;

// ’è‹`
typedef long long         ll;
typedef pair<ll, ll>      P;
#define ALL(x)            (x).begin(),(x).end()
#define REP(i, n)         for(ll i = 0 ; i < (ll)n ; ++i)
#define REPN(i, m, n)     for(ll i = m ; i < (ll)n ; ++i)
#define REVREP(i, n)      for(ll i = n - 1; i >= 0 ; i--)
#define VL                vector<ll>
#define VVL               vector<vector<ll>>
#define VVVL              vector<vector<vector<ll>>>
#define VC                vector<char>
#define VVC               vector<vector<char>>
#define INF               (ll)2e9
#define INF_LL            1LL<<60
//#define MOD             998244353
#define MOD               1000000007

ll Ceil(ll val, ll div)   { return (val + div - 1) / div; }
ll CeilN(ll val, ll div)  { return Ceil(val, div) * div; }
ll FloorN(ll x, ll n)     { return (x - x % n); }
bool IsOdd(ll x)          { return ((x & 1) == 1); }
bool IsEven(ll x)         { return ((x & 1) == 0); }
template<class T> bool chmax(T& a, T b) { if (a <= b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, T b) { if (a >= b) { a = b; return 1; } return 0; }

const int step[4][2] = {
	{ 1, 0 },
	{ -1, 0 },
	{ 0, 1 },
	{ 0, -1 },
};

int H, W;
char HW[1000 + 1][1000 + 1];
char magicAll[1000 + 1][1000 + 1];
ll DH, DW;

// bfs
int bfs(int sx, int sy)
{
	vector<vector<ll>> dist(H, vector<ll>(W, INF));
	deque<P> que;
	
	dist[sx][sy] = 0;
	que.emplace_front(sx, sy);
	while (que.size()) {
		ll xNow = que.front().first;
		ll yNow = que.front().second;
		que.pop_front();
		for (int i = 0; i < 4; i++) {
			int xNext = xNow + step[i][0];
			int yNext = yNow + step[i][1];
			if (!((0 <= xNext && xNext < H) && (0 <= yNext && yNext < W))) {
				continue;
			}
			if ((dist[xNow][yNow] < dist[xNext][yNext] && HW[xNext][yNext] == '.')) {
				dist[xNext][yNext] = dist[xNow][yNow];
				que.emplace_front(xNext, yNext);
			}
		}

		for (int h = -2; h <= 2; h++) {
			for (int w = -2; w <= 2; w++) {
				int xNext = xNow + h;
				int yNext = yNow + w;
				if (!((0 <= xNext && xNext < H) && (0 <= yNext && yNext < W))) {
					continue;
				}
				if ((dist[xNow][yNow] + 1 < dist[xNext][yNext] && HW[xNext][yNext] == '.')) {
					dist[xNext][yNext] = dist[xNow][yNow] + 1;
					que.emplace_back(xNext, yNext);
				}
			}
		}
	}
	
	if (dist[DH][DW] != INF) {
		return dist[DH][DW];
	} else {
		return -1;
	}
}

// ƒƒCƒ“
void Solve()
{
	// “ü—Í
	ll CH, CW;
	cin >> H >> W;
	cin >> CH >> CW;
	cin >> DH >> DW;
	CH--; CW--; DH--; DW--;
	REP(i, H) {
		REP(j, W) {
			cin >> HW[i][j];
			magicAll[i][j] = 'W';
		}
	}

	// Œ‹‰Ê
	cout << bfs(CH, CW) << endl;

}

// ƒƒCƒ“
int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(15);
	Solve();
	return 0;
}
