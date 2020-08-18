ll N, M, Q;
vector<ll> a, b, c, d;
ll ans = 0;
void dfs(vector<ll> &A, int depth)
{
	if (depth == N) {
		ll ansOne = 0;
		REP(j, Q) {
			ll dif = A[b[j]] - A[a[j]];
			if (dif == c[j]) {
				ansOne += d[j];
			}
		}
		if (ans < ansOne) {
			ans = ansOne;
		}
		return;
	}
	
	REP(i, M) {
		A[depth] = i + 1;
		if (0 < depth) {
			if (A[depth - 1] <= A[depth]) {
				dfs(A, depth + 1);
			}
		} else {
			dfs(A, depth + 1);
		}
	}
}

int main()
{
	cin >> N >> M >> Q;
	a.resize(Q), b.resize(Q), c.resize(Q), d.resize(Q);
	REP(i, Q) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		a[i]--; b[i]--;
	}

	vector<ll> A(N);
	dfs(A, 0);

	cout << ans << endl;
	return 0;
}
