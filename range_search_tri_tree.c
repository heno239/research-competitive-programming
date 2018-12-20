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
typedef unsigned int ui;
const ll mod = 1000000007;
const ll INF = (ll)1000000007 * 1000000007;
typedef pair<int, int> P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
//#define revstr(s) reverse(s.begin(),s.end())
typedef long double ld;
typedef complex<ld> Point;
const ld eps = 1e-11;
const ld pi = acos(-1.0);
typedef pair<ll, ll> LP;
typedef pair<ld, ld> LDP;
typedef unsigned long long ul;

//����a���������Ƃ��A��b,l,r�ɑ΂��āAmin{a[i]^b}(l<=i<r)��Ԃ����Ƃ̂ł���tri��

//bit�̍ő吔(a[i]<2^30�Ȃ�30)
const int digits = 30;
struct Node {
	//�q
	Node *lch, *rch;
	//����Node��ʂ����ЂƂ���
	vector<int> ids;
	//������
	Node() : lch(NULL), rch(NULL) {}
};
Node* nd;
//tri�؂ɗv�f��ǉ�
void add(Node* node, const int &s, int id) {
	per(i, digits) {
		int d = (1 << i);
		if (d&s) {
			if (node->rch == NULL)node->rch = new Node();
			node = node->rch;
		}
		else {
			if (node->lch == NULL)node->lch = new Node();
			node = node->lch;
		}
		node->ids.push_back(id);
	}
}
//����a�ŏ�����
void init(vector<int> a) {
	nd = new Node();
	rep(i, a.size()) {
		add(nd, a[i], i);
	}
}
//le<=i<ri���݂���i�����Ȃ��Ƃ�1���݂�Node��ʂ��Ă��邩�ǂ����̔���
bool in(Node* node, int le, int ri) {
	if (node == NULL)return false;
	int id = lower_bound(node->ids.begin(), node->ids.end(), le) - node->ids.begin();
	if (id == node->ids.size())return false;
	if (node->ids[id] >= ri)return false;
	return true;
}
//query����
//min{a[i]^b}(le<=i<ri)�����߂�
int dfs(Node* node, int b, int le, int ri) {
	int res = 0;
	per(i, digits) {
		int d = (1 << i);
		if (b&d) {
			//�ŏ��l��
			if (in(node->rch, le, ri)) {
				node = node->rch;
			}
			else {
				res += d;
				node = node->lch;
			}
			//�ő�l��
			/*
			if (in(node->lch, le, ri)) {
			res += d;
			node = node->lch;
			}
			else {
			node = node->rch;
			}
			*/
		}
		else {
			//�ŏ��l��
			if (in(node->lch, le, ri)) {
				node = node->lch;
			}
			else {
				res += d;
				node = node->rch;
			}
			//�ő�l��
			/*
			if (in(node->rch, le, ri)) {
			res += d;
			node = node->rch;
			}
			else {
			node = node->lch;
			}
			*/
		}
	}
	return res;
}
int main() {
	vector<int> a = { 1,2,4,5 };
	init(a);
	cout << dfs(nd, 7, 0, 4) << endl;//output:2
	cout << dfs(nd, 7, 0, 3) << endl;//output:3
	return 0;
}