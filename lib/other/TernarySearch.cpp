void Solve()
{
	double P;
	cin >> P;

	auto calc = [&](double year) {
		double speed = pow(2, (year / 1.5));
		double totalYear = year + P / speed;
		return totalYear;
	};

	double lb = 0;
	double lu = 92;
	REP(i, 121) {
		double c1 = (lb * 2 + lu) / 3;
		double c2 = (lb + lu * 2) / 3;
		double val1 = calc(c1);
		double val2 = calc(c2);
		if (val1 <= val2) {
			lu = c2;
		} else {
			lb = c1;
		}
	}

	cout << calc(lu) << endl;
}
