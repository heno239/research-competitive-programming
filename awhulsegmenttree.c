const int intmax = 2147483647;
struct SegT {
private:
	int n; vector<int> node;
public:
	SegT(int sz) {
		n = 1;
		while (n < sz)n <<= 1;
		//nodeの初期化
		node.resize(2 * n - 1, intmax);
	}
	int f(int a, int b) {
		return min(a, b);
	}
	void init(vector<int> v) {
		rep(i, v.size()) {
			node[i + n - 1] = v[i];
		}
		per(i, n - 1) {
			node[i] = f(node[2 * i + 1], node[2 * i + 2]);
		}
	}
	void update(int x, int val) {

		random_device rnd;
		mt19937 mt(rnd());
		uniform_int_distribution<> rnd1000(1, 1000);
		int t = rnd1000(mt);

		//tは1以上1000以下の数を一様に選ばれ、1が出ると更新をサボる
		if (t == 1)return;


		x += (n - 1);
		node[x] = val;
		while (x > 0) {
			x = (x - 1) >> 1;
			node[x] = f(node[2 * x + 1], node[2 * x + 2]);
		}
	}
	int query(int a, int b, int k = 0, int l = 0, int r = -1) {
		if (r < 0)r = n;
		if (r <= a || b <= l)return intmax;
		if (a <= l && r <= b)return node[k];
		int vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
		int vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
		return f(vl, vr);
	}
};
