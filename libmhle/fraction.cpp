#include "fraction.h"

namespace mhle {
	fraction::fraction() :
		m_integer(0),
		m_decimal(1)
	{

	}

	fraction::fraction(const fraction& f)
	{
		m_integer = f.m_integer;
		m_decimal = f.m_decimal;
	}


	fraction::fraction(int _integer,
					   int _decimal) :
		m_integer(_integer),
		m_decimal(_decimal)
	{
		reduce();
	}

	fraction::fraction(const char* str) :
		m_integer(0),
		m_decimal(1)
	{
		bool flag = 0;
		if (str[0] == '-')flag = 1, ++str;
		int* pt = &m_integer;
		while (*str != '\0') {
			if (*str == '/') {
				if (flag)m_integer *= -1;
				pt = &m_decimal;
			}
			else *pt = (*pt * 10) + (*str - 48);
			++str;
		}
		reduce();
	}

	fraction::fraction(const std::string& str) :
		fraction(str.data())
	{
	}

	const std::string fraction::to_string() const noexcept
	{
		std::string result;
		if (m_decimal == 1)
			return result + std::to_string(m_integer);
		else
			return (result +
					std::to_string(m_integer) +
					'/' + std::to_string(m_decimal));
	}

	const int fraction::to_int() const noexcept
	{
		return m_integer / m_decimal;
	}

	const double fraction::to_double() const noexcept
	{
		return m_integer * 1.0 / m_decimal;
	}

	fraction& fraction::operator=(const fraction& f)
	{
		m_integer = f.m_integer;
		m_decimal = f.m_decimal;
		return *this;
	}

	bool fraction::operator==(const fraction& f)const
	{
		return (m_integer == f.m_integer &&
				m_decimal == f.m_decimal);
	}

	const fraction fraction::operator+(const fraction& f)const
	{
		if (!m_integer)return f;
		if (!f.m_integer) return *this;
		return fraction(m_integer * f.m_decimal +
						m_decimal * f.m_integer
						,
						m_decimal * f.m_decimal);
	}

	const fraction fraction::operator-(const fraction& f) const
	{
		if (!m_integer)return -f;
		if (!f.m_integer)return *this;
		return fraction(m_integer * f.m_decimal -
						m_decimal * f.m_integer
						,
						m_decimal * f.m_decimal);
	}

	const fraction fraction::operator*(const fraction& f) const
	{
		if (!(m_integer && f.m_integer))return fraction(0);
		return fraction(m_integer * f.m_integer,
						m_decimal * f.m_decimal);
	}

	const fraction fraction::operator/(const fraction& f) const
	{
		if (!m_integer)return fraction(0);
		if (f.m_integer == 0) {
			throw std::runtime_error("try to devide by an zero");
			return fraction();
		}
		return *this * fraction(f.m_decimal, f.m_integer);
	}

	const fraction gcd(const fraction& f1, const fraction& f2)
	{
		return fraction(gcd(f1.m_integer, f2.m_integer),
						gcd(f1.m_decimal, f2.m_decimal));
	}

	const fraction lcm(const fraction& f1, const fraction& f2)
	{
		return fraction(f1 * f2 / gcd(f1, f2));
	}

	const fraction abs(fraction f)
	{
		if (f.m_integer < 0)f.m_integer *= -1;
		return f;
	}

	void fraction::reduce()
	{
		if (!m_decimal) {
			throw std::runtime_error("the divisor cannot be zero");
			return;
		}
		if (!m_integer) {
			m_decimal = 1;
			return;
		}
		if (m_decimal < 0) {
			m_integer *= -1;
			m_decimal *= -1;
		}
		int tmp = abs(gcd(m_integer, m_decimal));
		m_integer /= tmp, m_decimal /= tmp;
	}

	std::istream& operator>>(std::istream& in, fraction& f)
	{
		f.m_integer = 0;
		f.m_decimal = 1;
		std::string str;
		in >> str;
		unsigned i = 0;
		bool flag = 0;
		if (str[0] == '-')flag = 1, ++i;
		int* pt = &f.m_integer;
		while (i < str.length()) {
			if (str[i] == '/') {
				if (pt == &f.m_decimal) {
					throw std::runtime_error("Invalid input");
					return in;
				}
				pt = &f.m_decimal;
				f.m_decimal = 0;
			}
			else *pt = (*pt * 10) + (str[i] - 48);
			++i;
		}
		if (flag)f.m_integer *= -1;
		f.reduce();
		return in;
	}

	std::ostream& operator<<(std::ostream& out, const fraction& f)
	{
		out << f.to_string();
		return out;
	}

	const fraction fraction::operator-() const
	{
		return fraction(-m_integer, m_decimal);
	}

	fraction& fraction::operator+=(const fraction& f)
	{
		m_integer = (m_integer * f.m_decimal +
					 m_decimal * f.m_integer);
		m_decimal *= f.m_decimal;
		reduce();
		return *this;
	}

	fraction& fraction::operator-=(const fraction& f)
	{
		m_integer = (m_integer * f.m_decimal -
					 m_decimal * f.m_integer);
		m_decimal *= f.m_decimal;
		reduce();
		return *this;
	}

	fraction& fraction::operator*=(const fraction& f)
	{
		m_integer *= f.m_integer;
		m_decimal *= f.m_decimal;
		reduce();
		return *this;
	}

	fraction& fraction::operator/=(const fraction& f)
	{
		if (!f.m_integer) {
			throw std::runtime_error("try to devide by an zero");
			return *this;
		}
		m_integer *= f.m_decimal;
		m_decimal *= f.m_integer;
		reduce();
		return *this;
	}

}