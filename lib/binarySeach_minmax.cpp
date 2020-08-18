void Solve()
{
	ll K;
	cin >> K;
	VL A(K);
	REP(i, K) cin >> A[i];

	auto compExec = [&](ll mid, ll limit) {
		for (auto a : A) {
			if (mid < a) {
				return false;
			}
			mid -= mid % a;	
		}
		return (limit <= mid);
	};

	ll lb = 0;
	ll lu = 1e14;
	ll mid = 0;
	while ((lb + 1) != lu) {
		mid = (lb + lu) / 2;
		if (!compExec(mid, 2)) {
			lb = mid;
		} else {
			lu = mid;
		}
	}
	ll ansMin = lu;
	for (auto a : A) {
		lu -= lu % a;
	}
	if (lu != 2) {
		cout << -1 << endl;
		return;
	}

	lb = 0;
	lu = 1e14;
	while ((lb + 1) != lu) {
		mid = (lb + lu) / 2;
		if (!compExec(mid, 3)) {
			lb = mid;
		} else {
			lu = mid;
		}
	}
	ll ansMax = lu - 1;

	cout << ansMin << " " << ansMax << endl;
}
