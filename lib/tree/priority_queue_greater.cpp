/* ABC062	D - 3N Numbers */
void Solve()
{
	int N;
	cin >> N;
	vector<int> a(3 * N);
	REP(i, 3 * N) cin >> a[i];

	// 前半は大きい優先
	vector<ll> fSum(N + 1, 0);
	priority_queue<int, vector<int>, greater<int>> fQue;
	for (int idx = 0; idx < N; idx++) {
		fQue.push(a[idx]);
		fSum[0] += a[idx];
	}
	for (int i = 0; i < N; i++) {
		int val = a[i + N];
		fQue.push(val);
		fSum[i + 1] += (fSum[i] + val - fQue.top());
		fQue.pop();
	}

	// 後半は小さい優先
	vector<ll> bSum(N + 1, 0);
	priority_queue<int> bQue;
	for (int idx = 2 * N; idx < 3 * N; idx++) {
		bQue.push(a[idx]);
		bSum[N] += a[idx];
	}
	for (int i = N - 1; i >= 0; i--) {
		int val = a[i + N];
		bQue.push(val);
		bSum[i] += (bSum[i + 1] + val - bQue.top());
		bQue.pop();
	}

	ll ans = fSum[0] - bSum[0];
	for (int i = 0; i < fSum.size(); i++) {
		ans = max(ans, fSum[i] - bSum[i]);
	}
	cout << ans << endl;
	return 0;
}

