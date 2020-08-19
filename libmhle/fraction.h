#pragma once
#include<iostream>
#include<string>
#include<stdexcept>
#include<stdio.h>
#include<string.h>
#include"func.h"
namespace mhle {
	class fraction {
	public:
		fraction();
		fraction(const fraction& f);
		explicit fraction(unsigned integer,
						  unsigned decimal = 0,
						  bool negative = 0);
		explicit fraction(const char* str);
		explicit fraction(const std::string& str);

		const std::string to_string() const noexcept;
		const int to_int() const noexcept;
		const double to_double() const noexcept;

		unsigned integer()const { return m_integer; }
		unsigned decimal()const { return m_decimal; }
		bool negative()const { return m_negative; }


		fraction& operator= (const fraction& f);
		bool operator==(const fraction& f) const;
		const fraction operator+(const fraction& f)const;
		const fraction operator-(const fraction& f)const;
		const fraction operator*(const fraction& f)const;
		const fraction operator/(const fraction& f)const;
		const fraction operator-()const;
		fraction& operator+=(const fraction& f);
		fraction& operator-=(const fraction& f);
		fraction& operator*=(const fraction& f);
		fraction& operator/=(const fraction& f);
		std::istream& operator>>(std::istream& in);
		std::ostream& operator<<(std::ostream& out)const;
		friend const fraction gcd(const fraction& f1,
								  const fraction& f2);
		friend const fraction lcm(const fraction& f1,
								  const fraction& f2);
		friend const fraction abs(fraction f);
	protected:
		void reduce();
		unsigned m_integer, m_decimal;
		bool m_negative;
	};


}