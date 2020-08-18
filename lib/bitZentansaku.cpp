void Solve()
{
	ll N, M, X;
	cin >> N >> M >> X;
	
	vector<ll> C(N);
	vector<vector<ll>> A(N, vector<ll>(M));
	REP(i, N) {
		cin >> C[i];
		REP(j, M) cin >> A[i][j];
	}
 
	ll ans = INF;
	ll bitMax = (ll)1 << N;
	REP(bitPtn, bitMax) {
		ll ansOne = 0;
		vector<ll> aSum(M, 0);
		REP(j, N) {
			if (bitPtn & (ll)1 << j) {
				ansOne += C[j];
				REP(k, M) {
					aSum[k] += A[j][k];				
				}
			}
		}
 
		bool isOk = true;
		for (auto one : aSum) {
			if (one < X) {
				isOk = false;
				break;
			}
		}
 
		if (isOk) {
			chmin(ans, ansOne);		
		}
	}
	
	if (ans == INF) ans = -1;
	cout << ans << endl;
}
 
