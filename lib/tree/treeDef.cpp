/* 枝定義　*/
typedef struct edge {
	DWORD	to;
	QWORD	cost;

	edge() : to(0), cost(0) {}
	edge(DWORD argTo, QWORD argCost) : to(argTo), cost(argCost) {}

	bool operator > (const edge& e) const {
		return cost > e.cost;
	}
} EDGE;
