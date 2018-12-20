#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)

//sort���ꂽ����a���������Ƃ��A��b,l,r�ɑ΂��āAmin{a[i]^b}(l<=i<r)��Ԃ����Ƃ̂ł���tri��

//bit��
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
void add(Node* node, int x, int id) {
	per(i, digits) {
		int d = (1 << i);
		if (d&x) {
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
	sort(a.begin(), a.end());
	rep(i, a.size()) {
		add(nd, a[i], i);
	}
}
//le<=i<ri���݂���i�����Ȃ��Ƃ����݂�Node��ʂ��Ă��邩�̔���
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
			if (in(node->rch, le, ri)) {
				node = node->rch;
			}
			else {
				res += d;
				node = node->lch;
			}
		}
		else {
			if (in(node->lch, le, ri)) {
				node = node->lch;
			}
			else {
				res += d;
				node = node->rch;
			}
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