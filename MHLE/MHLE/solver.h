#pragma once
#include<vector>
#include<stdexcept>
namespace mhle {
	class solver {
	public:
		solver() = delete;
		solver(int num);
		solver(const solver&) = delete;
		void add_equation(const std::vector<int>& equation);
		void solve(std::vector<int>& answer);
	private:
		std::vector<std::vector<int> > equations;
		int m_num;
	};
}