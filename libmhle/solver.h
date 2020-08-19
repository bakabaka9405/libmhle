#pragma once
#include<vector>
#include<stdexcept>
namespace mhle {
	class solver {
	public:
		solver() = delete;
		solver(int num);
		solver(const solver&) = delete;

		void add_equations(const std::initializer_list<int>&
						   equations);
		void add_equations(std::vector<int>::const_iterator begin,
						   std::vector<int>::const_iterator end);
		void solve(std::vector<int>& answer);
	private:
		std::vector<std::vector<int> > m_equations;
		int m_num;
	};
}