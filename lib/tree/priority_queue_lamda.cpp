void Solve()
{
	// 入力
	ll N, K;
	cin >> N >> K;
	
	auto compare = [](Param a, Param b) {return a.time > b.time; };
	priority_queue<ll, vector<Param>, decltype(compare)> que{compare};
	REP(i, N) {
		Param param;
		cin >> param.a >> param.b;
		param.time = param.a;
		que.push(param);
	};
	
	ll ans = 0;
	REP(i, K) {
		Param one = que.top();
		que.pop();
		ans += one.time;
		one.time += one.b;
		que.push(one);
	}
	cout << ans << endl;
	return 0;
}

