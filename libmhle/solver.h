#pragma once
#include<vector>
#include<stdexcept>
#include"func.h"
#include"fraction.h"
namespace mhle {
	class solver {
	public:
		solver() = delete;
		solver(int num);
		solver(const solver&) = delete;

		void add_equations(const std::initializer_list<fraction>&
						   equations);
		void add_equations(std::vector<fraction>::const_iterator begin,
						   std::vector<fraction>::const_iterator end);
		void solve(std::vector<fraction>& answer);
	private:
		std::vector<std::vector<fraction> > m_equations;
		int m_num;
	};
}