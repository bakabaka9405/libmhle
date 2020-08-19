#include<iostream>
#include"../libmhle/solver.h"
using namespace std;
int main() {
	int num,a;
	vector<int> vec, ans;
	cout << "请输入方程未知数的数量：";
	cin >> num;
	mhle::solver solver(num);
	for (int i = 1; i <= num; i++) {
		cout << "请输入第 " << i << " 个方程（格式：若未知数数量为3，2a-b=1 => 2 -1 0 1）：" << endl;
		vec.clear();
		for (int i = 0; i < num + 1; i++) {
			cin >> a;
			vec.push_back(a);
		}
		solver.add_equations(vec.begin(), vec.end());
	}
	solver.solve(ans);
	cout << "方程的解为：";
	for (auto& i : ans)cout << i << " ";
	cout << endl;
	cin.get();
	return 0;
}