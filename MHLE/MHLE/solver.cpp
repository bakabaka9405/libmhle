#include "solver.h"
namespace mhle {
	int gcd(const int& a, const int& b) {
		return b ? gcd(b, a % b) : a;
	}

	int lcm(const int& a, const int& b) {
		return a * b / gcd(a, b);
	}

	mhle::solver::solver(int num) :
		equations(),
		m_num(num)
	{
	}
	void solver::add_equation(const std::vector<int>& equation)
	{
		//数量不等于未知数的数量+1，杀掉
		if (equation.size() != m_num + 1) {
			throw std::runtime_error("方程不完整");
			return;
		}

		int i = 0;		//遍历下标
		int tmp = 0;	//最大公因数

		//找到第一个不为0的数，把它赋给tmp
		//防止tmp得到0导致后面炸开
		while (i < equation.size() && equation.at(i) == 0)++i;
		//如果跑到底还没找到一个非0数，吐槽一波
		if (i == equation.size()) {
			throw std::runtime_error("这是哪个睿智写的全0方程");
			return;
		}
		tmp = equation.at(i);

		//跑到底，逐个缩小最大公因数
		while (i < equation.size() && tmp != 1)
			if (equation.at(i))
				tmp = gcd(tmp, equation.at(i));

		equations.push_back(equation);
		//一个一个除
		if (tmp != 1)for (auto& i : equations.back())if (i)i /= tmp;
	}
	void solvex(std::vector<std::vector<int> > equations) {

	}
	void solver::solve(std::vector<int>& answer)
	{
		
	}
}
