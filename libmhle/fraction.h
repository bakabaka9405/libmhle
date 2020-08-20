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
		fraction(int integer,
						  int decimal = 1);
		explicit fraction(const char* str);
		explicit fraction(const std::string& str);

		const std::string to_string() const noexcept;
		const int to_int() const noexcept;
		const double to_double() const noexcept;

		int integer()const { return m_integer; }
		unsigned decimal()const { return m_decimal; }


		fraction& operator= (const fraction& f);
		bool operator==(const fraction& f) const;
		bool operator!=(const fraction& f)const;
		const fraction operator+(const fraction& f)const;
		const fraction operator-(const fraction& f)const;
		const fraction operator*(const fraction& f)const;
		const fraction operator/(const fraction& f)const;
		const fraction operator-()const;
		fraction& operator+=(const fraction& f);
		fraction& operator-=(const fraction& f);
		fraction& operator*=(const fraction& f);
		fraction& operator/=(const fraction& f);
		friend std::istream& operator>>(std::istream& in,fraction& f);
		friend std::ostream& operator<<(std::ostream& out,const fraction& f);
		friend const fraction gcd(const fraction& f1,
								  const fraction& f2);
		friend const fraction lcm(const fraction& f1,
								  const fraction& f2);
		friend const fraction abs(fraction f);
	protected:
		void reduce();
		int m_integer,m_decimal;
	};


}