#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<iomanip>
#include<queue>
#include<ciso646>
#include<random>
#include<map>
#include<set>
#include<complex>
#include<bitset>
#include<stack>
#include<unordered_map>
#include<utility>
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
typedef unsigned int ui;
const ll mod = 1000000007;
typedef double ld;
typedef complex<ld> Point;
const ll INF = mod * mod;
typedef pair<int, int> P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
const ld eps = 1e-8;
const ld pi = acos(-1.0);
typedef pair<ld, ld> LDP;
typedef pair<ll, ll> LP;
#define fr first
#define sc second

struct bigint {
	string s;
	bigint() {};
	bigint(ll n) { s = to_string(n); };
	bigint(string t) { s = t; };
};
bool operator==(const bigint &a, const bigint &b) { return a.s == b.s; };
bool operator==(const bigint &a, const int &b) { return a.s == to_string(b); };
bool operator!=(const bigint &a, const bigint &b) { return !(a == b); };
bool operator!=(const bigint &a, const int &b) { return a != to_string(b); };
bool operator<(const bigint &a, const bigint &b) {
	if (a.s.length() != b.s.length())return a.s.length() < b.s.length();
	return a.s < b.s;
}
bool operator>(const bigint &a, const bigint &b) {
	if (a.s.length() != b.s.length())return a.s.length() > b.s.length();
	return a.s > b.s;
}
bool operator>=(const bigint &a, const bigint &b) {
	return !(a < b);
}
bool operator<=(const bigint &a, const bigint &b) {
	return !(a > b);
}
bigint operator+(const bigint &a, const bigint &b) {
	int len = max(a.s.length(), b.s.length());
	bigint ret; bool f = false;
	rep(i, len) {
		int c = 0;
		if (f)c = 1, f = false;
		int j = a.s.length() - 1 - i;
		if (j >= 0)c += a.s[j] - '0';
		j = b.s.length() - 1 - i;
		if (j >= 0)c += b.s[j] - '0';
		if (c >= 10)f = true, c -= 10;
		ret.s.push_back('0' + c);
	}
	if (f)ret.s.push_back('1');
	reverse(ret.s.begin(), ret.s.end()); return ret;
}
bigint operator+(const bigint &a, const int b) {
	return a + bigint(b);
}
bigint operator-(const bigint &a, const bigint &b) {
	int len = max(a.s.length(), b.s.length());
	bigint ret; bool f = false;
	rep(i, len) {
		int c = 0;
		if (f)c = -1, f = false;
		int j = a.s.length() - 1 - i;
		if (j >= 0)c += a.s[j] - '0';
		j = b.s.length() - 1 - i;
		if (j >= 0)c -= b.s[j] - '0';
		if (c < 0)f = true, c += 10;
		ret.s.push_back('0' + c);
	}
	while (ret.s.size() > 1 && ret.s.back() == '0')ret.s.pop_back();
	reverse(ret.s.begin(), ret.s.end());
	return ret;
}
bigint operator/(const bigint &a, const bigint &b) {
	bigint ret(0);
	bigint ans;
	int len = a.s.length();
	rep(i, len) {
		ret = ret + (a.s[i] - '0');
		int cnt = 0;
		while (ret >= b)++cnt, ret = ret - b;
		ans.s.push_back('0' + cnt);
		if (ret != 0)ret.s.push_back('0');
	}
	rep(i, ans.s.length()) {
		if (ans.s[i] != '0') {
			ans.s.erase(ans.s.begin(), ans.s.begin() + i);
			break;
		}
		if (i == (int)ans.s.length() - 1) {
			ans = 0;
		}
	}
	return ans;
}
bigint operator%(const bigint &a, const bigint &b) {
	bigint ret(0);
	int len = a.s.length();
	rep(i, len) {
		ret = ret + (a.s[i] - '0');
		while (ret >= b)ret = ret - b;
		if (ret != 0 && i < len - 1)ret.s.push_back((0));
	}
	return ret;
}
bigint min(const bigint &a, const bigint &b) {
	if (a < b)return a;
	else return b;
}

bigint dp[320];
void solve() {
	int k; string s; cin >> k >> s; k++;
	int n = s.length();
	int d = n / k, r = n % k;
	if (r == 0) {
		bigint ans = 0;
		rep(i, k) {
			bigint u = s.substr(i*d, d);
			ans = max(ans, u);
		}
		cout << ans.s << endl; return;
	}
	if (d < 320) {
		bigint le, ri; le = ri = 1;
		rep(i, d)le.s.push_back('0');
		rep(i, d + 1)ri.s.push_back('0');
		while (ri - le > 1) {
			bigint mid = (le + ri) / 2;
			//cout << mid.s << endl;
			int cur = 0, num = 0;
			rep(i, k) {
				bigint x = s.substr(cur, d + 1);
				if (x < mid) {
					cur += d + 1; num++;
					if (num == r)break;
				}
				else cur += d;
			}
			if (num == r)ri = mid;
			else le = mid;
		}
		cout << le.s << endl;
	}
	else {
		fill(dp, dp + k + 1, s);
		dp[0] = 0;
		rep(i, k) {
			per(j, r) {
				bigint x = s.substr(i*d + j, d + 1);
				dp[j + 1] = min(dp[j + 1], max(dp[j], x));
				x.s.pop_back();
				dp[j] = max(dp[j], x);
			}
		}
		cout << dp[r].s << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}