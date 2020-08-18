int N, K;
bool compExec(vector<pair<double, double>> &param, double rate)
{
	vector<double> val(param.size());
	REP(i, param.size()) {
		auto &paramOne = param[i];
		val[i] = paramOne.second - paramOne.first * rate / 100;
 	}
	sort(val.rbegin(), val.rend());
	double ans = 0;
	REP(i, K) {
		ans += val[i];
	}
	return (0 <= ans);
}

void Solve()
{
	cin >> N >> K;
	vector<pair<double, double>> param(N);
	REP(i, N) {
		cin >> param[i].first >> param[i].second;
		param[i].second = param[i].first * param[i].second / 100;
	}

	double lb = 0;
	double lu = 100;
	double mid = 0;
	REP(i, 121) {
		mid = (lb + lu) / 2;
		if (compExec(param, mid)) {
			lb = mid;
		} else {
			lu = mid;
		}
	}

	cout << setprecision(10) << mid << endl; 
	return 0;
}
